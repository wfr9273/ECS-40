#ifndef MEMORY_H
#define	MEMORY_H

#include "word.h"
#include "instruction.h"

class Registers;
class Memory;
using namespace std;

class ListNode
{
  Word *word;
  ListNode *next;
  ListNode(Word *w, ListNode *n);
  ~ListNode();
  friend class Memory;
}; //class ListNode


class Memory 
{
  ListNode *head;

public:
  Memory();
  ~Memory();
  const Word& operator[](int addr) const;
  Word& operator[](int addr);
  void insert(Word *w);
  const Instruction& fetch(Registers* registers);
  friend istream& operator>> (istream &is, Memory &memory);
}; // class Memory
#endif	// MEMORY_H
