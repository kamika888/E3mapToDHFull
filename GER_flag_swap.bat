@echo off
cd .\gfx\map\shields
ren shield_GER.bmp shield_GER_tmp.bmp
ren shield_GER_2.bmp shield_GER.bmp
ren shield_GER_tmp.bmp shield_GER_2.bmp
cd ..\..\..\gfx\map\flags
ren flag_GER.bmp flag_GER_tmp.bmp
ren flag_GER_2.bmp flag_GER.bmp
ren flag_GER_tmp.bmp flag_GER_2.bmp
cd ..\..\..\gfx\skins\ger
ren topbar.bmp topbar_tmp.bmp
ren topbar_2.bmp topbar.bmp
ren topbar_tmp.bmp topbar_2.bmp

echo German Flag is Swapped
pause