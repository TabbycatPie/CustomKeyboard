@echo off
setlocal
cd /d "%~dp0"

powershell.exe -NoLogo -NoProfile -Command "$content = Get-Content -LiteralPath '%~f0' -Raw; $marker = '# POWERSHELL_PAYLOAD'; $index = $content.IndexOf($marker); if ($index -lt 0) { throw 'PowerShell payload was not found.' }; Invoke-Expression $content.Substring($index + $marker.Length)"
set "EXIT_CODE=%ERRORLEVEL%"

if not "%EXIT_CODE%"=="0" (
    echo.
    echo Deployment failed. See the message above.
    pause
)
exit /b %EXIT_CODE%

# POWERSHELL_PAYLOAD
$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest

$BuildRoot = (Get-Location).Path
$ReleaseBuild = Join-Path $BuildRoot '_release_build'
$PackageDir = Join-Path $BuildRoot 'package\KeyboardSetter'

function Step([string]$Message) {
    Write-Host "`n==> $Message" -ForegroundColor Cyan
}

function Run([string]$Tool, [string[]]$Arguments, [string]$WorkingDirectory) {
    Write-Host ('    ' + $Tool + ' ' + ($Arguments -join ' '))
    Push-Location $WorkingDirectory
    try {
        & $Tool @Arguments
        if ($LASTEXITCODE -ne 0) {
            throw "Command failed with exit code ${LASTEXITCODE}: $Tool"
        }
    }
    finally {
        Pop-Location
    }
}

function FirstExisting([string[]]$Paths) {
    foreach ($path in $Paths) {
        if ($path -and (Test-Path $path -PathType Leaf)) {
            return (Resolve-Path $path).Path
        }
    }
    return $null
}

function FindCommand([string[]]$Names) {
    foreach ($name in $Names) {
        $command = Get-Command $name -ErrorAction SilentlyContinue | Select-Object -First 1
        if ($command) { return $command.Source }
    }
    return $null
}

try {
    Step 'Reading the existing Qt Creator build'
    $makefiles = @(
        (Join-Path $BuildRoot 'Makefile'),
        (Join-Path $BuildRoot 'Makefile.Release'),
        (Join-Path $BuildRoot 'Makefile.Debug')
    ) | Where-Object { Test-Path $_ -PathType Leaf }
    if ($makefiles.Count -eq 0) {
        throw 'No Makefile was found. Copy this BAT into the Qt Creator build folder after building the project once.'
    }

    $makeText = ($makefiles | ForEach-Object { Get-Content $_ -Raw }) -join "`n"

    $qmakeCandidates = New-Object System.Collections.Generic.List[string]
    foreach ($pattern in @(
        '(?im)^QMAKE\s*=\s*(.+?qmake(?:6)?\.exe)\s*$',
        '(?im)^QMAKE_QMAKE\s*=\s*(.+?qmake(?:6)?\.exe)\s*$',
        '(?i)([A-Z]:[/\\][^\r\n\"]*?qmake(?:6)?\.exe)'
    )) {
        foreach ($match in [regex]::Matches($makeText, $pattern)) {
            $value = $match.Groups[1].Value.Trim().Trim('"') -replace '/', '\'
            $qmakeCandidates.Add($value)
        }
    }
    $pathQmake = FindCommand @('qmake.exe', 'qmake6.exe', 'qmake')
    if ($pathQmake) { $qmakeCandidates.Add($pathQmake) }
    $qmake = FirstExisting ($qmakeCandidates | Select-Object -Unique)
    if (-not $qmake) {
        throw 'The qmake path could not be read from this build. Open Qt Creator, run qmake/build once, then copy this BAT into that build folder again.'
    }

    $qtBin = Split-Path $qmake -Parent
    $kitName = Split-Path (Split-Path $qtBin -Parent) -Leaf
    if ($kitName -notmatch '(?i)mingw') {
        throw "This build does not use a MinGW Qt kit: $kitName"
    }

    $projectCandidates = New-Object System.Collections.Generic.List[string]
    foreach ($match in [regex]::Matches($makeText, '(?i)([A-Z]:[/\\][^\r\n\"\t]*?\.pro)')) {
        $projectCandidates.Add(($match.Groups[1].Value.Trim().Trim('"') -replace '/', '\'))
    }
    foreach ($match in [regex]::Matches($makeText, '(?im)^DISTNAME\s*=.*$')) {
        $null = $match
    }
    $projectFile = FirstExisting ($projectCandidates | Select-Object -Unique)
    if (-not $projectFile) {
        throw 'KeyboardSetter.pro could not be located from the existing Makefile.'
    }
    $SourceDir = Split-Path $projectFile -Parent

    $windeployqt = FirstExisting @(
        (Join-Path $qtBin 'windeployqt.exe'),
        (Join-Path $qtBin 'windeployqt6.exe')
    )
    $lrelease = FirstExisting @(
        (Join-Path $qtBin 'lrelease.exe'),
        (Join-Path $qtBin 'lrelease6.exe')
    )
    if (-not $windeployqt) { throw "windeployqt was not found beside qmake: $qtBin" }
    if (-not $lrelease) { throw "lrelease was not found beside qmake: $qtBin" }

    $qtRoot = Split-Path (Split-Path (Split-Path $qtBin -Parent) -Parent) -Parent
    $makeCandidates = New-Object System.Collections.Generic.List[string]
    $toolsDir = Join-Path $qtRoot 'Tools'
    if (Test-Path $toolsDir -PathType Container) {
        Get-ChildItem $toolsDir -Filter 'mingw32-make.exe' -File -Recurse -ErrorAction SilentlyContinue |
            ForEach-Object { $makeCandidates.Add($_.FullName) }
    }
    $pathMake = FindCommand @('mingw32-make.exe', 'mingw32-make')
    if ($pathMake) { $makeCandidates.Add($pathMake) }
    $make = FirstExisting ($makeCandidates | Select-Object -Unique)
    if (-not $make) { throw 'mingw32-make.exe was not found for this Qt kit.' }

    Write-Host "    Project: $projectFile"
    Write-Host "    Qt kit:  $qtBin"
    Write-Host "    Make:    $make"

    Step 'Building a clean Release version'
    if (Test-Path $ReleaseBuild) { Remove-Item $ReleaseBuild -Recurse -Force }
    New-Item $ReleaseBuild -ItemType Directory -Force | Out-Null
    Run $qmake @($projectFile, 'CONFIG+=release', 'CONFIG-=debug') $ReleaseBuild
    Run $make @("-j$([Environment]::ProcessorCount)") $ReleaseBuild

    $releaseExe = FirstExisting @(
        (Join-Path $ReleaseBuild 'release\KeyboardSetter.exe'),
        (Join-Path $ReleaseBuild 'KeyboardSetter.exe')
    )
    if (-not $releaseExe) { throw "Release build completed but KeyboardSetter.exe was not found under $ReleaseBuild" }

    Step 'Running the official Qt deployment tool'
    if (Test-Path $PackageDir) { Remove-Item $PackageDir -Recurse -Force }
    New-Item $PackageDir -ItemType Directory -Force | Out-Null
    $packageExe = Join-Path $PackageDir 'KeyboardSetter.exe'
    Copy-Item $releaseExe $packageExe -Force
    Run $windeployqt @('--release', '--compiler-runtime', '--no-translations', $packageExe) $PackageDir

    Step 'Generating application translations'
    foreach ($language in @('trans_zh_CN', 'trans_en_US')) {
        $tsFile = Join-Path $SourceDir "lang\$language.ts"
        $qmFile = Join-Path $PackageDir "$language.qm"
        if (-not (Test-Path $tsFile -PathType Leaf)) { throw "Translation source is missing: $tsFile" }
        Run $lrelease @($tsFile, '-qm', $qmFile) $PackageDir
    }

    Step 'Copying non-Qt runtime DLLs'
    $debugDir = Join-Path $BuildRoot 'debug'
    $sourceLibDir = Join-Path $SourceDir 'libs'
    $runtimeSources = @($sourceLibDir, $debugDir) | Where-Object { Test-Path $_ -PathType Container }
    foreach ($runtimeSource in $runtimeSources) {
        Get-ChildItem $runtimeSource -Filter '*.dll' -File -ErrorAction SilentlyContinue |
            Where-Object {
                $_.Name -notmatch '^(?i)(Qt\d|libgcc|libstdc\+\+|libwinpthread)' -and
                $_.Name -notmatch '(?i)d\.dll$'
            } |
            ForEach-Object {
                $destination = Join-Path $PackageDir $_.Name
                if (-not (Test-Path $destination)) {
                    Copy-Item $_.FullName $destination
                    Write-Host "    Copied $($_.Name)"
                }
            }
    }

    $libusb = Join-Path $PackageDir 'libusb-1.0.dll'
    if (-not (Test-Path $libusb -PathType Leaf)) {
        throw 'libusb-1.0.dll was not found in the source libs folder or the existing debug folder.'
    }

    foreach ($required in @(
        $packageExe,
        (Join-Path $PackageDir 'platforms\qwindows.dll'),
        (Join-Path $PackageDir 'trans_zh_CN.qm'),
        (Join-Path $PackageDir 'trans_en_US.qm'),
        $libusb
    )) {
        if (-not (Test-Path $required -PathType Leaf)) { throw "Required release file is missing: $required" }
    }

    Write-Host "`nRelease package is ready:" -ForegroundColor Green
    Write-Host "    $PackageDir" -ForegroundColor Green
    Start-Process explorer.exe -ArgumentList $PackageDir
    Start-Process -FilePath $packageExe -WorkingDirectory $PackageDir
    exit 0
}
catch {
    Write-Host "`nERROR: $($_.Exception.Message)" -ForegroundColor Red
    Write-Host 'No old executable was started.' -ForegroundColor Yellow
    exit 1
}
