@rem Visual Studio Command Prompt Script
@rem Usage: msvclib.bat [usage|debug|release|clean] [static|dll]
@rem   usage    prints these usage details
@rem   debug    debug build configuration
@rem   release  release build configuration; default
@rem   clean    delete all intermediate and binary files
@rem   static   builds a static library; default
@rem   dll      builds a dynamic link library

@setlocal

@set MYBINARY=freetype
@set MYSOURCE=base/ftsystem.c base/ftinit.c base/ftdebug.c base/ftbase.c base/ftbbox.c base/ftglyph.c base/ftbdf.c base/ftbitmap.c base/ftcid.c base/ftfstype.c base/ftgasp.c base/ftgxval.c base/ftlcdfil.c base/ftmm.c base/ftotval.c base/ftpatent.c base/ftpfr.c base/ftstroke.c base/ftsynth.c base/fttype1.c base/ftwinfnt.c base/ftxf86.c cff/cff.c sfnt/sfnt.c truetype/truetype.c raster/raster.c smooth/smooth.c autofit/autofit.c pshinter/pshinter.c psnames/psnames.c
@set MYCL=cl /nologo /c /W3 /arch:SSE2 /fp:fast /GR- /TC /wd4146 /I. /DWIN32 /DFT2_BUILD_LIBRARY /D_CRT_SECURE_NO_WARNINGS /D_CRT_NONSTDC_NO_WARNINGS /D_BIND_TO_CURRENT_CRT_VERSION
@set MYLINK=link /nologo
@set MYMT=mt /nologo
@set MYLIB=lib /nologo

@if not defined INCLUDE goto :BAD_PROMPT
@if "%1" equ "usage" goto :OK_USAGE
@if "%1" equ "debug" goto :OK_DEBUG
@if "%1" equ "release" goto :OK_RELEASE
@if "%1" equ "clean" goto :OK_CLEAN
@goto :OK_DEFAULT

:OK_USAGE
@echo.
@echo Usage: msvclib.bat [usage^|debug^|release^|clean] [static^|dll]
@echo   usage    prints these usage details
@echo   debug    debug build configuration
@echo   release  release build configuration; default
@echo   clean    delete all intermediate and binary files
@echo   static   builds a static library; default
@echo   dll      builds a dynamic link library
@goto :END

:OK_DEBUG
@shift
@set MYBINARY=%MYBINARY%d
@set MYCL=%MYCL% /D_DEBUG /Od /RTC1 /MDd /Zi /Fd%MYBINARY%.pdb
@set MYLINK=%MYLINK% /DEBUG
@goto :OK_BUILD

:OK_RELEASE
@shift
@goto :OK_DEFAULT

:OK_CLEAN
@del /Q *.dll *.exp *.ilk *.lib *.manifest *.obj *.pdb 2>NUL
@goto :END

:OK_DEFAULT
@set MYCL=%MYCL% /DNDEBUG /Ob2 /Oi /Ot /Ox /MD
@goto :OK_BUILD

:OK_BUILD
@if "%1" equ "static" goto :OK_STATIC
@if "%1" equ "dll" goto :OK_DLL
@if "%1" equ "" goto :OK_STATIC
@goto :BAD_ARGS

:OK_STATIC
@set MYCL=%MYCL% /D_LIB
%MYCL% %MYSOURCE%
@if errorlevel 1 goto :BAD_BUILD
%MYLIB% /OUT:%MYBINARY%.lib *.obj
@if errorlevel 1 goto :BAD_BUILD
@goto :SUCCESS

:OK_DLL
@goto :NO_DLLSUPPORT
@set MYCL=%MYCL% /D_USRDLL
%MYCL% %MYSOURCE%
@if errorlevel 1 goto :BAD_BUILD
%MYLINK% /DLL /OUT:%MYBINARY%.dll *.obj
@if errorlevel 1 goto :BAD_BUILD
@if exist %MYBINARY%.dll.manifest^
  %MYMT% -manifest %MYBINARY%.dll.manifest -outputresource:%MYBINARY%.dll;2
@goto :SUCCESS

:SUCCESS
@del /Q *.exp *.ilk *.manifest *.obj 2>NUL
@echo.
@echo === BUILD SUCCESSFUL ===
@goto :END

:NO_DLLSUPPORT
@echo.
@echo *** This library only supports the 'static' build configuration ***
@goto :END

:BAD_PROMPT
@echo.
@echo *** This script must be run from a Visual Studio Command Prompt ***
@goto :END

:BAD_ARGS
@echo.
@echo *** Unknown option(s); run 'msvclib.bat usage' for build options ***
@goto :END

:BAD_BUILD
@echo.
@echo *** BUILD FAILED ***
@goto :END

:END
