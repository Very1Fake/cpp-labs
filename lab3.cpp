#include <iostream>
#include <string>

#include "stack.h"
#include "stack.cpp"

using namespace std;

struct Point
{
    int x;
    int y;
    int z;
};

int main()
{
    Stack<int> size_stack(1);

    cout << size_stack;

    size_stack.push(256);
    size_stack.push(128);
    size_stack.push(64);
    size_stack.push(32);

    cout << size_stack;

    Stack<char> string_stack(16);

    string_stack.push('h');
    string_stack.push('e');
    string_stack.push('l');
    string_stack.push('l');
    string_stack.push('o');
    string_stack.push('!');

    cout << string_stack;

    cout << string_stack.pop() << endl;
    cout << string_stack.pop() << endl;
    cout << string_stack.pop() << endl;
    cout << string_stack.pop() << endl;
    cout << string_stack.pop() << endl;
    cout << string_stack.pop() << endl;

    try
    {
        cout << string_stack.pop() << endl;
    } catch (invalid_argument) {
        cout << "Stack is empty";
    }

    string_stack.shrink_to_fit();
    cout << endl << string_stack;

    Stack<Point> point_stack(2);

    point_stack.push((Point){1, 0, 0});
    point_stack.push((Point){0, 1, 0});
    point_stack.push((Point){0, 0, 1});

    cout << point_stack;

    return 0;
}