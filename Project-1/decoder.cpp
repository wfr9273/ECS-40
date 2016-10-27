#include "decoder.h"
#include "registers.h"

void addl(int *op1,int *op2){
  int a,b;
  a=*op1;
  b=*op2;
  b+=a;
  *op2=b;
}

void subl(int *op1,int *op2){
  int c,d;
  c=*op1;
  d=*op2;
  d=c-d;
  *op2=d;
}

void andl(int *op1,int *op2){
  int e,f;
  e=*op1;
  f=*op2;
  f=e&f;
  *op2=f;
}

void movl(int *op1,int *op2){
  *op2=*op1;
}

void pushl(int *op1,Registers *registers, int memory[]){
  registers->regs[esp]-=4;
  memory[registers->regs[esp]]=*op1;
}

void leave(Registers *registers, int memory[]){
  registers->regs[esp]=registers->regs[ebp];
  registers->regs[ebp]=memory[registers->regs[esp]];
  registers->regs[esp]+=4;
}

void ret(Registers *registers, int memory[]){
  registers->regs[eip]=memory[registers->regs[esp]];
  registers->regs[esp]+=4;
}
