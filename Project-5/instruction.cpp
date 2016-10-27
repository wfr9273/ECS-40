#include <iostream>
#include <iomanip>
#include <cstring>
#include "instruction.h"
#include "word.h"


using namespace std;

Instruction::Instruction(int addr) : Word(addr)
{
  info = NULL;
}  // Instruction()


Instruction::~Instruction()
{
  if(info)
    delete [] info;
}  // ~Instruction
  
const char* Instruction::getInfo() const
{
  return info;
} // get()

void Instruction::operator=(const char* information)
{
  info = new char[strlen(information) + 1];
  strcpy(info, information);
} // operator =

ostream& operator<< (ostream &os, const Instruction &instruction)
{
  os << left << setw(20) << instruction.getInfo();
  return os;
} // operator <<
