#include <iostream>
#include <fstream>
#include <cstring>
#include "list.h"
#include "directory.h"

using namespace std;

void read(const char* name, List<File*>& list)
{
  ifstream f(name);
  char* line = new char[1000];
  char *p;
  
  while (f.getline(line, 1000) != NULL){
    p = strrchr(line, ' ');
    p++;

    if (line[0] == 'd')
    {
      File *d = new Directory(p);
      list.insert(d);
    } // if directory
    else
    {
	  File* fp = new File(p);
	  list.insert(fp);
    } // if not directory
  }
  delete []line;
} // read()


int main(int argc, char* argv[])
{
  List<File*> list;
  char *n;
  n = new char[1000];
  read(argv[1], list);
  while(true)
  {
    cout << "Please enter a file name (Done = exit): ";
    cin >> n;
    if (strcmp(n, "Done") == 0)
      break;
    File* newfile = new File(n);
    if (!list.find(newfile))
      cout << "Not found." << endl;
  }

  return 0;
}


