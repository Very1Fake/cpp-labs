#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <tuple>

#define MATCH_TYPE int32_t

using namespace std;

// Check if given match array has the match with given number
bool got_match(MATCH_TYPE *matches, size_t length, MATCH_TYPE to_check)
{
    for (size_t i = 0; i < length; i++)
    {
        if (matches[i] == to_check)
        {
            return true;
        }
    }

    return false;
}

// Print array
void print_array(MATCH_TYPE *array, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        cout << "Array element [" << i << "] = " << array[i] << "\n";
    }
}

// Task function
tuple<MATCH_TYPE *, size_t> count_numbers(string input)
{
    size_t prediction = (size_t)count(input.begin(), input.end(), ' ') + 1;
    MATCH_TYPE *matches = new MATCH_TYPE[prediction];
    size_t count = 0;

    stringstream input_stream(input);
    MATCH_TYPE number;
    string word;

    while (input_stream >> number || !input_stream.eof())
    {
        // Skip unparsable word
        if (input_stream.fail())
        {
            input_stream.clear();
            input_stream >> word;
            continue;
        }

        if (!got_match(matches, prediction, number))
        {
            matches[count] = number;
            count++;
        }
    }

    // Shrink matches array
    MATCH_TYPE* matches_final = new MATCH_TYPE[count];

    for (size_t i = 0; i < count; i++) {
        matches_final[i] = matches[i];
    }

    return make_tuple(matches_final, count);
}

// Testing function
int main()
{
    string input;
    cout << "Enter input string: ";
    getline(cin, input);

    auto [matches, length] = count_numbers(input);

    cout << "Unique numbers from input string:" << endl;
    print_array(matches, length);

    return 0;
}
