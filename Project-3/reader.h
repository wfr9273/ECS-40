#ifndef READER_H
#define	READER_H
// Author: Leo & Olivia

#include "instruction.h"
#include "registers.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

class Reader
{
  Instruction lines[1000];
  
  public:	
    void fetch(Instruction *instruction, Registers *registers);
    void read(Registers *registers, const char *filename);	
}; //class
#endif	// READER_H 

