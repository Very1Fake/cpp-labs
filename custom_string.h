#ifndef CUSTOM_STRING_H
#define CUSTOM_STRING_H
#include <ostream>

class String
{
private:
    size_t m_length;
    char *m_string;
public:
    String();
    String(char _char);
    String(const char *string);

    String(const String &string);
    ~String();

    void clear();
    const size_t length();

    const bool operator==(const String &other);
    const bool operator!=(const String &other);
    const bool operator>(const String &_other);
    const bool operator>=(const String &_other);
    const bool operator<(const String &_other);
    const bool operator<=(const String &_other);

    String &operator=(const String &_other);

    String &operator+=(const String &other);
    String &operator+=(const char *other);
    const String operator+(const String &other);
    const String operator+(const char *other);

    friend std::ostream &operator<<(std::ostream &_os, const String &string);
};

#endif
