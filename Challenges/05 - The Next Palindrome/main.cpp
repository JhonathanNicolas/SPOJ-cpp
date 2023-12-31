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
#include <algorithm>
using namespace std;

std::string incrementString(const std::string& str)
{
    string result = str;
    int carry = 1;

    for (int i = str.size() - 1; i >= 0 && carry; i--)
    {
        int sum = (str[i] - '0') + carry;
        result[i] = (sum % 10) + '0';
        carry = sum / 10;
    }

    if (carry)
        result.insert(result.begin(), '1');

    return result;
}

std::string get_smallest_palindrome(std::string& str)
{
    int n = str.size();
    std::string str_temp = "";

    str_temp = str;

    for (int i = 0; i < n -1; )
    {
        if (str_temp[i] == '0')
        {
            str_temp.erase(0, 1);
        }
        else
        {
            break;
        }
    }

    n = str_temp.size();

    if (n == 1)
    {
        if (str_temp == "9")
            return "11";
        else
            return to_string((str_temp[0] - '0') + 1);
    }

    bool allNines = all_of(str_temp.begin(), str_temp.end(), [](char c) { return c == '9'; });

    if (allNines)
    {
        str_temp = "";

        for (int i = 0; i < str.size(); i++)
        {
            if (str_temp == "")
                str_temp += "1";
            else
                str_temp += "0";
        }

        str_temp += "1";
        return str_temp;
    }

    bool is_odd = n % 2;
    int mid = n / 2;

    string left = str_temp.substr(0, mid);
    string right = str_temp.substr(mid + is_odd);

    string potentialPalindrome;
    if (is_odd)
        potentialPalindrome = left + str_temp[mid] + string(left.rbegin(), left.rend());
    else
        potentialPalindrome = left + string(left.rbegin(), left.rend());

    if (potentialPalindrome <= str_temp) {
        if (is_odd) {
            if (str_temp[mid] == '9') {
                left = incrementString(left);
                str_temp[mid] = '0';
            }
            else {
                str_temp[mid]++;
            }
        }
        else {
            left = incrementString(left);
        }
    }

    // Construct the palindrome using the incremented (or unchanged) values
    if (is_odd)
        return left + str_temp[mid] + string(left.rbegin(), left.rend());
    else
        return left + string(left.rbegin(), left.rend());
}

int main()
{
    int t;
    std::cin >> t;
    std::vector<std::string> numbers(t);

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