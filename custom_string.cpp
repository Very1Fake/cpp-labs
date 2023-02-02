#include <algorithm>
#include <cstring>
#include <string>
#include <stdexcept>
#include <iostream>

#include "custom_string.h"

using namespace std;

String::String() : m_length(0)
{
    m_string = new char[1];
    m_string[0] = '\0';
}

String::String(char _char) : m_length(1)
{
    m_string = new char[2];
    m_string[0] = _char;
    m_string[1] = '\0';
}

String::String(const char *string)
{
    if (!string)
    {
        m_length = 0;
        m_string = new char[0];
    }
    else
    {
        m_length = strlen(string);
        m_string = new char[m_length + 1];

        copy(string, string + m_length, m_string);
        m_string[m_length] = '\0';
    }
}

String::String(const String &string)
{
    char *buffer = new char[string.m_length + 1];
    copy(string.m_string, string.m_string + string.m_length, buffer);
    buffer[string.m_length] = '\0';

    m_string = buffer;
    m_length = string.m_length;
}

String::~String()
{
    delete[] m_string;
    m_string = nullptr;
}

void String::clear()
{
    m_length = 0;
    m_string = nullptr;
}

const size_t String::length()
{
    return m_length;
}

const bool String::operator==(const String &other)
{
    if (!other.m_string)
        return false;
    return strcmp(m_string, other.m_string) == 0;
}

const bool String::operator!=(const String &other)
{
    if (!other.m_string)
        return true;
    return strcmp(m_string, other.m_string) == 1;
}

String &String::operator=(const String &other)
{
    if (this != &other)
    {
        char *buffer = new char[other.m_length + 1];
        copy(other.m_string, other.m_string + other.m_length + 1, buffer);

        swap(buffer, m_string);
        m_length = other.m_length;

        delete[] buffer;
    }

    return *this;
}

const bool String::operator>(const String &_other)
{
    return lexicographical_compare(
        this->m_string,
        this->m_string + this->m_length + 1,
        _other.m_string,
        _other.m_string + _other.m_length + 1);
}

const bool String::operator>=(const String &_other)
{
    return (*this == _other || *this > _other);
}

const bool String::operator<(const String &_other)
{
    return !(*this > _other);
}

const bool String::operator<=(const String &_other)
{
    return (*this == _other || *this < _other);
}

String &String::operator+=(const String &other)
{
    if (this != &other)
    {
        auto totalLength = m_length + other.m_length;
        char *buffer = new char[totalLength + 1];

        copy(m_string, m_string + m_length, buffer);
        copy(other.m_string, other.m_string + other.m_length, buffer + m_length);
        buffer[totalLength] = '\0';

        swap(m_string, buffer);
        m_length = totalLength;

        delete[] buffer;
    }

    return *this;
}

String &String::operator+=(const char *other)
{
    const auto charLength = strlen(other);
    const auto totalLength = m_length + charLength;
    char *buffer = new char[totalLength + 1];

    copy(m_string, m_string + m_length, buffer);
    copy(other, other + charLength, buffer + m_length);
    buffer[totalLength] = '\0';

    swap(m_string, buffer);
    m_length = totalLength;

    delete[] buffer;

    return *this;
}

const String String::operator+(const String &other)
{
    const auto totalLength = m_length + other.m_length;
    char *buffer = new char[totalLength + 1];

    copy(m_string, m_string + m_length, buffer);
    copy(other.m_string, other.m_string + other.m_length, buffer + m_length);
    buffer[totalLength] = '\0';

    return String(buffer);
}

const String String::operator+(const char *other)
{
    const auto charLength = strlen(other);
    const auto totalLength = m_length + charLength;
    char *buffer = new char[totalLength + 1];

    copy(m_string, m_string + m_length, buffer);
    copy(other, other + charLength, buffer + m_length);
    buffer[totalLength] = '\0';

    return String(buffer);
}

std::ostream &operator<<(std::ostream &os, const String &string)
{
    os << string.m_string;
    return os;
}
