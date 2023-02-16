@echo off
title CMAKE POST BUILD
echo THIS SCRIPT MIRRORS MPE/source/Sandbox/Data folder into the CMAKE build folder (MPE/build/Data)

cd ../

set RELPATH=%cd%

echo %RELPATH%

(robocopy %RELPATH%\source\Sandbox\Data %RELPATH%\build\Data /e /mir) ^& IF %ERRORLEVEL% LEQ 1 exit 0