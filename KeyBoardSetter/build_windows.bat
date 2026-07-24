@echo off
setlocal
cd /d "%~dp0"

powershell.exe -NoLogo -NoProfile -File "%~dp0build_windows.ps1" %*
set "EXIT_CODE=%ERRORLEVEL%"

if not "%EXIT_CODE%"=="0" (
    echo.
    echo Build or deployment failed. See the message above.
    pause
)

exit /b %EXIT_CODE%
