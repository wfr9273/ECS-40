#ifndef INSTRUCTION_H
#define	INSTRUCTION_H

#include <iostream>
#include "word.h"

using namespace std;

class Instruction : public Word
{
  char *info;
public:
  Instruction(int addr);
  ~Instruction();
  const char* getInfo() const;
  void setInfo(const char* information);
  void operator=(const char* information);
  friend ostream& operator<< (ostream &os, const Instruction &instruction);
  
}; //class Instruction

#endif	// INSTRUCTION_H 

