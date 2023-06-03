#include "generator.h"
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

    Instruction *instructions = (Instruction*) malloc((num1+4) * sizeof(Instruction));

    instructions[0].opcode = 0;
    instructions[0].info1 = num1;
    instructions[0].info2 = 0;
    instructions[0].info3 = 0;

    instructions[1].opcode = 0;
    instructions[1].info1 = num2;
    instructions[1].info2 = 1;
    instructions[1].info3 = 0;

    instructions[2].opcode = 0;
    instructions[2].info1 = 0;
    instructions[2].info2 = 2;
    instructions[2].info3 = 0;

    for (int i = 3; i < num1+3; i++){
        instructions[i].opcode = 1;
        instructions[i].info1 = 2;
        instructions[i].info2 = 1;
        instructions[i].info3 = 2;
    }


    instructions[num1+3].opcode = -1;
    instructions[num1+3].info1 = -1;
    instructions[num1+3].info2 = -1;
    instructions[num1+3].info3 = -1;

    return instructions;
}

Instruction* generateDivisionInstructions(int num1, int num2) {
    Instruction* instructions = (Instruction*) malloc((num1 + 7) * sizeof(Instruction));

    instructions[0].opcode = 0;   // Salvar num1
    instructions[0].info1 = num1;
    instructions[0].info2 = 0;
    instructions[0].info3 = 0;

    instructions[1].opcode = 0;   // Salvar num2
    instructions[1].info1 = num2;
    instructions[1].info2 = 1;
    instructions[1].info3 = 0;

    instructions[2].opcode = 0;   // Inicializar quociente (resultado) com 0
    instructions[2].info1 = 0;
    instructions[2].info2 = 2;
    instructions[2].info3 = 0;

    instructions[3].opcode = 0;   // Inicializar contador de subtrações com 0
    instructions[3].info1 = 0;
    instructions[3].info2 = 3;
    instructions[3].info3 = 0;

    instructions[4].opcode = 0;   
    instructions[4].info1 = 1;
    instructions[4].info2 = 4;
    instructions[4].info3 = 0;

    
    for (int i = 5; i < num1+6; i++) {
        instructions[i].opcode = 2;   
        instructions[i].info1 = 0;
        instructions[i].info2 = 1;
        instructions[i].info3 = 0;
        while(instructions[i].info1 >= num2){
            instructions[i].opcode = 1;   
            instructions[i].info1 = 2;
            instructions[i].info2 = 4;
            instructions[i].info3 = 2;
        }
    }

    instructions[num1 + 6].opcode = -1;   // Encerrar programa
    instructions[num1 + 6].info1 = -1;
    instructions[num1 + 6].info2 = -1;
    instructions[num1 + 6].info3 = -1;

    return instructions;
}

//num1 = base, num2 = expoente
Instruction* generatePowerInstructions(int num1, int num2){
    
    Instruction *instructions;//ponteiro para instruction

    //loop para fazer a potencia, multiplicação sucessiva
    for(int i = 0; i < num2 ;i++){
    
        instructions = generateMultiplicationInstructions(int num1, int num2);
        //num1 = instructions[].info3;
        
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
