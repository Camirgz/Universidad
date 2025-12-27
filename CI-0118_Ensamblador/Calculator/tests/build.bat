@echo off
setlocal EnableDelayedExpansion

echo === Compilando Calculadora ===

:: Configuración
set CC=g++
set ASM_COMPILER=ml64
set NAME=Calculadora.exe
set CFLAGS=-c -std=c++17 -Iinclude -Llib
set SRC_DIR=src
set OBJ_DIR=build

:: Ejecutar el programa después de compilar (true/false)
set RUN_AFTER_COMPILE=false
:: Crear carpeta build si no existe
if not exist "%OBJ_DIR%" mkdir "%OBJ_DIR%"

:: Obtener ruta absoluta del directorio de objetos
for %%A in ("%OBJ_DIR%") do set OBJ_DIR=%%~fA

:: Borrar archivos anteriores en la carpeta build
del /Q "%OBJ_DIR%\*.obj" >nul 2>&1


:: Obtener ruta absoluta del directorio de objetos
for %%A in ("%OBJ_DIR%") do set OBJ_DIR=%%~fA

echo Compilando archivos .cpp...
for /R "%SRC_DIR%" %%F in (*.cpp) do (
    set "SRC=%%~fF"
    set "FILENAME=%%~nxF"
    set "OBJ=%OBJ_DIR%\%%~nF.obj"
    call :check_compile_cpp
)
if errorlevel 1 goto :compile_end

echo Compilando archivos .c...
for /R "%SRC_DIR%" %%F in (*.c) do (
    set "SRC=%%~fF"
    set "FILENAME=%%~nxF"
    set "OBJ=%OBJ_DIR%\%%~nF.obj"
    call :check_compile_cpp
)
if errorlevel 1 goto :compile_end

echo Compilando archivos .asm...
for /R "%SRC_DIR%" %%F in (*.asm) do (
    set "SRC=%%~fF"
    set "FILENAME=%%~nxF"
    set "OBJ=%OBJ_DIR%\%%~nF.obj"
    call :check_compile_asm
)
if errorlevel 1 goto :compile_end

goto :compile_end

:: Revisar si el .cpp cambió
:check_compile_cpp
if not exist "%OBJ%" goto :do_compile_cpp
for %%A in ("%SRC%") do set SRC_DATE=%%~tA
for %%B in ("%OBJ%") do set OBJ_DATE=%%~tB
if "%SRC_DATE%" gtr "%OBJ_DATE%" (
    goto :do_compile_cpp
) else (
    echo - Skipping: %FILENAME%
    goto :eof
)

:do_compile_cpp
echo - Compiling: %FILENAME%
"%CC%" %CFLAGS% "%SRC%" -o "%OBJ%" -Wall -Wextra -fmessage-length=0
if errorlevel 1 (
    echo Error compiling %FILENAME%
    exit /b 1
)
goto :eof

:check_compile_asm
if not exist "%OBJ%" goto :do_compile_asm
for %%A in ("%SRC%") do set SRC_DATE=%%~tA
for %%B in ("%OBJ%") do set OBJ_DATE=%%~tB
if "%SRC_DATE%" gtr "%OBJ_DATE%" (
    goto :do_compile_asm
) else (
    echo - Skipping: %FILENAME%
    goto :eof
)

:do_compile_asm
echo - Assembling: %FILENAME%
pushd "%OBJ_DIR%"
"%ASM_COMPILER%" /c "%SRC%" /Fo"%FILENAME:.asm=.obj%"
popd
if errorlevel 1 (
    echo Error assembling %FILENAME%
    exit /b 1
)
goto :eof

:compile_end

:: Enlazado
echo Linking...

:: Aquí está el fix IMPORTANTE: comillas en cada .obj
set "OBJ_FILES="
for %%F in ("%OBJ_DIR%\*.obj") do (
    set "OBJ_FILES=!OBJ_FILES! "%%F""
)

call %CC% -o "%NAME%" !OBJ_FILES! %LDFLAGS% %LIBS%

if errorlevel 1 (
    echo Linking error
    exit /b 1
) else (
    echo Successfull Compilation: %NAME%
    if /i "%RUN_AFTER_COMPILE%"=="true" (
        echo Ejecutando...
        start "" "%NAME%"
    )
)

endlocal
