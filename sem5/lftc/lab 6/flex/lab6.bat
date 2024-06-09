.\tools\nasm\nasm.exe -f obj output.asm
.\tools\nasm\ALINK.EXE output.obj -oPE -subsys console -entry start
.\output.exe