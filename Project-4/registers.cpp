// Author: Leo & Olivia


#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include "registers.h"
#include "labels.h"

using namespace std;

Registers::Registers()
{
  regs[esp] = 1000;
  regs[ebp] = 996;
  regs[eip] = 100;
  regs[eax] = 0;
  regs[edx] = 0;
  regs[flags] = 0xC0;
} //constructor

int* Registers::address(char *operand, int memory[], Labels *labels)
{
  static int value, value1;
  char *ptr, *ptr1;
  int regNum, index;
  regNum = stringToRegNum(operand);
  
  if(operand == NULL)
    return NULL;

  if(operand[0] == '$') // immediate mode
  {
    value = atoi(&operand[1]);
    return &value;
  } // if immediate mode
  
  if (*operand == '.' || *operand == '_')
  {
    value1 = labels->find(operand);
    return &value1;
  } // if labels mode
  
  if((ptr1 = strchr(operand, ',')) && *(++ptr1) != NULL)
    return scaleIndexMode(operand, memory);
    
  ptr = strchr(operand, '(');
  if(ptr) // some form of indirect addressing
  {
    *ptr = '\0';  // terminate operand string at first '('
    index = atoi(operand);  // will return 0 if no number there!
    return  &memory[regs[regNum] + index];
  } // if ptr
  else  // direct addressing
    return &(regs[regNum]);
} // address ()
	
int Registers::get(int number) const
{	
  switch(number)
  {
      case eax: return regs[eax]; break;
      case ebp: return regs[ebp]; break;
      case esp: return regs[esp]; break;
      case eip: return regs[eip]; break;
      case edx: return regs[edx]; break;
      case flags: return regs[flags]; break;
      default: return 0;
  } //switch
} //get
    
void Registers::set(Registers::RegName rn, int nNewValue)
{ 
  regs[rn] = nNewValue; 
} //set

int Registers::operator+=(int a)
{
  return regs[esp] += a;
} //+=

void Registers::setFlags(int result)
{
  if (result > 0)
    regs[flags] = 0x00;
      
  else if (result ==0)
    regs[flags] = 0x40;
      
  else
	regs[flags] = 0x80;
} //setFlags

int Registers::getFlags()
{
  if (regs[flags] == 0x00)
    return 0;
  
  else if (regs[flags] == 0x40)
    return 1;
  
  else if (regs[flags] == 0x80)
	return 2;  
  
  else
    return -1;  
} //getFlags

ostream &operator<<(ostream& os, const Registers& registers)
{
  os << " eip: " << setw(3) << right << registers.regs[Registers::eip]
  << " eax: " << setw(3) << right << registers.regs[Registers::eax]
  << " ebp: " << setw(3) << right << registers.regs[Registers::ebp]
  << " esp: " << setw(3) << right << registers.regs[Registers::esp]
  << " edx: " << setw(3) << right << registers.regs[Registers::edx]
  << " flags: " << setw(3) << right << registers.regs[Registers::flags]
  << endl;
  return os;
} //<<

int* Registers::scaleIndexMode(char* operand, int memory[])
{
  int address = 0;
  int a, b, c, d;
  char *ptr;
  a = atoi(operand);
  ptr = strchr(operand, '(');
  b = stringToRegNum(ptr);
  ptr = strchr(ptr, ',');
  c = stringToRegNum(ptr);
  ptr = strchr(ptr, ',');
  d = atoi(ptr);
  address = a + b + c * d;
  return &memory[address];
} // scale index mode

int Registers::stringToRegNum(char* str)
{
  int regN;
  char regNames[6][7] = {"eax", "ebp", "esp", "eip", "edx", "flags"};
  for(regN = eax; regN <= flags; regN++)
    if(strstr(str, regNames[regN]))
      break;
  return regN;
} // string-> regNum
