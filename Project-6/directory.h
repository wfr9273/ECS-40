#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "list.h"

class File
{
protected:
  char* name;

public:
  File(char* nam);
  const char* getName() const;

  virtual ~File();
  virtual bool find(File* f);
  virtual void insert(File* f);
  virtual bool operator==(const File& f);
  virtual bool operator<(const File& f);
  virtual bool operator>(const File& f);
}; // class File

class Directory : public File
{
  List<File*> files;

public:
  Directory(char* name);
  ~Directory();
  bool find(File* f);
  void insert(File* list);
  bool operator==(const File& f);
  bool operator<(const File& f);
  bool operator>(const File& f); 
}; // class Directory

#endif // DIRECTORY_H
