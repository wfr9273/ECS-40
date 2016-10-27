#ifndef REGISTERS_H
#define	REGISTERS_H
// Author: Leo & Olivia

typedef enum {eax, ebp, esp, eip} RegName;

class Registers 
{ 
  int regs[4];
  
  public:
    int* address(char *ptr, int memory[]);
    void initialize(int memory[1001]);
    void print(const char *instruction) const;
    int get(int number) const;
    void set(RegName rn, int nNewValue);
}; //class

#endif	// REGISTERS_H 

