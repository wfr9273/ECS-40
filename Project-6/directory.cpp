#include <iostream>
#include <cstring>
#include "directory.h"
#include "list.h"

using namespace std;

File::File(char* nam)
{
  name = new char[strlen(nam) + 1];
  strcpy(name, nam);
} // File constructor

const char* File::getName() const
{
  return name;
} // getName()

File::~File()
{
  if (name)
    delete name;
} // File destructor

void File::insert(File* f)
{
} // insert()

bool File::find(File* f)
{
  cout << name << endl;
  return true;
} // find()

bool File::operator==(const File& f)
{
  if (strcmp(name, f.name) == 0)
    return true;
  return false;
} // operator ==

bool File::operator<(const File& f)
{
  if (strcmp(name, f.name) < 0)
    return true;
  return false;
} // operator <

bool File::operator>(const File& f)
{
  if (strcmp(name, f.name) > 0)
    return true;
  return false;
} // operator >

Directory::Directory(char* nam) : File(nam)
{
} // constructor

Directory::~Directory()
{
} // Destructor

bool Directory::find(File* f)
{
  if (strcmp(name, f->getName()) == 0)
  {
    files.print();
    return true;
  } // if exact match
  else  // not exact match
    return files.find(f);
} // find()

void Directory::insert(File* f)
{
  if (strcmp(name, f->getName()) == 0) // if directory name is exactly same
    return;
  files.insert(f);
} // insert()

bool Directory::operator==(const File& f)
{
  int size = strlen(name);
  const char* c = f.getName();

  if ((strncmp(name, c, size) == 0) &&
      (c[size] == '/' || c[size] == '\0')) // if match
      return true;

  return false;
} // operator ==

bool Directory::operator<(const File& f)
{
  int size = strlen(name);
  const char* c = f.getName();

  if(strncmp(name, c, size) < 0)
    return true;

  if(strncmp(name, c, size) == 0 && c[size] != '/' && c[size] != '\0')
    return true;

  return false;
} // operator <

bool Directory::operator>(const File& f)
{
 int size = strlen(name);
  const char* c = f.getName();
  return(strncmp(name, c, size) > 0);
} // operator >
