;%include "io.inc" 
section .rodata 
section .bss 
x resd 1 
section .text 
global ff3 
global _ff3
ff3: 
_ff3:
    push ebp 
    mov ebp,esp 
    MOV dword[x],-1
    finit 
    fld qword[esp+8]
    fimul dword[x]
    fld1
    fscale
    leave
xor eax,eax 
ret
