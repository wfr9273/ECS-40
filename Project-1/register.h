#ifndef REGISTERS_H
#define REGISTERS_H
typedef struct
{
    int regs[4];
}Registers;
#endif // Registers

void initialize(Registers *registers);
