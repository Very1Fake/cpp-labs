#include <iostream>

#define N 10
#define ARRAY_TYPE uint16_t

using namespace std;

void swap(ARRAY_TYPE *array, size_t a, size_t b)
{
    ARRAY_TYPE temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}

// Task Function
void remove_element(ARRAY_TYPE *array, size_t len, size_t to_remove)
{
    if (to_remove < 0)
    {
        cout << "\n\nNegative index is incorrect. Array is unchanged\n\n";
    }
    else if (to_remove >= len)
    {
        cout << "\n\nIndex is out of bound. Array is unchanged!!!\n\n";
    }
    else
    {
        array[to_remove] = 0;
        for (size_t i = to_remove; i < len - 1; i++)
            swap(array, i, i + 1);
    }
}

// Print function
void print_array(ARRAY_TYPE *array, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        cout << "Array element [" << i << "] = " << array[i] << endl;
    }
}

// Full given array with random numbers
void fill_array(ARRAY_TYPE *array, size_t len)
{
    srand(time(nullptr));

    for (size_t i = 0; i < len; i++)
    {
        array[i] = rand();
    }
}

// Testing function
int main()
{
    ARRAY_TYPE array[N] = {};

    cout << "Creating source array\n";
    fill_array(array, N);

    cout << "Source array:\n";
    print_array(array, N);

    cout << "\nEnter index of value to remove: ";
    size_t index = 0;
    cin >> index;

    remove_element(array, N, index);
    cout << "\nThe array after removing value:\n";
    print_array(array, N);

    return 0;
}
