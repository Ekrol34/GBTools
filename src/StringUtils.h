#ifndef SUTILS_H
#define SUTILS_H

#include "Arduino.h"

namespace gb
{
    String* split(String str, char c, unsigned int& length);

    String* split(String str, String sep, unsigned int& length);

    String* split(String str, char c);

    void replaceInPlace(String &text, const String &target, const String &rep);

    String replaceCopy(const String text, const String &target, const String &rep);

    String* extractBetweenChars(const String &text, char c, unsigned int &length);

    bool isInt(const String& s);

    bool isFloat(const String& s);

    bool isString(const String& s);

    void replaceInPlaceSafe(String &text, const String &target, const String &rep, char guard);

    String replaceCopySafe(const String text, const String &target, const String &rep, char guard);

    void popFirst(String& str);

    void popLast(String& str);

    String* splitBetween(String text, String startToken, String endToken, unsigned int& length, bool singleRange = false);

}

#endif