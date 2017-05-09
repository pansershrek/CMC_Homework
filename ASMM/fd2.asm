;%include "io.inc" 
section .rodata 
section .bss 
x resd 1 
section .text 
global fd2 
global _fd2
fd2: 
_fd2:
    push ebp 
    mov ebp,esp 
    finit 
	mov dword[x],3
    fld qword[esp+8]
    fld qword[esp+8]
 	
    fmulp   
	fimul dword[x]
    
leave 
xor eax,eax 
ret
