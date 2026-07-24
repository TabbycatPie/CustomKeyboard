[CmdletBinding()]
param(
    [switch]$Clean,
    [switch]$NoRun
)

$ErrorActionPreference = "Stop"
Set-StrictMode -Version Latest

$RootDir = $PSScriptRoot
$ProjectDir = Join-Path $RootDir "KeyboardSetter"
$ProjectFile = Join-Path $ProjectDir "KeyboardSetter.pro"
$BuildDir = Join-Path $RootDir "build\windows-release"
$DistDir = Join-Path $RootDir "dist\KeyboardSetter"

function Write-Step([string]$Message) {
    Write-Host "`n==> $Message" -ForegroundColor Cyan
}

function Get-CommandPath([string]$Name) {
    $command = Get-Command $Name -ErrorAction SilentlyContinue | Select-Object -First 1
    if ($null -ne $command) { return $command.Source }
    return $null
}

function Invoke-Tool([string]$FilePath, [string[]]$Arguments, [string]$WorkingDirectory) {
    Write-Host ("    " + $FilePath + " " + ($Arguments -join " "))
    Push-Location $WorkingDirectory
    try {
        & $FilePath @Arguments
        if ($LASTEXITCODE -ne 0) {
            throw "Command failed with exit code ${LASTEXITCODE}: $FilePath"
        }
    }
    finally {
        Pop-Location
    }
}

function Find-QtBin {
    $candidates = New-Object System.Collections.Generic.List[string]

    if ($env:QT_BIN_DIR) {
        $candidates.Add($env:QT_BIN_DIR)
    }

    $pathQmake = Get-CommandPath "qmake.exe"
    if (-not $pathQmake) { $pathQmake = Get-CommandPath "qmake" }
    if ($pathQmake) {
        $candidates.Add((Split-Path $pathQmake -Parent))
    }

    $qtRoots = @("C:\Qt")
    if ($env:QTDIR) {
        $qtRoots = @($env:QTDIR) + $qtRoots
    }

    foreach ($qtRoot in $qtRoots | Select-Object -Unique) {
        if (Test-Path $qtRoot) {
            Get-ChildItem $qtRoot -Directory -ErrorAction SilentlyContinue |
                Sort-Object Name -Descending |
                ForEach-Object {
                    Get-ChildItem $_.FullName -Directory -Filter "mingw*" -ErrorAction SilentlyContinue |
                        Sort-Object Name -Descending |
                        ForEach-Object { $candidates.Add((Join-Path $_.FullName "bin")) }
                }
        }
    }

    foreach ($candidate in $candidates | Select-Object -Unique) {
        if ((Test-Path (Join-Path $candidate "qmake.exe")) -and
            (Test-Path (Join-Path $candidate "windeployqt.exe"))) {
            return (Resolve-Path $candidate).Path
        }
    }

    throw "Qt MinGW kit was not found. Add its bin directory to PATH or set QT_BIN_DIR, for example C:\Qt\5.15.2\mingw81_64\bin."
}

function Find-Make([string]$QtBin) {
    $pathMake = Get-CommandPath "mingw32-make.exe"
    if (-not $pathMake) { $pathMake = Get-CommandPath "mingw32-make" }
    if ($pathMake) { return $pathMake }

    $qtRoot = Split-Path (Split-Path (Split-Path $QtBin -Parent) -Parent) -Parent
    $toolsDir = Join-Path $qtRoot "Tools"
    if (Test-Path $toolsDir) {
        $make = Get-ChildItem $toolsDir -Filter "mingw32-make.exe" -File -Recurse -ErrorAction SilentlyContinue |
            Sort-Object FullName -Descending |
            Select-Object -First 1
        if ($make) { return $make.FullName }
    }

    throw "mingw32-make.exe was not found. Install the MinGW component for your Qt kit or add its bin directory to PATH."
}

function Find-LibusbDll([string]$QtBin, [string]$MakePath) {
    $candidates = @(
        (Join-Path $ProjectDir "libs\libusb-1.0.dll"),
        (Join-Path $BuildDir "release\libusb-1.0.dll"),
        (Join-Path $BuildDir "libusb-1.0.dll"),
        (Join-Path $QtBin "libusb-1.0.dll"),
        (Join-Path (Split-Path $MakePath -Parent) "libusb-1.0.dll")
    )

    $pathDll = Get-CommandPath "libusb-1.0.dll"
    if ($pathDll) { $candidates += $pathDll }

    foreach ($candidate in $candidates | Select-Object -Unique) {
        if ($candidate -and (Test-Path $candidate -PathType Leaf)) {
            return (Resolve-Path $candidate).Path
        }
    }
    return $null
}

try {
    if (-not (Test-Path $ProjectFile)) {
        throw "Project file not found: $ProjectFile"
    }

    Write-Step "Detecting Qt MinGW tools"
    $qtBin = Find-QtBin
    $qmake = Join-Path $qtBin "qmake.exe"
    $lrelease = Join-Path $qtBin "lrelease.exe"
    $windeployqt = Join-Path $qtBin "windeployqt.exe"
    $make = Find-Make $qtBin

    if (-not (Test-Path $lrelease)) {
        throw "lrelease.exe was not found in the selected Qt kit: $qtBin"
    }

    Write-Host "    Qt bin: $qtBin"
    Write-Host "    Make:   $make"

    if ($Clean) {
        Write-Step "Cleaning generated directories"
        Remove-Item $BuildDir -Recurse -Force -ErrorAction SilentlyContinue
        Remove-Item $DistDir -Recurse -Force -ErrorAction SilentlyContinue
    }

    New-Item $BuildDir -ItemType Directory -Force | Out-Null

    Write-Step "Generating application translations"
    $translationFiles = @(
        (Join-Path $ProjectDir "lang\trans_zh_CN.ts"),
        (Join-Path $ProjectDir "lang\trans_en_US.ts")
    )
    Invoke-Tool $lrelease $translationFiles $ProjectDir

    Write-Step "Configuring Release build"
    Invoke-Tool $qmake @($ProjectFile, "CONFIG+=release", "CONFIG-=debug") $BuildDir

    Write-Step "Building KeyboardSetter"
    Invoke-Tool $make @("-j$([Environment]::ProcessorCount)") $BuildDir

    $builtExeCandidates = @(
        (Join-Path $BuildDir "release\KeyboardSetter.exe"),
        (Join-Path $BuildDir "KeyboardSetter.exe")
    )
    $builtExe = $builtExeCandidates | Where-Object { Test-Path $_ -PathType Leaf } | Select-Object -First 1
    if (-not $builtExe) {
        throw "Build finished but KeyboardSetter.exe was not found under $BuildDir."
    }

    Write-Step "Preparing deployment directory"
    Remove-Item $DistDir -Recurse -Force -ErrorAction SilentlyContinue
    New-Item $DistDir -ItemType Directory -Force | Out-Null
    $deployedExe = Join-Path $DistDir "KeyboardSetter.exe"
    Copy-Item $builtExe $deployedExe -Force

    Write-Step "Deploying Qt DLLs and plugins"
    Invoke-Tool $windeployqt @("--release", "--compiler-runtime", "--no-translations", $deployedExe) $DistDir

    Write-Step "Copying application translations"
    foreach ($tsFile in $translationFiles) {
        $qmFile = [IO.Path]::ChangeExtension($tsFile, ".qm")
        if (-not (Test-Path $qmFile)) {
            throw "Translation output was not generated: $qmFile"
        }
        Copy-Item $qmFile $DistDir -Force
    }

    Write-Step "Locating libusb runtime"
    $libusbDll = Find-LibusbDll $qtBin $make
    if (-not $libusbDll) {
        throw "libusb-1.0.dll was not found. Put a DLL matching this MinGW build architecture in: $ProjectDir\libs\libusb-1.0.dll"
    }
    Copy-Item $libusbDll (Join-Path $DistDir "libusb-1.0.dll") -Force

    $requiredFiles = @(
        $deployedExe,
        (Join-Path $DistDir "platforms\qwindows.dll"),
        (Join-Path $DistDir "trans_zh_CN.qm"),
        (Join-Path $DistDir "trans_en_US.qm"),
        (Join-Path $DistDir "libusb-1.0.dll")
    )
    foreach ($requiredFile in $requiredFiles) {
        if (-not (Test-Path $requiredFile -PathType Leaf)) {
            throw "Required deployment file is missing: $requiredFile"
        }
    }

    Write-Host "`nDeployment completed: $DistDir" -ForegroundColor Green
    if (-not $NoRun) {
        Write-Step "Starting KeyboardSetter"
        Start-Process -FilePath $deployedExe -WorkingDirectory $DistDir
    }
    exit 0
}
catch {
    Write-Host "`nERROR: $($_.Exception.Message)" -ForegroundColor Red
    Write-Host "No application was started. Fix the issue and run the script again." -ForegroundColor Yellow
    exit 1
}
