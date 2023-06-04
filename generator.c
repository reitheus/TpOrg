#include "generator.h"
#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>
 
Instruction* generateRandomInstructions(int ramSize) {
    // 01|22|13|45 => isto é uma instrução
    // 02|33|12|01 => isto é outra instrução
            
    // 0 => salvar na memória
    // 1 => opcode => somar
    // 2 => opcode => subtrair
    //-1 => halt
    
    // 22 => significa um endereço da RAM (10 endereço) 
    // 13 => significa 2o endereço
    // 45 => significa 3o endereco
    //ramSize => ESTA FORA DO INTERVALO DE 0 A ramSize DA MEMÓRIA RAM

    Instruction* instructions = (Instruction*) malloc(10 * sizeof(Instruction));

    for (int i=0; i<9; i++){
        instructions[i].opcode = rand() % 4; //0, 1, 2, 3, 4
        instructions[i].info1 = rand() % ramSize; //0 ... RAM_SIZE
        do {
            instructions[i].info2 = rand() % ramSize; //0 ... RAM_SIZE
        } while (instructions[i].info1 == instructions[i].info2);
        instructions[i].info3 = rand() % ramSize; //0 ... RAM_SIZE
    }
    
    //inserindo a ultima instrucao do programa que nao faz nada que presta
    instructions[9].opcode =-1;
    instructions[9].info1 = -1;
    instructions[9].info2 = -1;
    instructions[9].info3 = -1;
    
    return instructions;
}

Instruction* generateMultiplicationInstructions(int num1, int num2){

    Instruction *instructions = (Instruction*) malloc((num1+5) * sizeof(Instruction));

    instructions[0].opcode = 0;
    instructions[0].info1 = num1;//mandar o valor de num1 para ir para memoria
    instructions[0].info2 = 0;//aponta para qual endereço da memoria vai ficar o valor
    instructions[0].info3 = 0;

    instructions[1].opcode = 0;
    instructions[1].info1 = num2;//manda o valor de num2 para memoria
    instructions[1].info2 = 1;//aponta para endereço da memoria o valor de num2 vai ficar
    instructions[1].info3 = 0;

    instructions[2].opcode = 0;
    instructions[2].info1 = 0;//adiciona 0 na memoria
    instructions[2].info2 = 2;//adiciona 0 na posição 2 da memoria, que será utilizada para armazenar o resultado depois
    instructions[2].info3 = 0;

    for (int i = 3; i < num1+3; i++){
        instructions[i].opcode = 1;//opcode de soma
        instructions[i].info1 = 2;
        instructions[i].info2 = 1;
        instructions[i].info3 = 2;
        
        
    }
    
   
    
    
    instructions[num1+4].opcode = -1;
    instructions[num1+4].info1 = -1;
    instructions[num1+4].info2 = -1;
    instructions[num1+4].info3 = -1;

    return instructions;
}

Instruction* generateDivisionInstructions(int num1, int num2) {
    Instruction* instructions = (Instruction*) malloc((num1 + 5) * sizeof(Instruction));
    
    int c=0;
    int vaule;
    instructions[0].opcode = 0;   // Salvar num1
    instructions[0].info1 = num1;
    instructions[0].info2 = 0;
    instructions[0].info3 = 0;

    instructions[1].opcode = 0;   // Salvar num2
    instructions[1].info1 = num2;
    instructions[1].info2 = 1;
    instructions[1].info3 = 0;

    
    int i=3;
    while (i<num1+3) {
        
        instructions[i].opcode = 2;   
        instructions[i].info1 = 0;
        instructions[i].info2 = 1;
        instructions[i].info3 = 0;

        vaule;
        printf("%d",vaule);
        if(vaule > 0){
            c=c+1;
        }
        

        i += 1;
    }
    instructions[i].opcode = 0;   
    instructions[i].info1 = c;
    instructions[i].info2 = 2;
    instructions[i].info3 = 0;

    instructions[i + 1].opcode = -1;   // Encerrar programa
    instructions[i + 1].info1 = -1;
    instructions[i + 1].info2 = -1;
    instructions[i + 1].info3 = -1;

    return instructions;
}

//num1 = base, num2 = expoente
Instruction* generatePowerInstructions(int num1, int num2){
    
    Instruction *instructions;//ponteiro para instruction
    int aux = num1;
    
    //loop para fazer a potencia, multiplicação sucessiva
    for(int i = 0; i < num2 ;i++){
    
        instructions = generateMultiplicationInstructions(num1, num1);
        instructions[aux + 3].opcode = 3;
        instructions[aux + 3].info1 = 2;
        num1 = instructions[aux + 3].info2;
        printf("num1 = %i", num1);
        instructions[aux + 3].info3 = 0;
        
    }

    
    return instructions;
}



Instruction* readInstructions(char* fileName, int* ramSize) {
    printf("FILE -> %s\n", fileName);
    FILE* file = fopen(fileName, "r"); // Abrindo arquivo no modo leitura
    
    if (file == NULL) {
        printf("Arquivo nao pode ser aberto.\n");
        exit(1);
    }

    int n, i = 0;
    fscanf(file, "%d %d", ramSize, &n);
    Instruction* instructions = (Instruction*) malloc(n * sizeof(Instruction));
    while (i < n) {
        fscanf(file, "%d %d %d %d", &instructions[i].opcode, &instructions[i].info1, &instructions[i].info2, &instructions[i].info3);
        i++;
    }
    fclose(file); // Fechando o arquivo

    return instructions;
}
