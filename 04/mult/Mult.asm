// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Inicializando a variável
	@R2
	M=0 // R2 = 0

// Especificando o loop	
(LOOP)
	@R0 // R0 é o número de vezes que o loop vai executar
	D=M // D = R0
	@END
	D;JEQ // se R0 = 0, pula para o fim
	
	@R1
	D=M // D = R1, que é o número que será somado
	@R2
	M=M+D // R2 = R2 + R1
	
	@R0
	M=M-1 // tira um do contador
	
	@LOOP
	0;JMP // volta para o começo do loop
	
(END)
	@END
	0;JMP // loop infinito ao fim do programa
