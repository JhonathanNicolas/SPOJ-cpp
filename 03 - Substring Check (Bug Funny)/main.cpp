/*
Given two binary strings, A (of length 10) and B (of length 5), output 1 if B is a substring of A and 0 otherwise.

Please note, that the solution may only be submitted in the following languages: Brainf**k, Whitespace and Intercal.

Input
24 lines consisting of pairs of binary strings A and B separated by a single space.

Output
The logical value of: 'B is a substring of A'.

Example
First two lines of input:

1010110010 10110
1110111011 10011
First two lines of output:
1
0
*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define NUM_INPUT_LINES 24
#define SIZE_STRING 10
#define SIZE_SUBSTRING 5

bool is_substring(std::string str, std::string sub_str)
{
    uint16_t i = 0, k = 0, j = 0;
    bool is_substring = true;

    for (i = j; i < str.size() - 1; i++)
    {
        j = i;

        for (k = 0; k < sub_str.size(); k++)
        {
            if (k == sub_str.size() - 1)
                return true;

            if ( (str[j] == sub_str[k]) && (j < str.size() - 1))
            {        
                j++;
                continue;
            }
            else
            {
                break;
            }
        }
    }
    return false;
}

int main() {
    // your code goes here
    std::vector<std::string> str(NUM_INPUT_LINES), sstr(NUM_INPUT_LINES);

    for (int i = 0; i < NUM_INPUT_LINES; i++)
    {
        cin >> str[i] >> sstr[i];

    }

    for (int i = 0; i < NUM_INPUT_LINES; i++)

    {
        if (is_substring(str[i], sstr[i]))
            cout << 1 << endl;
        else
            cout << 0 << endl;
    }
    return 0;
}