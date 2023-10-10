/*In one of the internet banks thousands of operations are being performed every day. Since certain customers do business more actively than others, some of the bank accounts occur many times in the list of operations. Your task is to sort the bank account numbers in ascending order. If an account appears twice or more in the list, write the number of repetitions just after the account number. The format of accounts is as follows: 2 control digits, an 8-digit code of the bank, 16 digits identifying the owner (written in groups of four digits), for example (at the end of each line there is exactly one space):

30 10103538 2222 1233 6160 0142
Banks are real-time institutions and they need FAST solutions. If you feel you can meet the challenge within a very stringent time limit, go ahead! A well designed sorting algorithm in a fast language is likely to succeed.

Input

t [the number of tests <= 5]
n [the number of accounts<= 100 000]
[list of accounts]
[empty line]
[next test cases]

Output

[sorted list of accounts with the number of repeated accounts]
[empty line]
[other results]

Example
Input:
2
6
03 10103538 2222 1233 6160 0142
03 10103538 2222 1233 6160 0141
30 10103538 2222 1233 6160 0141
30 10103538 2222 1233 6160 0142
30 10103538 2222 1233 6160 0141
30 10103538 2222 1233 6160 0142

5
30 10103538 2222 1233 6160 0144
30 10103538 2222 1233 6160 0142
30 10103538 2222 1233 6160 0145
30 10103538 2222 1233 6160 0146
30 10103538 2222 1233 6160 0143

Output:
03 10103538 2222 1233 6160 0141 1
03 10103538 2222 1233 6160 0142 1
30 10103538 2222 1233 6160 0141 2
30 10103538 2222 1233 6160 0142 2

30 10103538 2222 1233 6160 0142 1
30 10103538 2222 1233 6160 0143 1
30 10103538 2222 1233 6160 0144 1
30 10103538 2222 1233 6160 0145 1
30 10103538 2222 1233 6160 0146 1*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

typedef std::string account_number;

int compareNumericStrings(const account_number& str1, const account_number& str2) {
    if (str1 < str2) return -1;
    if (str1 > str2) return 1;
    return 0;
}

int main() {
    int t, j;
    cin >> t;
    vector<unordered_map<account_number, int>> accounts_map(t);

    for (int k = 0; k < t; k++) {
        cin >> j;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        account_number temp;

        for (int i = 0; i < j; i++) {
            getline(cin, temp);
            temp.erase(remove_if(temp.begin(), temp.end(), [](char c) { return !isdigit(c); }), temp.end());
            accounts_map[k][temp]++;
        }
    }

    for (int i = 0; i < t; i++) {
        vector<pair<account_number, int>> sorted_accounts(accounts_map[i].begin(), accounts_map[i].end());
        sort(sorted_accounts.begin(), sorted_accounts.end(), [](const auto& a, const auto& b) {
            return compareNumericStrings(a.first, b.first) < 0;
            });

        for (const auto& p : sorted_accounts) {
            cout << p.first.substr(0, 2) << " " << p.first.substr(2, 8) << " " << p.first.substr(10, 4) << " "
                << p.first.substr(14, 4) << " " << p.first.substr(18, 4) << " " << p.first.substr(22, 4)
                << " " << p.second << "\n";
        }

        cout << "\n";
    }

    return 0;
}
