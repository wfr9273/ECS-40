#ifndef INDEXPAGER_H
#define INDEXPAGER_H

#include <iostream>
#include <map>
#include <string>
#include "pager.h"

class IndexPager : Pager
{
  map<string, int> WordToInt;
  multimap<int, int> WordKeyToLineNumber;
public:
  void read(istream &in);
  void form_vector();
  void insert(string word, int line_count, int* wordKey);
  void help(string& line, int i, int temp, int temp1, bool con_flag);
  int help1(string& line, unsigned int j, int i,
            multimap<int, int>::iterator itA,
            int temp, bool* con_flag, int* temp1);

}; // class IndexPager

#endif
