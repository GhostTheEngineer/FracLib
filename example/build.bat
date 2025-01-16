@echo off
setlocal

@REM Require build flag
if not "%1"=="Release" if not "%1"=="Debug" (
    echo Usage: build.bat Release or Debug
    exit /b 1
)

set BUILD_TYPE=%1
set BUILD_DIR=bin\%BUILD_TYPE%
set FracLib=%CD%\..\out\FracLib

rem Normalize the path to FracLib
for /f "delims=" %%i in ("%FracLib%") do set FracLib=%%~fi

rem Ensure the library installation directory exists
if not exist "%FracLib%" (
    echo "Error: Required library directory %FracLib% does not exist."
    exit /b 1
)

mkdir %BUILD_DIR%
cd %BUILD_DIR%

cmake -S ../.. -B . -G "Ninja" -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DCMAKE_PREFIX_PATH="%FracLib%"
cmake --build .