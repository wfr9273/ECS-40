#include "registers.h"
#include "main.h"

#ifndef DECODER_H
#define DECODER_H
typedef struct
{
    char opcode[20];
    int *operand1;
    int *operand2;
}Decoder;
#endif // Decoder

void addl(int *op1,int *op2);

void subl(int *op1,int *op2);

void andl(int *op1,int *op2);

void movl(int *op1,int *op2);

void pushl(int *op1,Registers *registers, int memory[]);

void leave(Registers *registers, int memory[]);

void ret(Registers *registers, int memory[]);
