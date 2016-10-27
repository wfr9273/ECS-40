#ifndef DATA_H
#define	DATA_H
#include "word.h"

class Data : public Word
{
  int num;

public:
  Data(int addr);
  const int& get() const;
  int& get();
  int operator=(int n);
}; //class Data
#endif	// DATA_H
