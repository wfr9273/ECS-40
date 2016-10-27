#include "registers.h"
#include "main.h"

void initialize(Registers *registers)
{
    registers->regs[esp]=1000;
    registers->regs[ebp]=0;
    registers->regs[eip]=100;
    registers->regs[eax]=0;
}
