@echo off
setlocal enabledelayedexpansion

echo Compilado com sucesso!

set SRC=
for /r src\source %%f in (*.c) do (
    set SRC=!SRC! %%f
)

gcc -Wall -Wextra %SRC% -Isrc\headers -o game\RDPQuest.exe


pause
