#include <iostream>

#include "custom_string.h"
#include "custom_string.cpp"

using namespace std;

int main()
{
    String empty;

    cout << "Empty: '" << empty << "'" << endl;

    String str("some");

    cout << "After init: " << str << endl;

    str += "123";

    cout << "After appending: " << str << endl;

    empty += str;

    cout << "Empty after append: " << empty << endl;

    String hello("Hello");

    cout << "operator+: " << empty + hello << endl;

    cout << "Compare: "
         << "\n\t" << (empty == str)
         << "\n\t" << (str != hello)
         << "\n\t" << (hello < str)
         << "\n\t" << (hello > str) << endl;

    String copied = hello;

    cout << "Copied: " << copied << " , hello: " << hello << endl;

    return 0;
}