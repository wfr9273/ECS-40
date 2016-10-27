// Author: Leo & Olivia
#include <cstring>
#include "instruction.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int Instruction::getAddress() const
{
    return address;
}//getAddress
	
char* Instruction::getInfo() const
{
    return info;
} //getInfo
	
void Instruction::setInfo(const char* p)
{
    info = new char[strlen(p) + 1];
    strcpy(info, p);
} //setInfo
	
void Instruction::setAddress(int a)
{
    address = a;
} //setAddress

Instruction::Instruction():info(NULL){};

Instruction::~Instruction()
{
		
    if(info != NULL)
    {
        delete []info;
    } // if
}; // destructor

