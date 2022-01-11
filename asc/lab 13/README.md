nasm main.asm -fwin32 -o stocheaza.obj<br>
cl /Z7 main.c /link stocheaza.obj<br>
main.exe