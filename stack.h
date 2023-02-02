#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <exception>

using namespace std;

template <typename T>
class Stack
{
private:
    T *m_inner;
    size_t m_size;
    size_t m_capacity;

    void resize(size_t m_size);

public:
    Stack(size_t capacity = 0);

    void shrink_to_fit();

    void push(T item);

    T pop();

    inline friend ostream &operator<<(ostream &os, const Stack &self)
    {
        os << "Stack (m_size=" << self.m_size << ",m_capacity=" << self.m_capacity << ")" << endl;
        return os;
    }
};

#endif
