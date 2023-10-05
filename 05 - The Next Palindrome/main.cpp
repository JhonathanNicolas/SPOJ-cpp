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
#include <iterator>s
#include <algorithm>
using namespace std;

std::string sum_on_string(const std::string str)
{
    size_t str_len = str.size();
    std::string result = str;
    std::string temp = str;

    for (int i = str_len-1; i >= 0; i--)
    {
        if (str[i] != 57)
        {
            result[i] = ((result[i] - '0') + 1) + '0';
            return result;
        }
        else
        {
            temp = result;
            temp.erase(i, 1);
            result = sum_on_string(temp) + '0';
            return result;
        }
    }
}

std::string find_smallest_high_side(const std::string high_side, const std::string low_side)
{
    size_t high_side_len, low_side_len, j = 0;
    std::string result = "";

    high_side_len = high_side.size() - 1;
    low_side_len = low_side.size() - 1;
    result = high_side;

    if (low_side_len < high_side_len)
    {
        high_side_len--;
    }

    result = sum_on_string(result);
    return result;

}


int compare_sides(const std::string high_side, const std::string low_side)
{
    size_t high_side_len, low_side_len, j = 0;
    int result = 0;

    high_side_len = high_side.size() - 1;
    low_side_len = low_side.size()  - 1;
    
    if (low_side_len < high_side_len)
    {
        high_side_len--;
    }

    for (int i = high_side_len; i >= 0 ; i--)
    {
            

        if ( (high_side[i] - '0') > (low_side[j] - '0') )
        {
            return 0;
        }
        else if ((high_side[i] - '0') < (low_side[j] - '0'))
        {
            return -1;
        }
        else if (((high_side[i] - '0') == (low_side[j] - '0')) && (i == 0))
        {
            return -1;
        }

        if(low_side_len != 0)
            j = (j % low_side_len) + 1;
    }

    return result;
}

std::string get_smallest_palindrome(std::string str)
{
    bool is_odd, is_all_nine = true;
    int  middle, number, candidate, i, j, side;
    std::string str_high = "", str_middle = "", str_temp = "", str_temp2 = "";

    j = str.size();
    str_temp2 = str;

    //remove leading zeros
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

    //if it has only on digit just adds one or if it is nine return 11
    if (str.size() <= 1)
    {
        i = std::stoi(str);
        return i != 9 ? std::to_string(i + 1) : "11";

    }
    else if (str.size() % 2 == 0)
        is_odd = false;
    else
        is_odd = true;
    
    
    if (!is_odd)
        i = str.size() / 2;
    else
        i = (str.size() / 2) + 1;

    std::string high_side = str.substr(0, i);
    std::string low_side = str.substr(i);


    // verify if all digits are nine
    for (i = 0; i < j; i++)
    {
        if (str[i] != '9')
        {
            is_all_nine = false;
            break;
        }

    }

    if (is_all_nine) // if all digits are nine, then the next palindrome is "1 followed 0's and more 1"
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

        side = compare_sides(high_side, low_side);

        if (side == 0)
        {
            str_middle = "";

            if (is_odd)
            {
                str_middle = high_side.back();
                high_side.erase(high_side.size() - 1, 1);
            }

            low_side = high_side;
            std::reverse(low_side.begin(), low_side.end());
            return high_side + str_middle + low_side;
        }
        else
        {
            high_side = find_smallest_high_side(high_side, low_side);
            low_side = high_side;

            if (is_odd)
                low_side.resize(low_side.size() - 1);

            std::reverse(low_side.begin(), low_side.end());
            return high_side + str_middle + low_side;
        }

    }
}

int main() {
    // your code goes here
    int t = 1;
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
