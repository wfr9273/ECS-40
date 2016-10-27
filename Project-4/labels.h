#ifndef LABELS_H
#define	LABELS_H

#include "instruction.h"

class Labels{
	Instruction array[100];
	int count;
	
	public:
	friend ifstream &operator>>(ifstream& input, Labels& labels);
	int find(char *s);	
};
#endif
