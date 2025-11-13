#include "GBStringUtils.h"

String* gb::Split(String str, char c, unsigned int& length)
{
    length = 1;

    for(int i = 0; i < str.length(); i++)
    {
        if(str.charAt(i) == c) 
        {
            length++;
        }
    }

    String* result = new String[length];
    int substr_index = 0;
    String aux = "";

    for(int i = 0; i < str.length(); i++)
    {
        if(str.charAt(i) == c)
        {
            result[substr_index] = aux;
            substr_index++;
            aux = "";
            continue;
        }

        aux += str[i];
    }

    result[substr_index] = aux;

    return result;
}