@rem Visual Studio Command Prompt Script
@rem Usage: build.bat [usage|debug|release|clean] [static|dll]
@rem   usage    prints these usage details
@rem   debug    debug build configuration
@rem   release  release build configuration; default
@rem   clean    delete all intermediate and binary files
@rem   static   builds a static library; default
@rem   dll      builds a dynamic link library

@setlocal

@set MYBINARY=cairo
@set MYSOURCE=cairo-analysis-surface.c cairo-arc.c cairo-array.c cairo-atomic.c cairo-base64-stream.c cairo-base85-stream.c cairo-bentley-ottmann.c cairo-bentley-ottmann-rectangular.c cairo-bentley-ottmann-rectilinear.c cairo-botor-scan-converter.c cairo-boxes.c cairo-boxes-intersect.c cairo.c cairo-cache.c cairo-clip.c cairo-clip-boxes.c cairo-clip-polygon.c cairo-clip-region.c cairo-clip-surface.c cairo-color.c cairo-composite-rectangles.c cairo-compositor.c cairo-contour.c cairo-damage.c cairo-debug.c cairo-default-context.c cairo-device.c cairo-error.c cairo-fallback-compositor.c cairo-fixed.c cairo-font-face.c cairo-font-face-twin.c cairo-font-face-twin-data.c cairo-font-options.c cairo-freelist.c cairo-freed-pool.c cairo-gstate.c cairo-hash.c cairo-hull.c cairo-image-compositor.c cairo-image-info.c cairo-image-source.c cairo-image-surface.c cairo-lzw.c cairo-matrix.c cairo-mask-compositor.c cairo-mesh-pattern-rasterizer.c cairo-mempool.c cairo-misc.c cairo-mono-scan-converter.c cairo-mutex.c cairo-no-compositor.c cairo-observer.c cairo-output-stream.c cairo-paginated-surface.c cairo-path-bounds.c cairo-path.c cairo-path-fill.c cairo-path-fixed.c cairo-path-in-fill.c cairo-path-stroke.c cairo-path-stroke-boxes.c cairo-path-stroke-polygon.c cairo-path-stroke-traps.c cairo-path-stroke-tristrip.c cairo-pattern.c cairo-pen.c cairo-polygon.c cairo-polygon-intersect.c cairo-polygon-reduce.c cairo-raster-source-pattern.c cairo-recording-surface.c cairo-rectangle.c cairo-rectangular-scan-converter.c cairo-region.c cairo-rtree.c cairo-scaled-font.c cairo-shape-mask-compositor.c cairo-slope.c cairo-spans.c cairo-spans-compositor.c cairo-spline.c cairo-stroke-dash.c cairo-stroke-style.c cairo-surface.c cairo-surface-clipper.c cairo-surface-fallback.c cairo-surface-observer.c cairo-surface-offset.c cairo-surface-snapshot.c cairo-surface-subsurface.c cairo-surface-wrapper.c cairo-time.c cairo-tor-scan-converter.c cairo-tor22-scan-converter.c cairo-clip-tor-scan-converter.c cairo-toy-font-face.c cairo-traps.c cairo-tristrip.c cairo-traps-compositor.c cairo-unicode.c cairo-user-font.c cairo-version.c cairo-wideint.c cairo-cff-subset.c cairo-scaled-font-subsets.c cairo-truetype-subset.c cairo-type1-fallback.c cairo-type1-glyph-names.c cairo-type1-subset.c cairo-type3-glyph-surface.c cairo-pdf-operators.c cairo-pdf-shading.c cairo-png.c cairo-pdf-surface.c cairo-ft-font.c win32/cairo-win32-debug.c win32/cairo-win32-device.c win32/cairo-win32-gdi-compositor.c win32/cairo-win32-system.c win32/cairo-win32-surface.c win32/cairo-win32-display-surface.c win32/cairo-win32-printing-surface.c win32/cairo-win32-font.c 
@set MYCL=cl /nologo /c /W3 /arch:SSE2 /fp:fast /GR- /TC /wd4146 /wd4244 /I. /I../../pixman/pixman /I../../freetype/src /I../../zlib/src /I../../libpng/src /DWIN32 /DCAIRO_WIN32_STATIC_BUILD /D_CRT_SECURE_NO_WARNINGS /D_CRT_NONSTDC_NO_WARNINGS /D_BIND_TO_CURRENT_CRT_VERSION
@set MYLINK=link /nologo
@set MYMT=mt /nologo
@set MYLIB=lib /nologo /ignore:4221

@if not defined INCLUDE goto :BAD_PROMPT
@if "%1" equ "usage" goto :OK_USAGE
@if "%1" equ "debug" goto :OK_DEBUG
@if "%1" equ "release" goto :OK_RELEASE
@if "%1" equ "clean" goto :OK_CLEAN
@goto :OK_DEFAULT

:OK_USAGE
@echo.
@echo Usage: build.bat [usage^|debug^|release^|clean] [static^|dll]
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
@echo *** Unknown option(s); run 'build.bat usage' for build options ***
@goto :END

:BAD_BUILD
@echo.
@echo *** BUILD FAILED ***
@goto :END

:END
