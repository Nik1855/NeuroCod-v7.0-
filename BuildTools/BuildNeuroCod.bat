@echo off
setlocal enabledelayedexpansion

:: Проверка зависимостей
where msbuild >nul 2>&1
if %errorlevel% neq 0 (
    echo Ошибка: MSBuild не найден. Установите Visual Studio 2022.
    exit /b 1
)

where cppwinrt >nul 2>&1
if %errorlevel% neq 0 (
    echo Ошибка: cppwinrt не найден. Установите Windows 10 SDK.
    exit /b 1
)

:: Создание необходимых директорий
if not exist "..\x64" mkdir "..\x64"
if not exist "..\x64\Release" mkdir "..\x64\Release"
if not exist "..\GeneratedFiles" mkdir "..\GeneratedFiles"

:: Генерация файлов проекции C++/WinRT
cppwinrt.exe -in "sdk" -out "..\GeneratedFiles" -verbose

:: Компиляция проекта
msbuild ..\Core\NeuroCod.vcxproj ^
    /p:Configuration=Release ^
    /p:Platform=x64 ^
    /p:WindowsTargetPlatformVersion=10.0.19041.0

:: Копирование исполняемого файла
copy "..\x64\Release\NeuroCod.exe" "..\NeuroCod.exe" /Y

echo Сборка завершена! Исполняемый файл: ..\NeuroCod.exe
endlocal