;%include "io.inc" 
section .rodata 
section .bss 
x resd 1 
w1 resq 1
w2 resq 1
w3 resq 1
section .text 
global ff3 
global _ff3
ff3: 
_ff3:
    push ebp 
    mov ebp,esp 
    MOV dword[x],1
    finit 
    fld qword[esp+8]
	FCHS
   
	fst qword[w1]
	FRNDINT	
	fstp qword[w2]
	fld qword[w1]
	fld qword[w2]
	fsubp
	fst qword[w3]
	f2xm1 
	fiadd dword[x]
	fstp qword[w3]
	fld qword[w2]
	fld1
	fscale
	fld qword[w3]
	fmulp
    leave
xor eax,eax 
ret
