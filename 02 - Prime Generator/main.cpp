/*
Peter wants to generate some prime numbers for his cryptosystem. Help him! Your task is to generate all prime numbers between two given numbers!

Input
The input begins with the number t of test cases in a single line (t<=10). In each of the next t lines there are two numbers m and n (1 <= m <= n <= 1000000000, n-m<=100000) separated by a space.

Output
For every test case print all prime numbers p such that m <= p <= n, one number per line, test cases separated by an empty line.

Example
Input:
2
1 10
3 5

Output:
2
3
5
7

3
5
Warning: large Input/Output data, be careful with certain languages (though most should be OK if the algorithm is well designed)
Information
After cluster change, please consider PRINT as a more challenging problem.
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;


std::vector<bool> sieve_of_eratosthenes(int a, int b)
{

	if (b < a)
		return std::vector<bool>(0);
	else
	{
		std::vector<bool> is_prime(b - a + 1, true);

		if (a == 1)
			is_prime[0] = false;

		for (int p = 2; p * p <= b; ++p) {
			if ((a + p - 1) / p * p < p * p) 
			{
				for (int i = p * p; i <= b; i += p) 
				{
					is_prime[i - a] = false;
				}
			}
			else {
				for (int i = (a + p - 1) / p * p; i <= b; i += p)
				{
					is_prime[i - a] = false;
				}
			}
		}

		return is_prime;
	}
}
std::void_t<> print_list(std::vector<bool> list, int a)
{
	size_t size_list = list.size();
	std::string number_string;

	for(int i = 0; i < size_list; i++)
	{
		if (list[i])
		{

			number_string += std::to_string(a + i) + ' ';
		}
		
	}
	
	number_string.back() = '\n';
	cout << number_string;
}

int main() {
	
	int t;
	std::vector<int> n, m;
	std::vector<bool> prime_list;
	
	std::cin >> t;
	
	if (t > 0)
	{
		n.resize(t);
		m.resize(t);
	}
	
	for (int i = 0; i < t; i++)
	{
		std::cin >> n[i] >> m[i];

	}
	
	for (int i = 0; i < t; i++)
	{
		prime_list = sieve_of_eratosthenes(n[i], m[i]);
		print_list(prime_list, n[i]);
	}
	return 0;
}