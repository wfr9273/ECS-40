#include "registers.h"
#include "instruction.h"
#include "decoder.h"
#include "reader.h"
#include "labels.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

int Labels::find(char *s)
{
	int i;
	for (i = 0; i < 100; i++)
	{
	  if(strstr(array[i].getInfo(), s))
	    break;	
	}
	return array[i].getAddress();
}

ifstream &operator>>(ifstream& input, Labels& labels)
{
  char line[256], *ptr;
  int address = 100;
  input.seekg(0, input.beg);
  labels.count = 0;
  while(input.getline(line, 256, '\n') != NULL)
  {
	for(ptr = strchr(line, '\t'); ptr; ptr = strchr(line, '\t'))
      *ptr = ' ';  // replace all tabs with space characters
      
    if((ptr = strchr(line, '\n')) != NULL)
      *ptr = '\0';  // eliminate \n;
    
    for(ptr = line; *ptr == ' '; ptr++);  // get past leading spaces
    
    if(strstr(line, "main:"))
    {
      labels.array[labels.count].setAddress(address);
      labels.array[labels.count++].setInfo(ptr);
    } //label "main:"
    else
    {
      if(*ptr != '.' && *ptr != '_')
        address += 4;

      else if((line[0] == '.' && line[1] == 'L') || line[0] == '_')
      {
	    if((ptr = strchr(line, ':')) != NULL)
	      *ptr = '\0';
	      
	    ptr = line;
	    labels.array[labels.count].setAddress(address);
        labels.array[labels.count++].setInfo(ptr);
      } //directive
    }
  } // while more in file
  return input;
} // read()
