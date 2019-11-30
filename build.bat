@echo off

set program=img2cpp

set DEBUG=0

set IgnoredWarnings=-wd4505 -wd4702
set CompilerFlags=-nologo -WX -W4 -Z7 %IgnoredWarnings%
if %DEBUG% EQU 1 ( set CompilerFlags=%CompilerFlags% -Od
) ELSE ( set CompilerFlags=%CompilerFlags% -O2
)
set LinkerFlags=-incremental:no -opt:ref

IF NOT EXIST build mkdir build
pushd build

cl %CompilerFlags% ..\%program%.cpp /link %LinkerFlags%
set builderror=%ERRORLEVEL%

popd

exit /b %builderror%
