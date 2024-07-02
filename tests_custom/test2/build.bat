@echo off

echo "Building test1.exe"

setlocal ENABLEDELAYEDEXPANSION

set THIS_DIR=%~dp0
set ROOT_DIR=%THIS_DIR%..\..
echo ROOT_DIR=%ROOT_DIR%

set INTEL_VARS_PATH=C:\Program Files (x86)\Intel\oneAPI\compiler\latest\env
set VS_VARS_PATH=C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build

call "%VS_VARS_PATH%\vcvars64.bat"
@call "%INTEL_VARS_PATH%\vars.bat" -arch intel64

set FC=ifx
set INCLUDE_DIRS=%INCLUDE_DIRS% /I"%CONDA_PREFIX%\Library\include"
set LIB_DIRS=%LIB_DIRS% /LIBPATH:"%CONDA_PREFIX%\Library\lib" /LIBPATH:"%CONDA_PREFIX%\Library\bin"
set SHARED_FLAGS=/nologo /fpp /4I8 /double-size:64 /real-size:64 /integer-size:64 /assume:nobscc /DMKL_ILP64 /DEBUG

ifx test1.f %SHARED_FLAGS% %INCLUDE_DIRS% /link /DEFAULTLIB:libucrt /dll %LIB_DIRS%

@REM if errorlevel 1 exit 1

call test1.exe

@REM if errorlevel 1 exit 1

echo "Successfully built and tested test1.exe"

endlocal