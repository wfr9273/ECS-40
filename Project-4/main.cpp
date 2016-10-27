// Author: Leo & Olivia

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "registers.h"
#include "instruction.h"
#include "decoder.h"
#include "reader.h"
#include "labels.h"


using namespace std;

int main(int argc, char* argv[])
{
  Reader reader;
  Decoder decoder;
  Registers registers;
  Instruction instruction;
  Labels labels;
  int memory [1001];
  memory[1000] = 0;
  ifstream inf(argv[1]);
  inf >> reader;
  inf >> labels;
  char *s, buffer[10] = "main:";
  s = buffer;
  registers.set(Registers::eip, labels.find(s));

  while(registers.get(Registers::eip) != 0)
  {
    reader.fetch(&instruction, &registers);
    decoder.parse(&instruction, &registers, memory, &labels);
    decoder.execute(&registers, memory, &instruction);
    cout << setw(20) << left << instruction.getInfo() << registers;
  } // while eip not zero

  return 0;
}  // main()
