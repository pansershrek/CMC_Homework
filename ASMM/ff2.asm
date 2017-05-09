;%include "io.inc" 
section .rodata 
section .bss 
x resd 1 
section .text 
global ff2 
global _ff2
ff2: 
_ff2:
    push ebp 
    mov ebp,esp 
    finit 
    fld qword[esp+8]
    fld qword[esp+8]
 	
    fmulp   
	fld qword[esp+8]
 	fmulp
    
leave 
xor eax,eax 
ret
