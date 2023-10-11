/*Using two characters: . (dot) and * (asterisk) print a chessboard-like pattern. The first character printed should be * (asterisk).

Input
You are given t < 100 - the number of test cases and for each of the test cases two positive integers: l - the number of lines and c - the number of columns in the pattern (l, c < 100).

Output
For each of the test cases output the requested pattern (please have a look at the example). Use one line break in between successive patterns.

Example
Input:
3
3 1
4 4
2 5

Output:
*
.
*

*.*.
.*.*
*.*.
.*.*

*.*.*
.*.*.
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

std::string calc_chess_table(int lines, int collums)
{
    std::string chess_table = "";
    bool parity = false;

    for (int l = 0; l < lines; l++)
    {

        for (int c = 0; c < collums; c++)
        {
            if (!parity)
                chess_table += '*';
            else
                chess_table += '.';

            parity = !parity;
        }

        if (collums % 2 == 0)
            parity = !parity;

        chess_table += '\n';
    }
    return chess_table;
}

int main()
{
    int t;
    cin >> t;

    if (t <= 0)
        return 0;

    std::vector<int> lines(t), collums(t);

    for (int i = 0; i < t; i++)
    {
        cin >> lines[i] >> collums[i];
    }

    for (int i = 0; i < t; i++)
    {
        cout << calc_chess_table(lines[i], collums[i]) << endl;
    }

    return 0;
}