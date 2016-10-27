#include <map>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "pager.h"
#include "indexpager.h"

using namespace std;

void IndexPager::read(istream &in)
{
  string s;
  int wordKey = 0, line_count = 0;

  while(getline(in, s, '\n')) 
  {
    string word = "";
    
    for (string::iterator it = s.begin(); it != s.end(); it++)
    {
      if (isalpha(*it)) // if is alpha
        word += *it;
      else // if not alpha
      {
        insert(word, line_count, &wordKey);
        word = "";
      } // else
    } // for loop
    
    if (word != "") // if word is last
      insert(word, line_count, &wordKey);
    
    line_count++;
  } // while looop
  
  form_vector();
}  // read()

void IndexPager::insert(string word, int line_count, int* wordKey)
{
  map<string, int>::iterator itA = WordToInt.find(word);
		  
  if (itA != WordToInt.end()) // if exist
    WordKeyToLineNumber.insert(
               multimap<int, int>::value_type(itA->second, line_count));
  else // not exist
  {
    WordToInt.insert(map<string, int>::value_type(word, *wordKey));
    WordKeyToLineNumber.insert(
                  multimap<int, int>::value_type(*wordKey, line_count));
    (*wordKey)++;
  } // else
} // insert()

void IndexPager::form_vector()
{
  string line = "";
  int i, temp = -10, temp1 = -10;
  bool con_flag = false;

  for (map<string, int>::iterator it = WordToInt.begin();
                                  it != WordToInt.end(); it++)
  {

   if (it->first != "")
   {
     line += it->first + ' ';
     i = it->second;
   } // if not empty
   else // empty
     continue;
    
    help(line, i, temp, temp1, con_flag);   
    line += '.';
    text.push_back(line);
    line = "";
  } // for each word
} // formvector()

void IndexPager::help(string& line, int i, int temp, int temp1, bool con_flag)
{
  multimap<int, int>::iterator itA = WordKeyToLineNumber.find(i);
    
  for (unsigned int j = 0; j < WordKeyToLineNumber.count(i); j++, itA++)
  {
    if (temp == -10) // first one
      line += intToString(itA->second);
        
    else // not first one
    {
      if (itA->second - temp != 1 && itA->second - temp != 0)
      {
        if (con_flag) // if have consecutive line before
        {
          if (temp != temp1) // if consecutive not same line
            line += '-' + intToString(temp);
            
          line += ", " + intToString(itA->second);
          con_flag = false;
          temp1 = -10;
        } // if
        else // if not have consecutive line before
          line += ", " + intToString(itA->second);
      } // if not consecutive
      else // consecutive line
      {
        int a = help1(line, j, i, itA, temp, &con_flag, &temp1);
		
        if (a == 1)
          continue;      
      } // else
    } // not first one
      
    temp = itA->second;
  } // for multimap
} // help()

int IndexPager::help1(string& line, unsigned int j, int i,
                      multimap<int, int>::iterator itA,
                      int temp, bool* con_flag, int* temp1)
{
  if (j == WordKeyToLineNumber.count(i) - 1)
  {
    if (itA->second - temp != 0)
    {
      line += '-' + intToString(itA->second);
      return 1;
    } // if not same line
  } // if last line number
          
  if (!(*con_flag)) // first consecutive line number
    *temp1 = temp;
		    
  *con_flag = true;
  return 0;
} // help1()
