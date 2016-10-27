// Author: Sean Davis

#include "registers.h"
#include "decoder.h"
#include "reader.h"
#include "instruction.h"
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* address(Registers *registers, char *operand, int memory[])
{
    static int value;
    char regNames[4][7] = {"eax", "ebp", "esp", "eip"};
    char *ptr;
    int regNum, index;

    if(operand == NULL)
    return NULL;

    if(operand[0] == '$') // immediate mode
    {
        value = atoi(&operand[1]);
        return &value;
    } // if immediate mode

    for(regNum = eax; regNum <= eip; regNum++)
        if(strstr(operand, regNames[regNum]))
        break;

    ptr = strchr(operand, '(');
    if(ptr) // some form of indirect addressing
    {
        *ptr = '\0';  // terminate operand string at first '('
        index = atoi(operand);  // will return 0 if no number there!
        return  &memory[registers->regs[regNum] + index];
    } // if ptr
    else  // direct addressing
    return &(registers->regs[regNum]);

} // address ()

int main(int argc, char* argv[])
{
    int memory[1001];
    int i;
    for (i=0; i<1001; i++)
    {
        memory[i]=0;
    }

    int j;

    Reader *reader;
    reader=NULL;
    FILE *fp;
    Registers *registers;
    registers=NULL;
    initialize(registers);
    Decoder *decoder;
    decoder=NULL;

    char *token1;
    char *token2;
    
    int line_c=0;

    if((fp=fopen(argv[1],"r"))!=NULL)
    {
        line_c=readcommand(fp, reader);

        for (j=0; j<=line_c; j++)
        {
            if(registers->regs[eip]==reader->lines[j].address)
            {
                decoder->opcode[0]=*strtok(reader->lines[j].info," ");
                token1=strtok(NULL,",");
                token2=strtok(NULL," ");

                decoder->operand1=address(registers, token1, memory);
                decoder->operand2=address(registers, token2, memory);

                if (strcmp(decoder->opcode , "addl")==0)
                    addl(decoder->operand1, decoder->operand2);
                else if (strcmp(decoder->opcode , "subl")==0)
                    subl(decoder->operand1, decoder->operand2);
                else if (strcmp(decoder->opcode , "andl")==0)
                    addl(decoder->operand1, decoder->operand2);
                else if (strcmp(decoder->opcode , "movl")==0)
                    movl(decoder->operand1, decoder->operand2);
                else if (strcmp(decoder->opcode , "pushl")==0)
                    pushl(decoder->operand1, registers, memory);
                else if (strcmp(decoder->opcode , "leave")==0)
                    leave(registers, memory);
                else if (strcmp(decoder->opcode , "ret")==0)
                    ret(registers, memory);

                printf("%s %s, %s\teip: \t%d eax:\t%d ebp:\t%d esp:\t%d", decoder->opcode, token1, token2, registers->regs[eip], registers->regs[eax], registers->regs[ebp], registers->regs[esp]);

                registers->regs[eip]+=4;
            }
        }
    }

    return 0;
}  // main()

