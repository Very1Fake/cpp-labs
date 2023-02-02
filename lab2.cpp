#include "iostream"
#include "tuple"

#define ARRAY_TYPE int64_t

using namespace std;

// Get array from user
tuple<ARRAY_TYPE *, size_t> get_array()
{
    size_t length;

    cout << "Enter array length: ";
    cin >> length;

    ARRAY_TYPE *array = (ARRAY_TYPE *)malloc(sizeof(ARRAY_TYPE) * length);

    for (size_t i = 0; i < length; i++)
    {
        cout << "Enter [" << i << "] element of array: ";
        cin >> array[i];
    }

    return make_tuple(array, length);
}

// Print array
void print_array(ARRAY_TYPE *array, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        cout << "Array element [" << i << "] = " << array[i] << "\n";
    }
}

int cmp(const void *a, const void *b)
{
    const ARRAY_TYPE *x = (ARRAY_TYPE *)a;
    const ARRAY_TYPE *y = (ARRAY_TYPE *)b;

    return *x > *y;
}

// Entry point
int main()
{
    auto [user_array, user_length] = get_array();

    cout << endl
         << "Source array:" << endl;
    print_array(user_array, user_length);

    cout << endl
         << "Sorted array:" << endl;
    qsort(user_array, user_length, sizeof(ARRAY_TYPE), cmp);

    print_array(user_array, user_length);

    return 0;
}
