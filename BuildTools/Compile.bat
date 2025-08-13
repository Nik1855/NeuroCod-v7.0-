@echo off
setlocal

:: Установка переменных среды
call "%ProgramFiles(x86)%\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

:: Создание директорий
if not exist "..\x64\Release" mkdir "..\x64\Release"

:: Компиляция проекта
msbuild ..\Core\NeuroCod.vcxproj ^
    /p:Configuration=Release ^
    /p:Platform=x64 ^
    /p:WindowsTargetPlatformVersion=10.0.19041.0

:: Копирование зависимостей
call PostBuild.bat

:: Копирование исполняемого файла
copy "..\x64\Release\NeuroCod.exe" "..\NeuroCod.exe" /Y

echo Сборка завершена! Исполняемый файл: ..\NeuroCod.exe
endlocal