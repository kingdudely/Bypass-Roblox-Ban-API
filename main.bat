@echo off
chcp 65001 >nul
cls

:: Request administrative privileges
>nul 2>&1 "%SYSTEMROOT%\system32\cacls.exe" "%SYSTEMROOT%\system32\config\system"
if '%errorlevel%' NEQ '0' (
    echo Requesting administrative privileges...
    goto UACPrompt
) else (
    goto gotAdmin
)

:UACPrompt
    echo Set UAC = CreateObject^("Shell.Application"^) > "%temp%\getadmin.vbs"
    echo UAC.ShellExecute "cmd.exe", "/c %~s0", "", "runas", 1 >> "%temp%\getadmin.vbs"
    "%temp%\getadmin.vbs"
    del "%temp%\getadmin.vbs"
    exit /B

:gotAdmin
cls
echo Deleting all files in Roblox LocalStorage directory...
set "RobloxLocalStorage=%USERPROFILE%\AppData\Local\Roblox\LocalStorage"

if exist "%RobloxLocalStorage%" (
    del /q /f "%RobloxLocalStorage%\*" 2>nul
    echo All files in LocalStorage directory deleted successfully.
) else (
    echo Roblox LocalStorage directory not found.
)

echo Press any key to close . . .
pause > nul
