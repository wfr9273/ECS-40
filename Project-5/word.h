#ifndef WORD_H
#define	WORD_H

class Word
{
  int address;

public:
  Word(int addr);
  virtual ~Word();
  bool operator<(const Word &word) const;
}; //class word
#endif	// WORD_H
