/*
 * StringFunction.c
 *
 *  Created on: 27 Jan 2020
 *      Author: Tatjana
 */
#include "AS7261Sensor/StringFunction.h"


char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}

void ClearSpace(char* String)
{
	int Size=strlen(String);
	int i=0,k=0;

	for(i=0;i<Size;i++)
	{
		if(String[i]==' ')
			{
				for(k=i;k<(Size-1);k++)
				{
					String[k]=String[k+1];

				}
				i=0;
				String[Size-1]='\0';
			}
	}
}

void DelateOKinMSG (char *RecPoruka)
{
	RecPoruka[strlen(RecPoruka)-1]='\0'; // /r
	RecPoruka[strlen(RecPoruka)-1]='\0'; // K
	RecPoruka[strlen(RecPoruka)-1]=' '; // O
}
void DelateOKinMSGPlus (char *String)
{
	int Size = strlen(String);
	int i;

	for(i=0;i<(Size-3);i++)
		{
			if(String[i]=='O' && String[i+1]=='K' && String[i+2]=='\r')
				{
				String[i]='\0';
				String[i+1]='\0';
				String[i+2]='\0';
				}

		}
}
void ChangeCom(char* String)
{
	int len=strlen(String);
	int i=0;

	for(i=0;i<len;i++)
	{
		if(String[i]==',' || String[i]=='.')
		{
			String[i]=' ';
		}
	}
}
