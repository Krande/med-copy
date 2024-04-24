@echo off
:: Test script for debugging linker commands
:: This should read the following paths from an .env file located next to this batch file
for /f "tokens=*" %%a in (.env) do set %%a
:: ROOT_DIR=C:\work\code\med-copy
:: BUILD_OUTPUT_DIR=%ROOT_DIR%\build\win-msvc-intel-fortran
:: CONDA_ENV_DIR=C:\work\mambaforge\envs\med-deps

link.exe ^
    %BUILD_OUTPUT_DIR%\src\2.3.6\fi\CMakeFiles\_fi236.dir\entmaaf.f.obj ^
    %BUILD_OUTPUT_DIR%\src\2.3.6\fi\CMakeFiles\_fi236.dir\jntf.f.obj ^
    %BUILD_OUTPUT_DIR%\src\2.3.6\fi\CMakeFiles\_fi236.dir\gauss.f.obj ^
    %BUILD_OUTPUT_DIR%\src\2.3.6\fi\CMakeFiles\_fi236.dir\exit.f.obj ^
    %BUILD_OUTPUT_DIR%\src\2.3.6\fi\CMakeFiles\_fi236.dir\resf_i.f.obj ^
    %BUILD_OUTPUT_DIR%\src\2.3.6\fi\CMakeFiles\_fi236.dir\interf.f.obj ^
    %BUILD_OUTPUT_DIR%\src\2.3.6\fi\CMakeFiles\_fi236.dir\fichf.f.obj ^
    %BUILD_OUTPUT_DIR%\src\2.3.6\fi\CMakeFiles\_fi236.dir\maaf.f.obj ^
    %BUILD_OUTPUT_DIR%\src\2.3.6\fi\CMakeFiles\_fi236.dir\prof.f.obj ^
    %BUILD_OUTPUT_DIR%\src\2.3.6\fi\CMakeFiles\_fi236.dir\resf_r.f.obj ^
    %BUILD_OUTPUT_DIR%\src\2.3.6\fi\CMakeFiles\_fi236.dir\famf.f.obj ^
    %BUILD_OUTPUT_DIR%\src\2.3.6\fi\CMakeFiles\_fi236.dir\equf.f.obj ^
    %BUILD_OUTPUT_DIR%\src\2.3.6\fi\CMakeFiles\_fi236.dir\scalaire.f.obj ^
    %BUILD_OUTPUT_DIR%\src\fi\CMakeFiles\_fi.dir\medsupport.f.obj ^
    %BUILD_OUTPUT_DIR%\src\fi\CMakeFiles\_fi.dir\medequivalence.f.obj ^
    %BUILD_OUTPUT_DIR%\src\fi\CMakeFiles\_fi.dir\medlink.f.obj ^
    %BUILD_OUTPUT_DIR%\src\fi\CMakeFiles\_fi.dir\medinterp.f.obj ^
    %BUILD_OUTPUT_DIR%\src\fi\CMakeFiles\_fi.dir\medstructelement.f.obj ^
    %BUILD_OUTPUT_DIR%\src\fi\CMakeFiles\_fi.dir\medfilter.f.obj ^
    %BUILD_OUTPUT_DIR%\src\fi\CMakeFiles\_fi.dir\medfile.f.obj ^
    %BUILD_OUTPUT_DIR%\src\fi\CMakeFiles\_fi.dir\medlocalization.f.obj ^
    %BUILD_OUTPUT_DIR%\src\fi\CMakeFiles\_fi.dir\medprofile.f.obj ^
    %BUILD_OUTPUT_DIR%\src\fi\CMakeFiles\_fi.dir\medjoint.f.obj ^
    %BUILD_OUTPUT_DIR%\src\fi\CMakeFiles\_fi.dir\medparameter.f.obj ^
    %BUILD_OUTPUT_DIR%\src\fi\CMakeFiles\_fi.dir\medfamily.f.obj ^
    %BUILD_OUTPUT_DIR%\src\fi\CMakeFiles\_fi.dir\medfield.f.obj ^
    %BUILD_OUTPUT_DIR%\src\fi\CMakeFiles\_fi.dir\medflibrary.f.obj ^
    %BUILD_OUTPUT_DIR%\src\fi\CMakeFiles\_fi.dir\medmesh.f.obj ^
    %BUILD_OUTPUT_DIR%\src\2.3.6\cfi\CMakeFiles\_cfi236.dir\equcf.c.obj ^
    %BUILD_OUTPUT_DIR%\src\2.3.6\cfi\CMakeFiles\_cfi236.dir\fichcf.c.obj ^
    %BUILD_OUTPUT_DIR%\src\2.3.6\cfi\CMakeFiles\_cfi236.dir\intercf.c.obj ^
    %BUILD_OUTPUT_DIR%\src\2.3.6\cfi\CMakeFiles\_cfi236.dir\jntcf.c.obj ^
    %BUILD_OUTPUT_DIR%\src\2.3.6\cfi\CMakeFiles\_cfi236.dir\rescf.c.obj ^
    %BUILD_OUTPUT_DIR%\src\2.3.6\cfi\CMakeFiles\_cfi236.dir\entmaacf.c.obj ^
    %BUILD_OUTPUT_DIR%\src\2.3.6\cfi\CMakeFiles\_cfi236.dir\famcf.c.obj ^
    %BUILD_OUTPUT_DIR%\src\2.3.6\cfi\CMakeFiles\_cfi236.dir\maacf.c.obj ^
    %BUILD_OUTPUT_DIR%\src\2.3.6\cfi\CMakeFiles\_cfi236.dir\procf.c.obj ^
    %BUILD_OUTPUT_DIR%\src\2.3.6\cfi\CMakeFiles\_cfi236.dir\scalairecf.c.obj ^
    %BUILD_OUTPUT_DIR%\src\2.3.6\cfi\CMakeFiles\_cfi236.dir\gausscf.c.obj ^
    %BUILD_OUTPUT_DIR%\src\2.3.6\cfi\CMakeFiles\_cfi236.dir\exitcf.c.obj ^
    %BUILD_OUTPUT_DIR%\src\2.3.6\cfi\CMakeFiles\_cfi236.dir\famcf231.c.obj ^
    %BUILD_OUTPUT_DIR%\src\2.3.6\cfi\CMakeFiles\_cfi236.dir\famcf232.c.obj ^
    %BUILD_OUTPUT_DIR%\src\2.3.6\cfi\CMakeFiles\_cfi236.dir\MEDversionedApiF.cxx.obj ^
    %BUILD_OUTPUT_DIR%\src\cfi\CMakeFiles\_cfi.dir\librarycf.c.obj ^
    %BUILD_OUTPUT_DIR%\src\cfi\CMakeFiles\_cfi.dir\medlocalizationcf.c.obj ^
    %BUILD_OUTPUT_DIR%\src\cfi\CMakeFiles\_cfi.dir\medprofilecf.c.obj ^
    %BUILD_OUTPUT_DIR%\src\cfi\CMakeFiles\_cfi.dir\medinterpcf.c.obj ^
    %BUILD_OUTPUT_DIR%\src\cfi\CMakeFiles\_cfi.dir\medlinkcf.c.obj ^
    %BUILD_OUTPUT_DIR%\src\cfi\CMakeFiles\_cfi.dir\medequivalencecf.c.obj ^
    %BUILD_OUTPUT_DIR%\src\cfi\CMakeFiles\_cfi.dir\medfieldcf.c.obj ^
    %BUILD_OUTPUT_DIR%\src\cfi\CMakeFiles\_cfi.dir\meshcf.c.obj ^
    %BUILD_OUTPUT_DIR%\src\cfi\CMakeFiles\_cfi.dir\medfamilycf.c.obj ^
    %BUILD_OUTPUT_DIR%\src\cfi\CMakeFiles\_cfi.dir\medstructelementcf.c.obj ^
    %BUILD_OUTPUT_DIR%\src\cfi\CMakeFiles\_cfi.dir\medsupportcf.c.obj ^
    %BUILD_OUTPUT_DIR%\src\cfi\CMakeFiles\_cfi.dir\medjointcf.c.obj ^
    %BUILD_OUTPUT_DIR%\src\cfi\CMakeFiles\_cfi.dir\medparametercf.c.obj ^
    %BUILD_OUTPUT_DIR%\src\cfi\CMakeFiles\_cfi.dir\medfiltercf.c.obj ^
    %BUILD_OUTPUT_DIR%\src\cfi\CMakeFiles\_cfi.dir\filecf.c.obj ^
    %BUILD_OUTPUT_DIR%\src\cfi\CMakeFiles\_cfi.dir\MEDversionedApi3F.cxx.obj ^
    %BUILD_OUTPUT_DIR%\src\CMakeFiles\medfwrap.dir\MEDiteratorsF.f.obj ^
    /out:%BUILD_OUTPUT_DIR%\src\medfwrap.dll ^
    /implib:%BUILD_OUTPUT_DIR%\src\medfwrap.lib ^
    /pdb:medfwrap.pdb ^
    /dll ^
    /version:11.1 ^
    /machine:x64 ^
    /LIBPATH:%CONDA_ENV_DIR%/lib ^
    msvcrt.lib ^
    /DEF:%BUILD_OUTPUT_DIR%\src\medfwrap_symbols.def ^
    %BUILD_OUTPUT_DIR%\src\medC.lib ^
    %CONDA_ENV_DIR%\Library\lib\hdf5.lib ^
    kernel32.lib ^
    user32.lib ^
    gdi32.lib ^
    winspool.lib ^
    shell32.lib ^
    ole32.lib ^
    oleaut32.lib ^
    uuid.lib ^
    comdlg32.lib ^
    advapi32.lib ^
    /DEBUG

SET "DLL_PATH=%BUILD_OUTPUT_DIR%\src\medfwrap.dll"
SET SYMBOL=MSEIPW

dumpbin /EXPORTS %DLL_PATH% | findstr %SYMBOL%
IF ERRORLEVEL 1 (
    echo Error: Symbol %SYMBOL% not found in %DLL_PATH%.
    exit /b 1
) ELSE (
    echo Success: Symbol %SYMBOL% found in %DLL_PATH%.
)

SET SYMBOL=MSEIPW222

dumpbin /EXPORTS %DLL_PATH% | findstr %SYMBOL%
IF ERRORLEVEL 1 (
    echo Error: Symbol %SYMBOL% not found in %DLL_PATH%.
    exit /b 1
) ELSE (
    echo Success: Symbol %SYMBOL% found in %DLL_PATH%.
)