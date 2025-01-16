@echo off
setlocal

echo Compiling tests..
g++ -std=c++17 -o ./tests/test ./tests/main.cpp ./src/frac.cpp
if %errorlevel% neq 0 (
    echo Compilation failed.
    exit /b 1
)

echo Starting tests...
if exist ./tests/test.exe (
    start ./tests/test.exe
) else (
    echo Test executable not found.
    exit /b 1
)