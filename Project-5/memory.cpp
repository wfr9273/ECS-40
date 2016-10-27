#include <iostream>
#include <cstdlib>
#include <cstring>
#include "word.h"
#include "memory.h"
#include "data.h"
#include "registers.h"
#include "instruction.h"

using namespace std;

ListNode::ListNode(Word *w, ListNode *n)
{
  word = w;
  next = n;
} //ListNode constructor

ListNode::~ListNode()
{
  if (word)
    delete word;
} //ListNode destructor

Memory::Memory()
{
  head = NULL;
} //Memory constructor

Memory::~Memory()
{
  ListNode *ptr;
  
  for (ptr = head; ptr; ptr = head)
  {
    head = ptr->next;
    delete ptr;
  } //for loop
} //Memory destructor

const Word& Memory::operator[](int addr) const
{
  Word w(addr);
  //cout << addr << endl;
  ListNode *ptr;
  
  for (ptr = head; ptr; ptr = ptr->next)
  {
    if (!(w < *(ptr->word)) && !(*(ptr->word) < w))
      return *(ptr->word);
  } //for loop
      
  cout << "Seg fault at address: <" << addr << ">" << endl;
  exit(1);
} // const []

void Memory::insert(Word *w)
{
  ListNode *ptr, *prev = NULL;
  ptr = head;

  while (ptr && *(ptr->word) < *w)
  {
    prev = ptr;
    ptr = ptr->next;
  } //while

  if (prev) // not first node
    prev->next = new ListNode(w, ptr);

  else // first node
    head = new ListNode(w, ptr);
} //insert()

Word& Memory::operator[](int addr)
{
  Word w(addr);
  ListNode *ptr;
  for (ptr = head; ptr; ptr = ptr->next)
  {
    if (!(w < *(ptr->word)) && !(*(ptr->word) < w))
      return *(ptr->word);
  } //for loop
  Data *d = new Data(addr);
  insert(d);
  return *d;
} // non-const []


const Instruction& Memory::fetch(Registers* registers)
{
  Word *word = &(*this)[registers->get(Registers::eip)];
  registers->set(Registers::eip, registers->get(Registers::eip) + 4);
  return *dynamic_cast<Instruction*>(word);
} // fetch()

istream& operator>> (istream &is, Memory &memory)
{
  char line[256], *ptr;
  int address = 100;
  
  while(is.getline(line, 256))
  {
    for(ptr = strchr(line, '\t'); ptr; ptr = strchr(line, '\t'))
      *ptr = ' ';  // replace all tabs with space characters
    
    for(ptr = line; *ptr == ' '; ptr++);  // get past leading spaces
    
    if(*ptr != '.' && *ptr != '_' && !strstr(line, "main:") && *ptr != 'f')
    {
      Instruction *instru = new Instruction(address);
      *instru = ptr;
      //Word *w = dynamic_cast<Word*>(&instru);
      memory.insert(instru);
      address += 4;
    } // if not directive, nor main:
  }  // while more in file
  
  return is;
}  // operator>>



