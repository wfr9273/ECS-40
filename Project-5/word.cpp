#include <cstring>
#include "word.h"

Word::Word(int addr)
{
  address = addr;
} //constructor

Word::~Word(){}

bool Word::operator<(const Word &w) const
{
  return (address - w.address < 0);
} //operator <
