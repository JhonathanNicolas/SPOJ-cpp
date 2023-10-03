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
using namespace std;

int get_smallest_palindrome(std::string str)
{
    bool is_odd;
    int high_side, low_side, middle, number, candidate, i;
    std::string str_high, str_low;

    if (str.size() == 1)
        return 11;
    else if (str.size() % 2 == 0)
        is_odd = false;
    else
        is_odd = true;

    if(is_odd)
    {
        for(size_t i = str.size()-1; i >= str.size()/2; i-- )
        {
            str_high += str[i];
        }

        high_side = std::stoi(str_high);

        for(size_t i = str.size()/2 - 1; i >= 0; i--)
        {
            str_low += str[i];
        }

        low_side = std::stoi(str_low);
        number = std::stoi(str_high + str_low);
        

        i = 0;
        do
        {
            candidate = std::stoi(std::to_string(high_side+i) + std::to_string(high_side+i));
            i++;
        }while(candidate < number);

        return candidate;
    }

    return 0;
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
		std::cout << get_smallest_palindrome(numbers[i]);
	}

	return 0;
}