#ifndef DECODER_H
#define	DECODER_H
// Author: Leo & Olivia

#include "instruction.h"
#include "registers.h"
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
    void addl();
    void andl(); 
    void leave(Registers *registers, int memory[1001]) const;
    void movl();
    void pushl(Registers *registers, int memory[1001]) const;
    void ret(Registers *registers, int memory[1001]) const;
    void subl();
  
  public:
    void parse(Instruction *instruction, Registers *registers, 
               int memory[1001]);
    void execute(Registers *registers, int memory[1001]);
   
}; //class
#endif	// DECODER_H 

