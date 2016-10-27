// Author: Leo & Olivia

#include "registers.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstring>

using namespace std;

void Registers::initialize(int memory[1001])
{
  regs[esp] = 1000;
  regs[ebp] = 996;
  regs[eip] = 100;
  regs[eax] = 0;
  memory[1000] = 0;
}  // initialize()

void Registers::print(const char *instruction) const
{
  cout << setw(20) << left << instruction << " eip: " 
  << setw(3) << right << regs[eip] << " eax: " << setw(3) 
  << right << regs[eax] << " ebp: " << setw(3) << right
  << regs[ebp] << " esp: " << setw(3) << right << regs[esp] << endl;
}  // print()

int* Registers::address(char *operand, int memory[])
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
      default: return 0;
  } //switch
} //get
    
void Registers::set(RegName rn, int nNewValue)
{ 
    regs[rn] = nNewValue; 
} //set
