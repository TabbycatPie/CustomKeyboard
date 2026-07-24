[CmdletBinding()]
param(
    [switch]$Clean,
    [switch]$NoRun,
    [string]$QtBinDir
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

function Get-QtTool([string]$QtBin, [string[]]$Names) {
    foreach ($name in $Names) {
        $path = Join-Path $QtBin $name
        if (Test-Path $path -PathType Leaf) { return $path }
    }
    return $null
}

function ConvertTo-QtBin([string]$Candidate) {
    if (-not $Candidate) { return $null }
    $expanded = [Environment]::ExpandEnvironmentVariables($Candidate.Trim('"'))
    if (Test-Path $expanded -PathType Leaf) {
        return Split-Path $expanded -Parent
    }
    if (Test-Path (Join-Path $expanded "bin") -PathType Container) {
        return (Join-Path $expanded "bin")
    }
    return $expanded
}

function Find-QtBin([string]$PreferredQtBin) {
    $candidates = New-Object System.Collections.Generic.List[string]
    $diagnostics = New-Object System.Collections.Generic.List[string]

    foreach ($preferred in @($PreferredQtBin, $env:QT_BIN_DIR, $env:QTDIR, $env:QT_ROOT_DIR)) {
        if ($preferred) { $candidates.Add((ConvertTo-QtBin $preferred)) }
    }

    foreach ($commandName in @("qmake.exe", "qmake6.exe", "qmake")) {
        $pathQmake = Get-CommandPath $commandName
        if ($pathQmake) { $candidates.Add((Split-Path $pathQmake -Parent)) }
    }

    $qtCreatorFiles = @(
        (Join-Path $env:APPDATA "QtProject\qtcreator\qtversion.xml"),
        (Join-Path $env:APPDATA "QtProject\qtcreator\profiles.xml")
    )
    foreach ($configFile in $qtCreatorFiles) {
        if (Test-Path $configFile -PathType Leaf) {
            $content = Get-Content $configFile -Raw -ErrorAction SilentlyContinue
            foreach ($match in [regex]::Matches($content, '(?i)([A-Z]:[/\\][^<"\r\n]*?qmake(?:6)?\.exe)')) {
                $qmakePath = [System.Net.WebUtility]::HtmlDecode($match.Groups[1].Value) -replace '/', '\'
                $candidates.Add((Split-Path $qmakePath -Parent))
            }
        }
    }

    $qtRoots = @(
        "C:\Qt", "D:\Qt", "E:\Qt",
        (Join-Path $env:USERPROFILE "Qt"),
        (Join-Path $env:LOCALAPPDATA "Qt"),
        (Join-Path $env:ProgramFiles "Qt")
    )
    foreach ($qtRoot in $qtRoots | Where-Object { $_ } | Select-Object -Unique) {
        if (-not (Test-Path $qtRoot -PathType Container)) { continue }
        Get-ChildItem $qtRoot -Directory -ErrorAction SilentlyContinue |
            Sort-Object Name -Descending |
            ForEach-Object {
                if ($_.Name -like "mingw*") {
                    $candidates.Add((Join-Path $_.FullName "bin"))
                }
                Get-ChildItem $_.FullName -Directory -Filter "mingw*" -ErrorAction SilentlyContinue |
                    Sort-Object Name -Descending |
                    ForEach-Object { $candidates.Add((Join-Path $_.FullName "bin")) }
            }
    }

    foreach ($candidate in $candidates | Where-Object { $_ } | Select-Object -Unique) {
        $qtBin = ConvertTo-QtBin $candidate
        $qmake = Get-QtTool $qtBin @("qmake.exe", "qmake6.exe")
        $deploy = Get-QtTool $qtBin @("windeployqt.exe", "windeployqt6.exe")
        $release = Get-QtTool $qtBin @("lrelease.exe", "lrelease6.exe")
        $missing = @()
        if (-not $qmake) { $missing += "qmake" }
        if (-not $deploy) { $missing += "windeployqt" }
        if (-not $release) { $missing += "lrelease" }
        if ($missing.Count -gt 0) {
            $diagnostics.Add("$qtBin (missing: $($missing -join ', '))")
            continue
        }

        $kitName = (Split-Path (Split-Path $qtBin -Parent) -Leaf)
        if ($kitName -notmatch '(?i)mingw') {
            $diagnostics.Add("$qtBin (not a MinGW kit: $kitName)")
            continue
        }
        return $qtBin
    }

    Write-Host "`nQt candidates checked:" -ForegroundColor Yellow
    if ($diagnostics.Count -eq 0) {
        Write-Host "    No Qt installation candidates were found."
    } else {
        $diagnostics | Select-Object -Unique | ForEach-Object { Write-Host "    $_" }
    }
    throw "Qt MinGW kit was not found. Run: build_windows.bat -QtBinDir `"D:\Qt\6.x.x\mingw_64\bin`""
}

function Find-Make([string]$QtBin) {
    $qtRoot = Split-Path (Split-Path (Split-Path $QtBin -Parent) -Parent) -Parent
    $toolsDir = Join-Path $qtRoot "Tools"
    if (Test-Path $toolsDir) {
        $kitName = Split-Path (Split-Path $QtBin -Parent) -Leaf
        $kitVersion = [regex]::Match($kitName, '\d+').Value
        $makeCandidates = Get-ChildItem $toolsDir -Filter "mingw32-make.exe" -File -Recurse -ErrorAction SilentlyContinue
        $make = $makeCandidates |
            Sort-Object @{Expression={ if ($kitVersion -and $_.FullName -match [regex]::Escape($kitVersion)) { 0 } else { 1 } }}, FullName |
            Select-Object -First 1
        if ($make) { return $make.FullName }
    }

    $pathMake = Get-CommandPath "mingw32-make.exe"
    if (-not $pathMake) { $pathMake = Get-CommandPath "mingw32-make" }
    if ($pathMake) { return $pathMake }

    throw "mingw32-make.exe was not found for Qt kit $QtBin. Install its matching MinGW component or add the compiler bin directory to PATH."
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
    $qtBin = Find-QtBin $QtBinDir
    $qmake = Get-QtTool $qtBin @("qmake.exe", "qmake6.exe")
    $lrelease = Get-QtTool $qtBin @("lrelease.exe", "lrelease6.exe")
    $windeployqt = Get-QtTool $qtBin @("windeployqt.exe", "windeployqt6.exe")
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
