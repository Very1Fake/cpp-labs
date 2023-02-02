#include "stack.h"

template <typename T>
Stack<T>::Stack(size_t capacity) : m_capacity(capacity), m_size(capacity)
{
    m_inner = new T[m_capacity];
}

template <typename T>
void Stack<T>::resize(size_t size)
{
    T *temp = new T[size];

    for (size_t i = 0; i < size; i++)
    {
        temp[i] = m_inner[i];
    }

    m_inner = temp;
    m_capacity = size;
}

template <typename T>
void Stack<T>::shrink_to_fit()
{
    if (m_capacity > m_size)
    {
        resize(m_size);
    }
}

template <typename T>
void Stack<T>::push(T item)
{
    if (m_capacity == m_size)
    {
        resize(m_capacity * 2);
    }

    m_inner[m_size++] = item;
}

template <typename T>
T Stack<T>::pop()
{
    if (m_size == 0)
    {
        throw invalid_argument("Stack is empty");
    }
    else
    {
        m_size--;
        T item = m_inner[m_size];
        return item;
    }
}
