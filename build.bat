@echo off
setlocal

:: Require build flag and set variable
if not "%1"=="Release" if not "%1"=="Debug" (
    echo Usage: build.bat Release or Debug
    exit /b 1
)
set BUILD_TYPE=%1

:: Create build directory
set BUILD_DIR=out\bin\%BUILD_TYPE%
mkdir %BUILD_DIR%

cd %BUILD_DIR%

:: Set install directory - must come after we are in build directory
set INSTALL_DIR="%CD%\..\..\FracLib"

:: Generate library
cmake -G "Ninja" -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DCMAKE_INSTALL_PREFIX=%INSTALL_DIR% ../../..

:: Build and install the library
cmake --build .
cmake --install .