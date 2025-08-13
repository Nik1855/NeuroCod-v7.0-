@echo off
setlocal

echo Копирование необходимых DLL...

copy "%ProgramFiles(x86)\Windows Kits\10\bin\10.0.19041.0\x64\Microsoft.UI.Xaml\2.7\Microsoft.UI.Xaml.dll" "..\x64\Release\" /Y
copy "%ProgramFiles(x86)\Microsoft Visual Studio\2022\Community\VC\Redist\MSVC\14.44.35207\x64\Microsoft.VC143.CRT\vcruntime140.dll" "..\x64\Release\" /Y
copy "%ProgramFiles(x86)\Microsoft Visual Studio\2022\Community\VC\Redist\MSVC\14.44.35207\x64\Microsoft.VC143.CRT\vcruntime140_1.dll" "..\x64\Release\" /Y

echo DLL скопированы!
endlocal