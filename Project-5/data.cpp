#include "data.h"
#include "word.h"

Data::Data(int addr):Word(addr)
{
} // Data contructor

int Data::operator=(int n)
{
  num = n;
  return num;
} // assignment operator

const int& Data::get() const
{
  return num;
} //const get()

int& Data::get()
{
  return num;
} //get()
