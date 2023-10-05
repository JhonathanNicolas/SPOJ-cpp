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

    string rev_left = string(left.rbegin(), left.rend());

    if (rev_left <= right)
        left = incrementString(left);

    rev_left = string(left.rbegin(), left.rend());

    if (is_odd)
        return left + str_temp[mid] + rev_left;
    else
        return left + rev_left;
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
