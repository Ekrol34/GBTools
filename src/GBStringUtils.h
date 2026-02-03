#ifndef GBUTILS_H
#define GBUTILS_H

#include "Arduino.h"
#include "GBString.h"

namespace gb
{
    GBString* __split(GBString str, char c, unsigned int& length);

    GBString* __split(GBString str, GBString sep, unsigned int& length);

    GBString* __split(GBString str, char c);

    void __replaceInPlace(GBString &text, const GBString &target, const GBString &rep);

    GBString __replaceCopy(const GBString text, const GBString &target, const GBString &rep);

    GBString* __extractBetweenChars(const GBString &text, char c, unsigned int &length);

    bool __isString(const GBString& s);

    void __replaceInPlaceSafe(GBString &text, const GBString &target, const GBString &rep, char guard);

    // GBString __replaceCopySafe(const GBString text, const GBString &target, const GBString &rep, char guard);

    GBString* __splitBetween(GBString text, GBString startToken, GBString endToken, unsigned int& length, bool singleRange = false);

}

#endif