// Author: Leo & Olivia

#include "decoder.h"
#include "instruction.h"
#include "registers.h"
#include "labels.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

void Decoder::addl(Registers *registers)
{
  *operand2 = *operand1 + *operand2;
  registers->setFlags(*operand2);
}  // addl()

void Decoder::andl(Registers *registers)
{
  *operand2 = *operand1 & *operand2;
  registers->setFlags(*operand2);
}  // andl()

void Decoder::execute(Registers *registers, int memory[1001],
                      Instruction *instruction)
{
  const char *opcodes[] = { "addl", "andl", "leave", "movl", "pushl",
                            "ret", "subl", "cmpl", "incl", "jg", "jle",
                            "jmp", "leal", "call", "sall"};
  enum OpcodeNum {ADDL, ANDL, LEAVE, MOVL, PUSHL, RET, SUBL, CMPL,
                  INCL, JG, JLE, JMP, LEAL, CALL, SALL};
  int opcodeNum;
  
  for(opcodeNum = ADDL; 
    strcmp(opcode, opcodes[opcodeNum]) != 0 || opcodeNum > SALL;
    ++opcodeNum);
  
  switch (opcodeNum)
  {
    case ADDL: addl(registers); break;
    case ANDL: andl(registers); break;
    case LEAVE: leave(registers, memory); break;
    case MOVL: movl(); break;
    case PUSHL: pushl(registers, memory); break;
    case RET: ret(registers, memory); break;
    case SUBL: subl(registers); break;
    case CMPL: cmpl(registers); break;
    case INCL: incl(registers); break;
    case JG: jg(registers); break;
    case JLE: jle(registers); break;
    case JMP: jmp(registers); break;
    case LEAL: leal(registers); break;
    case CALL: call(registers, memory); break;
    case SALL: sall(registers); break;
    default: cout << "Invalid opcode!\n" << endl;
  } // switch on oncodeNum
}  // execute()

void Decoder::leave(Registers *registers, int memory[1001]) const
{
  registers->set(Registers::esp, registers->get(Registers::ebp));
  registers->set(Registers::ebp, memory[registers->get(Registers::esp)]);
  *registers += 4;
}  // leave()

void Decoder::movl()
{
  *operand2 = *operand1;
}  // movl()

void Decoder::parse(Instruction *instruction, Registers *registers,
                    int memory[1001], Labels *labels)
{
  char *ptr, info[1000];
  
  //instruction->setInfo(info);
  strcpy(info, instruction->getInfo());
  
  strcpy(opcode, strtok(info, " "));
  ptr = strtok(NULL, " ");
  
  if(ptr)
  {
	  if(ptr[0] != '.' && ptr[1] != 'L' && ptr[0] != '_')
	  {
        operand1 = registers->address(ptr, memory, labels);
        ptr = strtok(NULL, " ");
        if(ptr)
        operand2 = registers->address(ptr, memory, labels);
      }  //if not directive
      else if((ptr[0] == '.' && ptr[1] == 'L') || (ptr[0] == '_'))
        operand1 = registers->address(ptr, memory, labels);
  } // if there is at least one operand
}  // parse()

void Decoder::pushl(Registers *registers, int memory[1001]) const
{
  *registers += (-4);
  memory[registers->get(Registers::esp)] = *operand1;
}  // pushl()


void Decoder::ret(Registers *registers, int memory[1001]) const
{
  registers->set(Registers::eip, memory[registers->get(Registers::esp)]);
  *registers += 4;
}  // ret()

void Decoder::subl(Registers *registers)
{
  *operand2 = *operand2 - *operand1;
  registers->setFlags(*operand2);
}  // subl()

void Decoder::cmpl(Registers *registers)
{
  registers->setFlags(*operand2 - *operand1);
}  //cmpl()

void Decoder::incl(Registers *registers)
{
	(*operand1)++;
	registers->setFlags(*operand1);
}  //incl()

void Decoder::jg(Registers *registers)
{
	if (registers->getFlags() == 0){
	  	registers->set(Registers::eip, *operand1);
	}
}  //jg()
    
void Decoder::jle(Registers *registers)
{
	if (registers->getFlags() == 1 || registers->getFlags() == 2){
	  	registers->set(Registers::eip, *operand1);
	}
}  //jle()

void Decoder::jmp(Registers *registers)
{
  	registers->set(Registers::eip, *operand1);
}  //jmp()

void Decoder::leal(Registers *registers)
{
  *operand2 = registers->get(Registers::ebp) + *operand1;
} //leal()

void Decoder::call(Registers *registers, int memory[1001])
{
  *registers += (-4);
  memory[registers->get(Registers::esp)] = registers->get(Registers::eip);
  registers->set(Registers::eip, *operand1);
} //call()
    
void Decoder::sall(Registers *registers)
{
  *operand2 << *operand1;
  registers->setFlags(*operand2);
} //sall()
