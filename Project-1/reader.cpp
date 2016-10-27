#include "instruction.h"
#include "reader.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int readcommand(FILE* file, Reader *reader)
{

int line_count=0;
char buffer[500];
int buffer_count=0;
int address_count=100;


while((fgets(buffer,501,file))!=NULL)
{
    while(buffer[buffer_count]!='\0')
    {
        if (buffer[buffer_count]=='\t')
        {
            buffer[buffer_count++]=' ';
            continue;
        }
        else if (buffer[buffer_count]=='\n')
        {
            buffer[buffer_count]='\0';
            buffer_count=0;
            break;
        }
        else if ((buffer[buffer_count]=='.') | (buffer[buffer_count]==':'))
        {
            buffer[0]='\0';
            buffer_count=0;
            break;
        }
        else
        {
            buffer_count++;
            continue;
        }
    }

    if (buffer[0]!='\0')
    {
        reader->lines[line_count].address=address_count;
        reader->lines[line_count].info=(char *)malloc(strlen(buffer)*sizeof(char));
        strcpy(reader->lines[line_count].info,buffer);
        line_count++;
        address_count+=4;
    }

}

return line_count;
}
