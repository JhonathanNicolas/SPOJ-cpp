/*
Given a sequence of 2*k characters, please print every second character from the first half of the sequence. Start printing with the first character.

Input
In the first line of input you are given the positive integer t (1<=t<=100) - the number of test cases. In the each of the next t lines, you are given a sequence of 2*k (1<=k<=100) characters.

Output
For each of the test cases please please print every second character from the first half of a given sequence (the first character should appear).

Example
Input:
4
your
progress
is
noticeable

Output:
y
po
i
ntc

*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    int t;
    
    cin >> t;

    std::vector<string> str(t);
std:string temp = "";

    for (int i = 0; i < str.size(); i++)
        cin >> str[i];

    for (int i = 0; i < str.size(); i++)
    {
        str[i] = str[i].substr(0, (str[i].size() / 2));

        for (int j = 0; j < str[i].size(); j += 2)
        {
            temp += str[i][j];
        }

        cout << temp << endl;
        temp = "";
    }
    return 0;
}