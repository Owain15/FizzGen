@echo off
setlocal enabledelayedexpansion

set PREMAKE_DIR=vendor\bin\premake
set PREMAKE_EXE=%PREMAKE_DIR%\premake5.exe
set PREMAKE_VERSION=5.0.0-beta8
set PREMAKE_URL=https://github.com/premake/premake-core/releases/download/v%PREMAKE_VERSION%/premake-%PREMAKE_VERSION%-windows.zip

set NEEDS_DOWNLOAD=0

if not exist "%PREMAKE_EXE%" (
    set NEEDS_DOWNLOAD=1
) else (
    for /f "tokens=*" %%V in ('"%PREMAKE_EXE%" --version 2^>^&1') do set INSTALLED_VERSION=%%V
    echo Found premake5: !INSTALLED_VERSION!
    echo !INSTALLED_VERSION! | findstr /C:"%PREMAKE_VERSION%" >nul
    if errorlevel 1 (
        echo Version mismatch. Re-downloading v%PREMAKE_VERSION%...
        set NEEDS_DOWNLOAD=1
    )
)

if "!NEEDS_DOWNLOAD!"=="1" (
    if not exist "%PREMAKE_DIR%" mkdir "%PREMAKE_DIR%"
    echo Downloading premake5 v%PREMAKE_VERSION%...
    powershell -NoProfile -Command ^
        "Invoke-WebRequest -Uri '%PREMAKE_URL%' -OutFile '%PREMAKE_DIR%\premake5.zip';" ^
        "Expand-Archive -Path '%PREMAKE_DIR%\premake5.zip' -DestinationPath '%PREMAKE_DIR%' -Force;" ^
        "Remove-Item '%PREMAKE_DIR%\premake5.zip'"
    echo premake5 v%PREMAKE_VERSION% downloaded.
)

echo Updating git submodules...
git submodule sync --recursive
git submodule update --init --recursive

call %PREMAKE_EXE% vs2026
PAUSE