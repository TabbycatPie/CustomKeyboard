@echo off
::Keil执行文件位置
set UV=D:\IDEs\Keil5\UV4\UV4.exe
::uvprojx工程文件位置
set PRO_REC=..\CustomKeyboard\project\project.uvproj
set PRO_REM=..\nrf_key_stc8h1k08\project\project.uvproj
set REC_GH=..\CustomKeyboard\project\global.h
set REC_HEX=..\CustomKeyboard\project\Objects\CH552G.hex
set REM_GH=..\nrf_key_stc8h1k08\project\global.h
set REM_HEX=..\nrf_key_stc8h1k08\project\Objects\STC8.hex
echo ---------------------------------------------------------------
echo Author:TabbyCatPie
echo Init Loop..
for /l %%a in (0, 1, 255) do (
    echo setting address %%a to global.h
    echo #define ADDRESS %%a >%REC_GH%
    echo #define ADDRESS %%a >%REM_GH%
    echo start compile...
    echo compiling %PRO_REC%
    %UV% -j0 -b %PRO_REC%
    echo compiling %PRO_REM%
    %UV% -j0 -b %PRO_REM%
    echo move file .hex file to .\firmware
    ::创建文件夹
    echo moving files
    if not exist .\firmware md .\firmware
    if not exist .\firmware\S%%a md .\firmware\S%%a
    move %REC_HEX% .\firmware\S%%a
    ren .\firmware\S%%a\CH552G.hex .\firmware\S%%a\receiver.hex
    move %REM_HEX% .\firmware\S%%a
    ren .\firmware\S%%a\STC8.hex .\firmware\S%%a\remoter.hex
)