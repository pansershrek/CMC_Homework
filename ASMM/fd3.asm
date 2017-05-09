;%include "io.inc" 
section .rodata 
section .bss 
x resd 1 
section .text 
global fd3 
global _fd3
fd3: 
_fd3:
    push ebp 
    mov ebp,esp 
    MOV dword[x],-1
    finit 
    fld qword[esp+8]
    fimul dword[x]
    fld1
    fscale
	fimul dword[x]
	fldln2
	fmulp
    leave
xor eax,eax 
ret
