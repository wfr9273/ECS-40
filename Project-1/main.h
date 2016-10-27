#include "registers.h"
#ifndef MAIN_H
#define MAIN_H
enum {eax, ebp, esp, eip};
#endif // Main
int *address(Registers *registers, char *ptr, int memory[]);
