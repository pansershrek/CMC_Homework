;%include "io.inc" 
section .rodata 
section .bss 
x resd 1 
section .text 
global fd1
global _fd1 
fd1: 
_fd1:
    push ebp 
    mov ebp,esp 
    finit 
    MOV dword[x],1
    fld qword[esp+8] 
    fld qword[esp+8] 
    FMULP
	
	FIADD dword[x]
	MOV dword[x],-8
	fst st1
	FMULP
	
	fld qword[esp+8]
	FIMUL dword[x]
	FDIVRP
    leave 
xor eax,eax 
ret
