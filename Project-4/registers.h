#ifndef REGISTERS_H
#define	REGISTERS_H
// Author: Leo & Olivia
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include "labels.h"

using namespace std;

class Registers 
{ 
  int regs[6];
  int stringToRegNum(char* str);
  
  public:
    typedef enum {eax, ebp, esp, eip, edx, flags} RegName;
    Registers();
    int* address(char *ptr, int memory[], Labels *labels);
    void initialize(int memory[1001]);
    void print(const char *instruction) const;
    int get(int number) const;
    void set(RegName rn, int nNewValue);
    void setFlags(int result);
    int getFlags();
    int* scaleIndexMode(char* operand, int memory[]);
    
    friend ostream &operator<<(ostream& os, const Registers& registers);
    int operator+=(int a);
}; //class

#endif	// REGISTERS_H 

