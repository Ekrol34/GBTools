#include "GBStringUtils.h"

GBString* gb::__split(GBString str, char c, unsigned int& length)
{
    const size_t slices = str.count(c) + 1;
    GBString* array = new GBString[slices];

    size_t count = 0;

    for(size_t i = 0; i < str.length(); i++)
    {
        if(str.charAt(i) == c)
        {
            count++;
            continue;
        }

        array[count] += str.charAt(i);
    }

    length = count + 1;

    return array;
}


GBString* gb::__split(GBString str, GBString sep, unsigned int& length)
{
    const size_t slices = str.count(sep.get_c()) + 1;
    GBString* array = new GBString[slices];

    GBString aux = "";
    int cont = 0;

    for(int i = 0; i < str.length(); i++)
    {
        aux += str.charAt(i);

        if(aux.count(sep.get_c()) == 1)
        {
            aux.replace(sep.get_c(), "");
            array[cont] = aux;
            cont++;

            aux = "";
        }
    }

    array[cont] = aux;

    length = cont + 1;

    return array;
}

GBString* gb::__split(GBString str, char c)
{
    unsigned int dummy;
    return __split(str, c, dummy);
}

void gb::__replaceInPlace(GBString &text, const GBString &target, const GBString &rep) 
{
  if (target.length() == 0) return;

  text.replace(target.get(), rep.get());
}

GBString gb::__replaceCopy(const GBString text, const GBString &target, const GBString &rep) 
{
  if (target.length() == 0) return text;

  GBString copy = text;
  copy.replace(target.get(), rep.get());
  return copy;
}

GBString* gb::__extractBetweenChars(const GBString &text, char c, unsigned int &length)
{
    int size = 0;
    bool open = false;

    for(int i = 0; i < text.length(); i++)
    {
        if(text.charAt(i) == c)
        {
            if(!open) open = true;
            else
            {
                size++;
                open = false;
            }
        }
    }

    length = size == 0 ? 1 : size;

    GBString* result = new GBString[length];

    if(size == 0)
    {
        result[0] = text;
        return result;
    }

    GBString aux = "";
    open = false;
    size = 0;

    for(int i = 0; i < text.length(); i++)
    {
        if(text.charAt(i) == c)
        {
            if(!open) open = true;
            else
            {
                open = false;

                for(int j = 0; j < aux.length(); j++) result[size] += aux.charAt(j);
                
                aux = "";
                size++;
            }

            continue;
        }

        if(open) aux += text.charAt(i);
    }

    return result;
}

bool gb::__isString(const GBString& s) 
{
    if (s.length() < 2) return false;

    char first = s[0];
    char last  = s[s.length() - 1];

    if ((first == '"' && last == '"') ||
        (first == '\'' && last == '\'')) {
        return true;
    }

    return false;
}

void gb::__replaceInPlaceSafe(GBString &text, const GBString &target, const GBString &rep, char guard)
{
    if (target.length() == 0) return;

    GBString result = "";
    bool protectedZone = false;

    for (int i = 0; i < text.length(); )
    {
        char c = text.charAt(i);

        if (c == guard)
        {
            protectedZone = !protectedZone;
            result += c;
            i++;
            continue;
        }

        if (!protectedZone && text.startsWith(target.get_c(), i))
        {
            result += rep.get_c();
            i += target.length();
        }
        else
        {
            result += c;
            i++;
        }
    }

    text = result;
}

// GBString gb::__replaceCopySafe(const GBString text, const GBString &target, const GBString &rep, char guard)
// {
//     if (target.length() == 0) return text;

//     GBString result = "";
//     bool protectedZone = false;

//     for (int i = 0; i < text.length(); )
//     {
//         char c = text.charAt(i);

//         if (c == guard)
//         {
//             protectedZone = !protectedZone;
//             result += c;
//             i++;
//             continue;
//         }

//         if (!protectedZone && text.startsWith(target.get_c(), i))
//         {
//             result += rep.get_c();
//             i += target.length();
//         }
//         else
//         {
//             result += c;
//             i++;
//         }
//     }

//     return result;
// }

GBString* gb::__splitBetween(GBString text, GBString startToken, GBString endToken, unsigned int& length, bool singleRange)
{
    if (singleRange)
    {
        int start = text.indexOf(startToken.get_c(), 0);
        if (start == -1)
        {
            length = 0;
            return nullptr;
        }

        int contentStart = start + startToken.length();
        int end = text.lastIndexOf(endToken.get_c());

        length = 1;
        GBString* result = new GBString[1];

        if (end == -1 || end < contentStart)
        {
            result[0] = text.substring(contentStart);
        }
        else
        {
            result[0] = text.substring(contentStart, end - contentStart);
        }

        return result;
    }

    length = 0;
    int position = 0;

    while (true)
    {
        int start = text.indexOf(startToken.get_c(), position);
        if (start == -1) break;

        int searchFrom = start + startToken.length();
        int end = text.indexOf(endToken.get_c(), searchFrom);

        length++;
        position = (end == -1)
            ? text.length()
            : end + endToken.length();
    }

    if (length == 0) return nullptr;

    GBString* result = new GBString[length];

    position = 0;
    for (unsigned int i = 0; i < length; ++i)
    {
        int start = text.indexOf(startToken.get_c(), position);
        if (start == -1) break;

        int contentStart = start + startToken.length();
        int end = text.indexOf(endToken.get_c(), contentStart);

        if (end == -1)
        {
            result[i] = text.substring(contentStart);
            position = text.length();
        }
        else
        {
            result[i] = text.substring(contentStart, end - contentStart);
            position = end + endToken.length();
        }
    }

    return result;
}
