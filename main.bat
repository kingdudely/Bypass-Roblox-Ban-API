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
echo Deleting Roblox cookies file...
set "RobloxCookies=%USERPROFILE%\AppData\Local\Roblox\LocalStorage\RobloxCookies.dat"
if exist "%RobloxCookies%" (
    del /q /s /f "%RobloxCookies%"
    echo Roblox cookies file deleted successfully.
) else (
    echo No Roblox cookies file found.
)

echo Press any key to close . . .
pause > nul
