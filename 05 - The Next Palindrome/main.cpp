/*
A positive integer is called a palindrome if its representation in the decimal system is the same when read from left to right and from right to left. For a given positive integer K of not more than 1000000 digits, write the value of the smallest palindrome larger than K to output. Numbers are always displayed without leading zeros.

Input
The first line contains integer t, the number of test cases. Integers K are given in the next t lines.

Output
For each K, output the smallest palindrome larger than K.

Example
Input:
2
808
2133

Output:
818
2222
Warning: large Input/Output data, be careful with certain languages


*/


#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
using namespace std;

std::string get_smallest_palindrome(std::string str)
{
    bool is_odd, is_all_nine = true;
    int  middle, number, candidate, i, j, k;
    std::string str_high = "", str_middle = "", str_temp = "", str_temp2 = "";

    j = str.size();
    str_temp2 = str;
    for (i = 0; i < j; i++)
    {
        if (str_temp2[i] == '0')
        {
            if ((i + 1) == j)
                break;
            str.erase(0,1);
        }
        else
        {
            break;
        }
    }

    if (str.size() <= 1)
    {
        i = std::stoi(str);
        return i != 9 ? std::to_string(i + 1) : "11";

    }
    else if (str.size() % 2 == 0)
        is_odd = false;
    else
        is_odd = true;

    std::string low_side(str.rbegin() + 0, str.rbegin() + str.size() / 2);
    std::string high_side(str.rbegin() + (is_odd ? (str.size() / 2) + 1 : (str.size() / 2)), str.rend());
    std::reverse(high_side.begin(), high_side.end());
    std::reverse(low_side.begin(), low_side.end());
    str_middle += str.at(str.size() / 2);
    middle = stoi(str_middle);


    

    if (str.find("0") != std::string::npos || (str.find("1") != std::string::npos) || (str.find("2") != std::string::npos) || (str.find("3") != std::string::npos)
        || (str.find("4") != std::string::npos) || (str.find("5") != std::string::npos) || (str.find("6") != std::string::npos) || (str.find("7") != std::string::npos)
        || (str.find("8") != std::string::npos))
        is_all_nine = false;

    if (is_all_nine)
    {

        for (i = (is_odd ? 0 : 1); i <= high_side.size(); i++)
        {
            if (str_temp == "")
                str_temp += "1";
            else
                str_temp += "0";
        }

        std::string str_temp2(str_temp.rbegin() + 0, str_temp.rend());

        if (!is_odd)
            str_temp += "0" + str_temp2;
        else
            str_temp += str_temp2;

        return str_temp;
    }
    else
    {
        if (!is_odd)
        {
            if (middle > ((high_side[high_side.size() - 1] - '0')))
            {
                high_side[high_side.size() - 1] = '0' + (high_side[high_side.size() - 1] - '0') + 1;
            }
            else
            {
                is_all_nine = true;
                for (int i = 0; i < low_side.size(); i++)
                {
                    if ((high_side[i] - '0') < (low_side[i] - '0'))
                    {
                        high_side[high_side.size() - 1] = '0' + middle + 1;
                        break;
                    }
                    if ((high_side[i] - '0') != (low_side[i] - '0'))
                        is_all_nine = false;
                }
                if (is_all_nine)
                {
                    if (middle != 9)
                        high_side[high_side.size() - 1] = '0' + middle + 1;
                }

            }

            low_side = high_side;
            std::reverse(low_side.begin(), low_side.end());
            return high_side + low_side;
        }
        else
        {
            if ((low_side[0] - '0') > (high_side[high_side.size() - 1] - '0'))
            {
                middle += 1;
            }
            else if ((low_side[0] - '0') == (high_side[high_side.size() - 1] - '0'))
            {
                is_all_nine = false;

                for (int i = 1; i < low_side.size(); i++)
                {
                    if (((low_side[i] - '0') > (high_side[high_side.size() - i - 1] - '0')) || (((low_side[i] - '0') == (high_side[high_side.size() - i - 1] - '0')) && (i == low_side.size() - 1)))
                    {
                        is_all_nine = true;
                        break;
                    }
                }
                if (is_all_nine || ((high_side.size() == 1) && (((high_side[0] - '0') <= (low_side[0] - '0')))))
                {
                    if (middle != 9)
                        middle += 1;
                    else
                    {
                        for (int i = high_side.size() - 1; i >= 0; i--)
                        {
                            if ((high_side[i] - '0') != 9)
                            {
                                high_side[i] = ((high_side[i] + '0') + 1) - '0';
                                middle = 0;
                                break;
                            }
                        }
                    }
                }
            }

            low_side = high_side;
            std::reverse(low_side.begin(), low_side.end());
            return high_side + std::to_string(middle) + low_side;
        }

    }
}

int main() {
    // your code goes here
    int t;
    std::vector<std::string> numbers(0);

    std::cin >> t;

    if (t > 0)
    {
        numbers.resize(t);
    }

    for (int i = 0; i < t; i++)
    {
        std::cin >> numbers[i];
    }

    for (int i = 0; i < t; i++)
    {
        std::cout << get_smallest_palindrome(numbers[i]) << endl;
    }

    return 0;
}
