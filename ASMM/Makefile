all: main.o ff1.o ff2.o ff3.o fd1.o fd2.o fd3.o 
	gcc -o MyProg -m32 -lm ff1.o ff2.o ff3.o fd1.o fd2.o fd3.o main.o
main.o: main.c
	gcc -m32 -lm -c -o main.o main.c
ff1.o: ff1.asm
	nasm -f elf32 -o ff1.o ff1.asm
ff2.o: ff2.asm
	nasm -f elf32 -o ff2.o ff2.asm
ff3.o: ff3.asm
	nasm -f elf32 -o ff3.o ff3.asm
fd1.o: fd1.asm
	nasm -f elf32 -o fd1.o fd1.asm
fd2.o: fd2.asm
	nasm -f elf32 -o fd2.o fd2.asm
fd3.o: fd3.asm
	nasm -f elf32 -o fd3.o fd3.asm
clean:
	rm -rf *.o
