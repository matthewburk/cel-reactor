@rem Visual Studio Command Prompt Script
@rem Usage: build.bat [usage|debug|release|clean]
@rem   usage    prints these usage details
@rem   debug    debug build configuration
@rem   release  release build configuration; default
@rem   clean    delete all intermediate and binary files

@setlocal

@if not defined INCLUDE goto :BAD_PROMPT
@if "%1" equ "usage" goto :OK_USAGE
@if "%1" equ "debug" goto :OK_DEBUG
@if "%1" equ "release" goto :OK_RELEASE
@if "%1" equ "clean" goto :OK_CLEAN
@goto :OK_RELEASE

:OK_USAGE
@echo.
@echo Usage: build.bat [usage^|debug^|release^|clean]
@echo   usage    prints these usage details
@echo   debug    debug build configuration
@echo   release  release build configuration; default
@echo   clean    delete all intermediate and binary files
@goto :END

:OK_DEBUG
@set MYCONFIG=debug
@goto :OK_BUILD

:OK_RELEASE
@set MYCONFIG=release
@goto :OK_BUILD

:OK_CLEAN
@set MYCONFIG=clean
@goto :OK_BUILD

:OK_BUILD

@pushd zlib\src
@call build.bat %MYCONFIG%
@if errorlevel 1 goto :END
@popd

@pushd libpng\src
@call build.bat %MYCONFIG%
@if errorlevel 1 goto :END
@popd

@pushd pixman\src
@call build.bat %MYCONFIG%
@if errorlevel 1 goto :END
@popd

@pushd freetype\src
@call build.bat %MYCONFIG%
@if errorlevel 1 goto :END
@popd

@pushd cairo\src
@call build.bat %MYCONFIG%
@if errorlevel 1 goto :END
@popd

@goto :END

:BAD_PROMPT
@echo.
@echo *** This script must be run from a Visual Studio Command Prompt ***
@goto :END

:END

