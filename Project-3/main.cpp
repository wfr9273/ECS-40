// Author: Leo & Olivia

#include "registers.h"
#include "instruction.h"
#include "decoder.h"
#include "reader.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main(int argc, char* argv[])
{
  Reader reader;
  Decoder decoder;
  Registers registers;
  Instruction instruction;
  int memory [1001];
  registers.initialize(memory);
  reader.read(&registers, argv[1]);
  
  while(registers.get(eip) != 0)
  {
    reader.fetch(&instruction, &registers);
    decoder.parse(&instruction, &registers, memory);
    decoder.execute(&registers, memory);
    registers.print(instruction.getInfo());
  } // while eip not zero

  return 0;
}  // main()

