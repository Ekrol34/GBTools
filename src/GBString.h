#ifndef GBSTRING_H
#define GBSTRING_H

#include "Arduino.h"

struct GBString
{
    static constexpr size_t CAPACITY = 256;

    char buf[CAPACITY];
    const char* ptr;
    size_t len;

    GBString() : ptr(buf), len(0)
    {
        buf[0] = '\0';
    }

    GBString(const char* s) : ptr(buf)
    {
        if (!s)
        {
            len = 0;
            buf[0] = '\0';
            return;
        }

        len = strlen(s);
        if (len >= CAPACITY) len = CAPACITY - 1;
        memcpy(buf, s, len);
        buf[len] = '\0';
    }

    GBString(const char* s, size_t l) : ptr(buf)
    {
        if (!s)
        {
            len = 0;
            buf[0] = '\0';
            return;
        }

        len = (l >= CAPACITY) ? CAPACITY - 1 : l;
        memcpy(buf, s, len);
        buf[len] = '\0';
    }

    GBString(const String& s) : ptr(buf)
    {
        len = s.length();
        if (len >= CAPACITY) len = CAPACITY - 1;
        memcpy(buf, s.c_str(), len);
        buf[len] = '\0';
    }

    size_t length() const { return len; }
    bool empty() const { return len == 0; }
    const char* get() const { return ptr; }

    const char* c_str() const
    {
        return ptr;
    }

    String toString() const { return String(ptr); }

    const char* get_c() const 
    { 
        // Tamaño máximo de string que esperamos manejar 
        constexpr size_t MAX_SIZE = 256; 

        // buffer estático por defecto 
        static char buffer[MAX_SIZE]; if (!ptr || len == 0) 
        { 
            buffer[0] = '\0'; 
            return buffer; 
        } 
        
        // copia solo hasta el máximo permitido 
        size_t n = (len < MAX_SIZE - 1) ? len : MAX_SIZE - 1; 
        memcpy(buffer, ptr, n); 
        buffer[n] = '\0'; 
        
        return buffer; 
    }

    char charAt(size_t index) const
    {
        return (index < len) ? ptr[index] : '\0';
    }

    size_t count(char c) const
    {
        size_t cnt = 0;
        for (size_t i = 0; i < len; i++)
        {
            if (ptr[i] == c)
                cnt++;
        }
        return cnt;
    }

    char operator[](size_t i) const
    {
        return (i < len) ? ptr[i] : '\0';
    }

    // ---- Concatenación ----

    GBString& operator+=(char c)
    {
        if (len + 1 >= CAPACITY)
            return *this;

        buf[len++] = c;
        buf[len] = '\0';
        ptr = buf;
        return *this;
    }

    GBString& operator+=(const char* s)
    {
        if (!s) return *this;

        size_t n = strlen(s);
        size_t space = CAPACITY - 1 - len;
        if (n > space) n = space;

        memcpy(buf + len, s, n);
        len += n;
        buf[len] = '\0';
        ptr = buf;
        return *this;
    }

    bool equals(const char* s) const
    {
        if (!s) return false;
        return strlen(s) == len && memcmp(ptr, s, len) == 0;
    }

    bool equals(const GBString& other) const
    {
        return len == other.len && memcmp(ptr, other.ptr, len) == 0;
    }

    bool operator==(const GBString& other) const { return equals(other); }
    bool operator==(const char* s) const { return equals(s); }
    bool operator==(const String& s) const
    {
        return len == s.length() && memcmp(ptr, s.c_str(), len) == 0;
    }

    bool operator!=(const GBString& other) const { return !equals(other); }
    bool operator!=(const char* s) const { return !equals(s); }
    bool operator!=(const String& s) const { return !(*this == s); }

    bool startsWith(const char* prefix) const
    {
        if (!prefix) return false;

        size_t n = strlen(prefix);
        if (n > len) return false;

        return memcmp(ptr, prefix, n) == 0;
    }

    bool startsWith(const char* prefix, size_t offset) const
    {
        if (!prefix || offset > len) return false;

        size_t n = strlen(prefix);
        if (offset + n > len) return false;

        return memcmp(ptr + offset, prefix, n) == 0;
    }

    GBString substring(size_t pos, size_t n = SIZE_MAX) const
    {
        if (pos >= len) return GBString();
        if (pos + n > len) n = len - pos;
        return GBString(ptr + pos, n);
    }

    int lastIndexOf(char c) const
    {
        if (len == 0) return -1;

        for (int i = (int)len - 1; i >= 0; i--)
            if (ptr[i] == c) return i;

        return -1;
    }

    int lastIndexOf(char c, size_t from) const
    {
        if (len == 0) return -1;
        if (from >= len) from = len - 1;

        for (int i = (int)from; i >= 0; i--)
            if (ptr[i] == c) return i;

        return -1;
    }

    int lastIndexOf(const char* s) const
    {
        if (!s) return -1;

        size_t n = strlen(s);
        if (n == 0 || n > len) return -1;

        for (int i = (int)(len - n); i >= 0; i--)
            if (memcmp(ptr + i, s, n) == 0)
                return i;

        return -1;
    }

    int lastIndexOf(const char* s, size_t from) const
    {
        if (!s) return -1;

        size_t n = strlen(s);
        if (n == 0 || n > len) return -1;

        if (from > len - n)
            from = len - n;

        for (int i = (int)from; i >= 0; i--)
            if (memcmp(ptr + i, s, n) == 0)
                return i;

        return -1;
    }

    int indexOf(char c, size_t from = 0) const
    {
        for (size_t i = from; i < len; i++)
            if (ptr[i] == c) return i;
        return -1;
    }

    int indexOf(const char* s) const
    {
        if (!s) return -1;
        size_t n = strlen(s);
        if (n == 0 || n > len) return -1;

        for (size_t i = 0; i <= len - n; i++)
            if (memcmp(ptr + i, s, n) == 0)
                return i;

        return -1;
    }

    int indexOf(const char* s, size_t from = 0) const
    {
        if (!s || from >= len) return -1;
        size_t n = strlen(s);
        if (n == 0 || n > len - from) return -1;

        for (size_t i = from; i <= len - n; i++)
        {
            if (memcmp(ptr + i, s, n) == 0)
                return i;
        }

        return -1;
    }

    size_t count(const char* s) const
    {
        if (!s) return 0;

        size_t n = strlen(s);
        if (n == 0 || n > len) return 0;

        size_t cnt = 0;
        for (size_t i = 0; i <= len - n;)
        {
            if (memcmp(ptr + i, s, n) == 0)
            {
                cnt++;
                i += n;   
            }
            else
            {
                i++;
            }
        }
        return cnt;
    }

    char popFirst()
    {
        if (len == 0) return '\0';
        char c = buf[0];
        memmove(buf, buf + 1, --len);
        buf[len] = '\0';
        return c;
    }

    char popLast()
    {
        if (len == 0) return '\0';
        char c = buf[--len];
        buf[len] = '\0';
        return c;
    }

    // bool isDigit() const
    // {
    //     if (len == 0) return false;
    //     for (size_t i = 0; i < len; i++)
    //         if (ptr[i] < '0' || ptr[i] > '9') return false;
    //     return true;
    // }

    bool isInt() const
    {
        if (len == 0) return false;
        size_t i = (ptr[0] == '-' || ptr[0] == '+') ? 1 : 0;
        if (i >= len) return false;
        for (; i < len; i++)
            if (ptr[i] < '0' || ptr[i] > '9') return false;
        return true;
    }

    bool isFloat() const
    {
        if (length() == 0) return false;

        bool punto = false;
        int start = 0;

        if (ptr[0] == '-') 
        {
            if (length() == 1) return false;
            start = 1;
        }

        for (int i = start; i < length(); i++) 
        {
            if (ptr[i] == '.') 
            {
                if (punto) return false; 
                punto = true;
            } 
            else if (!isDigit(ptr[i])) 
            {
                return false;
            }
        }
        
        return true;
    }

    int toInt() const { return atoi(ptr); }
    float toFloat() const { return atof(ptr); }

    size_t replace(char find, char repl, char* out, size_t outSize) const
    {
        if (!out || outSize == 0) return 0;

        size_t n = (len < outSize - 1) ? len : outSize - 1;
        for (size_t i = 0; i < n; i++)
            out[i] = (ptr[i] == find) ? repl : ptr[i];
        out[n] = '\0';
        return n;
    }

    size_t replace(const char* target, const char* sustituto)
    {
        if (!target || !sustituto) return 0;

        size_t targetLen = strlen(target);
        if (targetLen == 0 || targetLen > len) return 0;

        size_t replLen = strlen(sustituto);

        char tmp[CAPACITY];
        size_t outLen = 0;
        size_t count = 0;

        for (size_t i = 0; i < len;)
        {
            if (i + targetLen <= len &&
                memcmp(buf + i, target, targetLen) == 0)
            {
                for (size_t j = 0; j < replLen && outLen < CAPACITY - 1; j++)
                    tmp[outLen++] = sustituto[j];

                i += targetLen;
                count++;
            }
            else
            {
                if (outLen < CAPACITY - 1)
                    tmp[outLen++] = buf[i];
                i++;
            }
        }

        tmp[outLen] = '\0';

        memcpy(buf, tmp, outLen + 1);
        len = outLen;
        ptr = buf;

        return count;
    }

};

#endif
