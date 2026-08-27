
@echo off
rem Wrapper to run Check-EventLocalization.ps1 by dragging event file(s) onto this .bat
rem Place this .bat in the same folder as Check-EventLocalization.ps1 (tools\)

rem Resolve this batch file's directory and the PowerShell script path
set "SCRIPT_DIR=%~dp0"
set "PS_SCRIPT=%SCRIPT_DIR%Check-EventLocalization.ps1"

if not exist "%PS_SCRIPT%" (
  echo PowerShell script not found: "%PS_SCRIPT%"
  echo Ensure Check-EventLocalization.ps1 is in the same folder as this .bat
  pause
  exit /b 2
)

if "%~1"=="" (
  echo Usage: Drag one or more event .txt files onto this batch file.
  echo Or run: "%~nx0" "path\to\eventfile.txt"
  pause
  exit /b 1
)

rem Simple single-file wrapper (safer for drag-and-drop paths with parentheses).
rem If you need multi-file support, we can add a robust loop that handles arbitrary paths.
if "%~1"=="" (
  echo Usage: Drag one event .txt file onto this batch file.
  echo Or run: "%~nx0" "path\to\eventfile.txt"
  pause
  exit /b 1
)

set "EVENT_FILE=%~1"
if not exist "%EVENT_FILE%" (
  echo File not found: "%EVENT_FILE%"
  pause
  exit /b 2
)

echo ------------------------------------------------------------
echo Checking event file: "%EVENT_FILE%"
echo ------------------------------------------------------------

powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%PS_SCRIPT%" -EventFile "%EVENT_FILE%"
set "rc=%ERRORLEVEL%"

if "%rc%"=="3" (
  echo Some localization keys were missing (exit code 3).
  echo.
  pause
  exit /b 3
)
if "%rc%"=="2" (
  echo Event path resolution error (exit code 2).
  echo.
  pause
  exit /b 2
)
if "%rc%"=="1" (
  echo PowerShell script reported an error (exit code 1).
  echo.
  pause
  exit /b 1
)

echo All keys were found; no missing localization entries.
echo.
pause
exit /b 0

:end_args
echo All done.
pause
exit /b 0
