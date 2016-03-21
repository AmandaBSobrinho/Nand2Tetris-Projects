// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, the
// program clears the screen, i.e. writes "white" in every pixel.
	
(LOOP1) // fica esperando por uma tecla ser pressionada
	@SCREEN
	D=A
	@addr
	M=D-1 // addr = 16384-1 (endereço base da tela menos 1)
	
	@255
	D=A
	@n
	M=D // n = 256 (para as linhas)
	
	@KBD
	D=M
	@LOOP2
	D;JEQ // se nenhuma tecla é pressionada, entra no loop 2 (deixa a tela branca)
	
	@LOOP3 // se alguma tecla é pressionada, entra no loop 3 (deixa a tela preta)
	0;JMP
	
(LOOP2) // faz andar em 256 linhas para a tela branca
	@31
	D=A
	@i
	M=D // i = 32
	
	@n
	D=M
	@LOOP1
	D;JEQ // quando terminar de preencher as 256 linhas, volta a aguardar (LOOP1)
	
	@n
	M=M-1 // tira um da variável contadora n
	@addr
	M=M+1 // passa para o próximo endereço
	
	@LOOP4
	0;JEQ // entra no loop 4 para preencher a linha inteira de branco
	
(LOOP3) // faz andar em 256 linhas para a tela preta
	@32
	D=A
	@i
	M=D // i = 32
	
	@n
	D=M
	@LOOP1
	D;JEQ // quando terminar de preencher as 256 linhas (D = 0), volta a aguardar (LOOP1)
	
	@n
	M=M-1 // tira um da variável contadora
	@addr
	M=M+1 // passa para o próximo endereço
	
	@LOOP5
	0;JEQ // entra no loop 5 para preencher a linha inteira de preto
	
(LOOP4) // deixa a linha branca
	@i
	D=M
	@LOOP2
	D;JEQ // se i = 0, vai para o loop 2 (acabou de deixar a primeira linha branca)
	
	@addr
	A=M
	M=0 // RAM[addr] = 0 em binário (16 bits 0)
	
	@i
	M=M-1 // tira um da variável contadora
	@addr
	M=M+1 // passa para o próximo endereço
	
	@LOOP4
	0;JMP // volta ao início do loop 4
	
(LOOP5) // deixa a linha preta
	@i
	D=M
	@LOOP3
	D;JEQ // se i = 0, vai para o loop 3 (acabou de deixar a primeira linha preta)
	
	@addr
	A=M
	M=-1 // RAM[addr] = -1 em binário (16 bits 1)
	
	@i
	M=M-1 // tira um da variável contadora
	@addr
	M=M+1 // passa para o próximo endereço
	
	@LOOP5
	0;JMP // volta ao início do loop 5
