;%include "io.inc" 
section .rodata 
section .bss 
x resd 1 
section .text 
global ff1
global _ff1 
ff1: 
_ff1:
    push ebp 
    mov ebp,esp 
    finit 
    MOV dword[x],1
    fld qword[esp+8] 
    fld qword[esp+8] 
    FMULP
	FIADD dword[x]
	MOV dword[x],4
    FLD1
    FIMUL dword[x]
    FDIVRP
    MOV dword[x],1
    FIADD dword[x]
    leave 
xor eax,eax 
ret
