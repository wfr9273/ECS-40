// Author: Leo & Olivia

#include "decoder.h"
#include "instruction.h"
#include "registers.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;


void Decoder::addl()
{
  *operand2 = *operand1 + *operand2;
}  // addl()

void Decoder::andl()
{
  *operand2 = *operand1 & *operand2;
}  // andl()

void Decoder::execute(Registers *registers, int memory[1001])
{
  const char *opcodes[] = { "addl", "andl", "leave", "movl", "pushl", "ret",
    "subl"};
  enum OpcodeNum {ADDL, ANDL, LEAVE, MOVL, PUSHL, RET, SUBL};
  int opcodeNum;
  
  for(opcodeNum = ADDL; 
    strcmp(opcode, opcodes[opcodeNum]) != 0 || opcodeNum > SUBL;
    ++opcodeNum);
  
  switch (opcodeNum)
  {
    case ADDL: addl(); break;
    case ANDL: andl(); break;
    case LEAVE: leave(registers, memory); break;
    case MOVL: movl(); break;
    case PUSHL: pushl(registers, memory); break;
    case RET: ret(registers, memory); break;
    case SUBL: subl(); break;
    default: cout << "Invalid opcode!\n" << endl;
  } // switch on oncodeNum
 
}  // execute()

void Decoder::leave(Registers *registers, int memory[1001]) const
{
  registers->set(esp, registers->get(ebp));
  registers->set(ebp, memory[registers->get(esp)]);
  registers->set(esp, registers->get(esp) + 4);
}  // leave()


void Decoder::movl()
{
  *operand2 = *operand1;
}  // movl()


void Decoder::parse(Instruction *instruction, 
                    Registers *registers, int memory[1001])
{
  char *ptr, info[1000];
  
  //instruction->setInfo(info);
  strcpy(info, instruction->getInfo());
  
  strcpy(opcode, strtok(info, " "));
  ptr = strtok(NULL, " ");
  
  if(ptr)
  {
    operand1 = registers->address(ptr, memory);
    ptr = strtok(NULL, " ");
    
    if(ptr)
      operand2 = registers->address(ptr, memory);
  } // if there is at least one operand
}  // parse()





void Decoder::pushl(Registers *registers, int memory[1001]) const
{
  registers->set(esp, registers->get(esp)-4);
  memory[registers->get(esp)] = *operand1;
}  // pushl()


void Decoder::ret(Registers *registers, int memory[1001]) const
{
  registers->set(eip, memory[registers->get(esp)]);
  registers->set(esp, registers->get(esp) + 4);
}  // ret()


void Decoder::subl()
{
  *operand2 = *operand2 - *operand1;
}  // subl()
