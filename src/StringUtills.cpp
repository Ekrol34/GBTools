#include "StringUtils.h"

String* gb::split(String str, char c, unsigned int& length)
{
    if (str.indexOf(c) == -1)
    {
        length = 1;
        String* result = new String[1];
        result[0] = str;
        return result;
    }

    length = 1;
    for (int i = 0; i < str.length(); i++)
    {
        if (str.charAt(i) == c)
            length++;
    }

    String* result = new String[length];
    int substr_index = 0;
    String aux = "";

    for (int i = 0; i < str.length(); i++)
    {
        if (str.charAt(i) == c)
        {
            result[substr_index++] = aux;
            aux = "";
        }
        else
        {
            aux += str[i];
        }
    }

    result[substr_index] = aux;
    return result;
}


String* gb::split(String str, String sep, unsigned int& length)
{
    length = 1;
    int pos = 0;

    while ((pos = str.indexOf(sep, pos)) != -1)
    {
        length++;
        pos += sep.length();
    }

    String* result = new String[length];

    int start = 0;
    int index = 0;
    int sepPos;

    while ((sepPos = str.indexOf(sep, start)) != -1)
    {
        result[index++] = str.substring(start, sepPos);
        start = sepPos + sep.length();
    }

    result[index] = str.substring(start);

    return result;
}

String* gb::split(String str, char c)
{
    unsigned int dummy;
    return split(str, c, dummy);
}

void gb::replaceInPlace(String &text, const String &target, const String &rep) 
{
  if (target.length() == 0) return;

  text.replace(target, rep);
}

String gb::replaceCopy(const String text, const String &target, const String &rep) 
{
  if (target.length() == 0) return text;

  String copy = text;
  copy.replace(target, rep);
  return copy;
}

String* gb::extractBetweenChars(const String &text, char c, unsigned int &length)
{
    length = 0;

    bool open = false;
    for (unsigned int i = 0; i < text.length(); i++)
    {
        if (text.charAt(i) == c)
        {
            if (!open)
                open = true;
            else
            {
                length++;
                open = false;
            }
        }
    }

    if (length == 0)
        return nullptr;

    String* result = new String[length];

    unsigned int index = 0;
    open = false;
    String aux = "";

    for (unsigned int i = 0; i < text.length(); i++)
    {
        char ch = text.charAt(i);

        if (ch == c)
        {
            if (!open)
            {
                open = true;
                aux = "";
                aux += c;  
            }
            else
            {
                aux += c;  
                result[index++] = aux;
                aux = "";
                open = false;
            }
        }
        else if (open)
        {
            aux += ch;
        }
    }

    return result;
}

bool gb::isInt(const String& s) 
{
    if (s.length() == 0) return false;

    int start = 0;
    if (s[0] == '-') 
    {
        if (s.length() == 1) return false;
        start = 1;
    }

    for (int i = start; i < s.length(); i++) 
    {
        if (!isDigit(s[i])) 
        {
            return false;
        }
    }
    return true;
}

bool gb::isFloat(const String& s) 
{
    if (s.length() == 0) return false;

    bool punto = false;
    int start = 0;

    if (s[0] == '-') 
    {
        if (s.length() == 1) return false;
        start = 1;
    }

    for (int i = start; i < s.length(); i++) 
    {
        if (s[i] == '.') 
        {
            if (punto) return false; 
            punto = true;
        } 
        else if (!isDigit(s[i])) 
        {
            return false;
        }
    }
    return true;
}

bool gb::isString(const String& s) 
{
    if (s.length() < 2) return false;

    char first = s[0];
    char last  = s[s.length() - 1];

    // Debe empezar y terminar con la misma comilla
    if ((first == '"' && last == '"') ||
        (first == '\'' && last == '\'')) {
        return true;
    }

    return false;
}

void gb::replaceInPlaceSafe(String &text, const String &target, const String &rep, char guard)
{
    if (target.length() == 0) return;

    String result = "";
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

        if (!protectedZone && text.startsWith(target, i))
        {
            result += rep;
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

String gb::replaceCopySafe(const String text, const String &target, const String &rep, char guard)
{
    if (target.length() == 0) return text;

    String result = "";
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

        if (!protectedZone && text.startsWith(target, i))
        {
            result += rep;
            i += target.length();
        }
        else
        {
            result += c;
            i++;
        }
    }

    return result;
}

void gb::popFirst(String& str)
{
    if (str.length() == 0) return;
    str.remove(0, 1);
}

void gb::popLast(String& str)
{
    int len = str.length();
    if (len == 0) return;
    str.remove(len - 1, 1);
}

String* gb::splitBetween(String text, String startToken, String endToken, unsigned int& length, bool singleRange)
{
    if (singleRange)
    {
        int start = text.indexOf(startToken);
        if (start == -1)
        {
            length = 0;
            return nullptr;
        }

        int contentStart = start + startToken.length();
        int end = text.lastIndexOf(endToken);

        length = 1;
        String* result = new String[1];

        if (end == -1 || end < contentStart)
        {
            result[0] = text.substring(contentStart);
        }
        else
        {
            result[0] = text.substring(contentStart, end);
        }

        return result;
    }

    length = 0;
    int position = 0;

    while (true)
    {
        int start = text.indexOf(startToken, position);
        if (start == -1) break;

        int searchFrom = start + startToken.length();
        int end = text.indexOf(endToken, searchFrom);

        length++;
        position = (end == -1) ? text.length() : end + endToken.length();
    }

    if (length == 0)
        return nullptr;

    String* result = new String[length];

    position = 0;
    for (unsigned int i = 0; i < length; ++i)
    {
        int start = text.indexOf(startToken, position);
        if (start == -1) break;

        int contentStart = start + startToken.length();
        int end = text.indexOf(endToken, contentStart);

        if (end == -1)
        {
            result[i] = text.substring(contentStart);
            position = text.length();
        }
        else
        {
            result[i] = text.substring(contentStart, end);
            position = end + endToken.length();
        }
    }

    return result;
}
