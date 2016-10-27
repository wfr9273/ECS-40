#ifndef DECODER_H
#define	DECODER_H
// Author: Leo & Olivia

#include "instruction.h"
#include "registers.h"
#include "labels.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

class Decoder
{
  char opcode[20];
  int *operand1;
  int *operand2;
  
  private:
    void addl(Registers *registers);
    void andl(Registers *registers); 
    void leave(Registers *registers, int memory[1001]) const;
    void movl();
    void pushl(Registers *registers, int memory[1001]) const;
    void ret(Registers *registers, int memory[1001]) const;
    void subl(Registers *registers);
    void cmpl(Registers *registers);
    void incl(Registers *registers);
    void jg(Registers *registers);
    void jle(Registers *registers);
    void jmp(Registers *registers);
    void leal(Registers *registers);
    void call(Registers *registers, int memory[1001]);
    void sall(Registers *registers);
  
  public:
    void parse(Instruction *instruction, Registers *registers, 
               int memory[1001], Labels *labels);
    void execute(Registers *registers, int memory[1001],
                 Instruction *instruction);
   
}; //class
#endif	// DECODER_H 

