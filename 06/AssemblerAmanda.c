// Assembler - Nand2Tetis - Week 06

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ConvertBin (int AI){
	int rem, i=1, binary=0;
	while (AI!=0){
		rem=AI%2;
        	AI/=2;
        	binary+=rem*i;
        	i*=10;
        }

	return binary;
}

int main (){
	FILE *arq1, *arq2;
	char ins[60], A[60], CT[17];
	char *dest, *comp, *jmp;
	int AI, i;
	
	struct symbol_value{
		char symbol[4];
		char value[4];
	};

	struct symbol_comp{
		char comp1[4];
		char comp2[4];
		char controls[7];
	};
	
	if (!(arq1 = fopen("Add.asm", "r"))){
		printf("Erro na abertura do arquivo!\n");
		return 0;
	}
	
	if (!(arq2 = fopen("Add.hack", "w"))){ // abrir um novo arquivo para escrita do código traduzido para binário
		printf("Erro na abertura do arquivo!\n");
		return 0;
	}
	
	static struct symbol_value dest_table[] = {
		{"\0" ,"000"},
		{"M"  ,"001"},
		{"D"  ,"010"},
		{"MD" ,"011"},
		{"A"  ,"100"},
		{"AM" ,"101"},
		{"AD" ,"110"},
		{"AMD","111"}
	};
	static struct symbol_value jmp_table[] = {
		{"\0" ,"000"},
		{"JGT","001"},
		{"JEQ","010"},
		{"JGE","011"},
		{"JLT","100"},
		{"JNE","101"},
		{"JLE","110"},
		{"JMP","111"}
	};
	static struct symbol_comp comp_table[] = {
		{"0"  ,"\0" ,"101010"},
		{"1"  ,"\0" ,"111111"},
		{"-1" ,"\0" ,"111010"},
		{"D"  ,"\0" ,"001100"},
		{"A"  ,"M"  ,"110000"}, 
		{"!D" ,"\0" ,"001101"},
		{"!A" ,"!M" ,"110001"},
		{"-D" ,"\0" ,"001111"},
		{"-A" ,"-M" ,"110011"},
		{"D+1","\0" ,"011111"},
		{"A+1","M+1","110111"},
		{"D-1","\0" ,"001110"},
		{"A-1","M-1","110010"},
		{"D+A","D+M","000010"},
		{"D-A","D-M","010011"},
		{"A-D","M-D","000111"},
		{"D&A","D&M","000000"},
		{"D|A","D|M","010101"}
	};
	
	while(fgets(ins, sizeof(ins), arq1)!=NULL){ // andamos linha por linha no arquivo, lendo cada uma
		if(ins[0] == '@'){ // se for uma instrução A
			strcpy(A, ins+1); // copiamos somente a instrução para o vetor A (sem o '@')
			AI = atoi(A); // convertemos para um inteiro
			AI = ConvertBin(AI); // AI recebe seu valor em binário
			fprintf(arq2, "%016d\n", AI); // imprimimos a instrução A em binário no arquivo
		}
		if(ins[0] != '@' && ins[0] != '/' && ins != NULL){ // se for uma instrução C
			dest=strtok(ins, "=");
			comp=strtok('\0', ";");
			jmp=strtok('\0', "\n"); // dividimos cada pedaço dela em um vetor
			// Procuramos cada pedaço nas tabelas e obtemos os valores em binário
			CT[0]=CT[1]=CT[2]='1'; // os três primeiros bits da instrução C recebem 1
			if(comp!=NULL){
				for(i=0; i<18; i++){
					if(!strcmp(comp_table[i].comp1, comp)){
						CT[3]='0'; // a recebe 0
						strcpy(CT+4, comp_table[i].controls);
						break;
					}
					else if(!strcmp(comp_table[i].comp2, comp)){
						CT[3]='1'; // a recebe 1
						strcpy(CT+4, comp_table[i].controls);
						break;
					}
				}
			}
			if(dest!=NULL){
				for(i=0; i<8; i++)
					if(!strcmp(dest_table[i].symbol, dest)){
						strcpy(CT+10, dest_table[i].value);
						break;
					}
			}
			if(jmp!=NULL){
				for(i=0; i<8; i++)
					if(!strcmp(jmp_table[i].symbol, jmp)){
						strcpy(CT+13, jmp_table[i].value);
						break;
					}
			}
			fprintf(arq2, "%s\n", CT); // imprime a instrução C em binário no arquivo
		}	
	}
	
	fclose(arq1);
	fclose(arq2);
	return 0;
}
