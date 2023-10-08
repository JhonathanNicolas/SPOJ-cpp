/*
One part of the new WAP portal is also a calculator computing expressions with very long numbers. To make the output look better, the result is formated the same way as is it usually used with manual calculations.

Your task is to write the core part of this calculator. Given two numbers and the requested operation, you are to compute the result and print it in the form specified below. With addition and subtraction, the numbers are written below each other. Multiplication is a little bit more complex: first of all, we make a partial result for every digit of one of the numbers, and then sum the results together.

Input
There is a single positive integer T on the first line of input (equal to about 1000). It stands for the number of expressions to follow. Each expression consists of a single line containing a positive integer number, an operator (one of +, - and *) and the second positive integer number. Every number has at most 500 digits. There are no spaces on the line. If the operation is subtraction, the second number is always lower than the first one. No number will begin with zero.

Output
For each expression, print two lines with two given numbers, the second number below the first one, last digits (representing unities) must be aligned in the same column. Put the operator right in front of the first digit of the second number. After the second number, there must be a horizontal line made of dashes (-).

For each addition or subtraction, put the result right below the horizontal line, with last digit aligned to the last digit of both operands.

For each multiplication, multiply the first number by each digit of the second number. Put the partial results one below the other, starting with the product of the last digit of the second number. Each partial result should be aligned with the corresponding digit. That means the last digit of the partial product must be in the same column as the digit of the second number. No product may begin with any additional zeros. If a particular digit is zero, the product has exactly one digit -- zero. If the second number has more than one digit, print another horizontal line under the partial results, and then print the sum of them.

There must be minimal number of spaces on the beginning of lines, with respect to other constraints. The horizontal line is always as long as necessary to reach the left and right end of both numbers (and operators) directly below and above it. That means it begins in the same column where the leftmost digit or operator of that two lines (one below and one above) is. It ends in the column where is the rightmost digit of that two numbers. The line can be neither longer nor shorter than specified.

Print one blank line after each test case, including the last one.

Example
Sample Input:

4
12345+67890
324-111
325*4405
1234*4

Sample Output:

 12345
+67890
------
 80235

 324
-111
----
 213

    325
  *4405
  -----
   1625
     0
 1300
1300
-------
1431625

1234
  *4
----
4936
Warning: large Input/Output data, be careful with certain languages.
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;



class Expression
{
public:
    Expression()
    {
        _expression = "";
        _expression_number = 0;
        _opr = 0;
        _large_size = 0;
    }

    void set_expression(const std::string expression)
    {
        std::string temp = expression;
        _expression = _expression_number == 2 ? temp.insert(0, 1, _opr) : temp;
        _set_large_size();
    }

    void add_space()
    {
        _expression = " " + _expression;
        _set_large_size();
    }

    void set_expression_number(uint8_t num)
    {
        _expression_number = num;
    }

    void set_opr(char opr)
    {
        _opr = opr;
    }

    uint8_t get_large_size()
    {
        return _large_size;
    }

    std::string get_expression()
    {
        return _expression;
    }

    char get_opr()
    {
        return _opr;
    }

private:
    std::string _expression;
    uint8_t _expression_number;
    char _opr;
    uint8_t _large_size;

    void _set_large_size()
    {
        _large_size = _expression.size();
    }

};

class ArithDrawing
{
public:
    ArithDrawing(std::string raw_expression)
    {
        _raw_drawing = raw_expression;
        _size_lagest_expression = 0;
        number_of_result = 0;
        _result = "";
        _result2 = "";
        _drawing = "";
    }

    std::string get_drawing()
    {
        uint8_t size_e1, size_e2;

        _assing_expression();

        do {
            size_e1 = _first_expression.get_large_size();
            size_e2 = _second_expression.get_large_size();

            if (size_e1 > size_e2)
                _second_expression.add_space();
            else if(size_e1 < size_e2)
                _first_expression.add_space();

        } while (size_e1 != size_e2);

        _size_lagest_expression = size_e1;

        _get_result();
        get_second_result_line();
        _write_first_line();
        _jump_line();
        _write_second_line();
        _jump_line();
        _write_hyphen_first_line();
        _jump_line();
        _write_first_result_line();
        _jump_line();
        _write_hyphen_second_line();
        _write_second_result_line();
        return _drawing;
    }

private:
    Expression _first_expression;
    Expression _second_expression;
    uint8_t _size_lagest_expression;
    uint8_t number_of_result;
    std::string _result;
    std::string _result2;
    std::string _raw_drawing;
    std::string _drawing;

    void _write_first_line()
    {
        int size_result = _result.find('\n') == std::string::npos ? _result.size() : _result.find('\n');
        int size_result2 = _result2.size();

        while (_first_expression.get_large_size() < size_result-1)
        {
            _first_expression.add_space();
            size_result = _result.find('\n') == std::string::npos ? _result.size() : _result.find('\n');
        }

        if (_result2 != "")
        {
            while (_first_expression.get_large_size() < size_result2)
            {
                _first_expression.add_space();
            }
        }
            _drawing = _first_expression.get_expression();
    }

    void _write_second_line()
    {
        int size_result = _result.find('\n') == std::string::npos ? _result.size() : _result.find('\n');;
        int size_result2 = _result2.size();

        while (_second_expression.get_large_size() < size_result-1)
        {
            _second_expression.add_space();
            size_result = _result.find('\n') == std::string::npos ? _result.size() : _result.find('\n');
        }

        if (_result2 != "")
        {
            while (_second_expression.get_large_size() < size_result2)
            {
                _second_expression.add_space();
            }
        }
        _drawing += _second_expression.get_expression();
    }

    void _write_hyphen_first_line()
    {
        std:string result_line(_size_lagest_expression, '-');
        int size_result2 = _result2.size();

        if (_result2 != "")
        {
            while (result_line.size() < size_result2)
            {
                result_line = ' ' + result_line;
            }
        }
        _drawing += result_line;
    }

    void _write_hyphen_second_line()
    {
        if ((_first_expression.get_opr() != '*') || ( (_first_expression.get_opr() == '*') && (_removeNonDigits(_second_expression.get_expression()).size() == 1) ))
            return;

        uint8_t dash_len = _result.find('\n');
        std:string result_line(dash_len, '-');
        _drawing += result_line;
    }

    void _jump_line()
    {
        _drawing += '\n';
    }

    void _insert_space_on_result()
    {
        _result.insert(0, 1, ' ');
    }
    void _get_result()
    {
        char opr  = _first_expression.get_opr();
        int size_result = 0;
        switch (opr)
        {
            case '+':
            case '-':
                 _result = _sum_string(_first_expression.get_expression(), _second_expression.get_expression(), opr);
                 size_result = _result.size();
                
                 while (size_result < _size_lagest_expression)
                 {
                      _insert_space_on_result();
                      size_result = _result.size();
                 }
            break;

            case '*':
                _result = _multiply_string(_first_expression.get_expression(), _second_expression.get_expression());
            default:
            break;
        }
    }
    std::string _multiply_string(const std::string& str1, const std::string& str2)
    {
        std::string str_num1 = _removeNonDigits(str1);
        std::string str_num2 = _removeNonDigits(str2);
        std::string result = "";
        int carry = 0, sum = 0, diff_size = 0;
        int size_greatest_str = str_num1.size() > str_num2.size() ? str_num1.size() : str_num2.size();

        str_num1 = _padWithZeros(str_num1, size_greatest_str);
        str_num2 = _padWithZeros(str_num2, str_num2.size() == 1 ? 0 : size_greatest_str);

        for (int i = str_num2.size() - 1; i >= 0; i--)
        {
            bool is_padding = false;
            diff_size = 0;
            for (int j = 0; j < str_num1.size(); j++)
            {
                if (str_num1[j] == '0')
                {
                    is_padding = true;
                }
                else
                {
                    is_padding = false;
                    diff_size = j;
                    break;
                }
            }
            for (int j = str_num1.size() - 1; j >= diff_size; j--)
            {
                sum = (str_num1[j] - '0') * (str_num2[i] - '0') ;
                sum += (sum == 0) ? 0 : carry;
                result += (sum % 10) + '0';
                carry = sum / 10;
            }

            if (carry)
            {
                result += carry + '0';
                carry = 0;
            }
                

            result += '\n';
        }

        result = _add_spaces_on_multiply(result);
        result.erase(result.size() - 1);
        return result;
    }

    std::string _add_spaces_on_multiply(const std::string& input) 
    {
        std::istringstream ss(input);
        std::string line;
        std::vector<std::string> lines;

        while (std::getline(ss, line, '\n'))
        {
            std::string line_temp = line;

            for (int i = line_temp.size() - 1; i > 0 ; i--)
          {
                if (line[i] == '0')
                {
                    line.erase(i,1);
                    line += ' ';
                }
                else
                    break;
            }

            lines.push_back(line);

        }

        std::string result;
        std::string l_old = "";
        int spacesNeeded = lines.size() - 1;
        for (auto& l : lines) {

            l.insert(l.end(), spacesNeeded, ' ');

            if (l_old != "")
            {
                while (l.size() < l_old.size() - 1)
                {
                    l.insert(l.end(), 1, ' ');
                }
            }

            l_old = l;
            std::reverse(l.begin(), l.end());
            result += l + '\n';
            spacesNeeded -= 1;
        }

        return result;
    }

    std::string _padWithZeros(const std::string& str, int size) {
        std::string padded = str;
        while (padded.size() < size) {
            padded.insert(padded.begin(), '0');
        }
        return padded;
    }
    std::string _sum_string(const std::string& str1, const std::string& str2, char opr)
    {
        std::string str_num1 = _removeNonDigits(str1);
        std::string str_num2 = _removeNonDigits(str2);
        std::string result_r = "";
        int size_greatest_str = str_num1.size() > str_num2.size() ? str_num1.size() : str_num2.size();
        int carry = 0, sum = 0;

        str_num1 = _padWithZeros(str_num1, size_greatest_str);
        str_num2 = _padWithZeros(str_num2, size_greatest_str);

        for (int i = size_greatest_str - 1; i >= 0 || carry; i--)
        {
            if (opr == '+') 
            {
                if (i < 0)
                {
                    result_r += '1';
                    carry = 0;
                }
                else
                {
                    sum = (str_num1[i] - '0') + (str_num2[i] - '0') + carry;
                    result_r += (sum % 10) + '0';
                    carry = sum / 10;
                }
            }
            else if (opr == '-')
            {
                {
                    int num1 = str_num1[i] - '0';
                    int num2 = str_num2[i] - '0';

                    if (num1 >= num2)
                    {
                        sum = num1 - num2 - carry;
                        carry = 0;
                    }
                    else
                    {
                        sum = 10 + num1 - num2 - carry;
                        carry = 1;
                    }
                }

                result_r += sum + '0';
            }
        }

        std::string result(result_r.rbegin(), result_r.rend());
        result_r = result;

        for (int i = 0; i < result_r.size() - 1;)
        {
            if (result_r[0] == '0')
                result_r.erase(0, 1);
            else
                break;
        }

        return result_r;
        
    }

    std::string _removeNonDigits(const std::string& input) {
        std::string result;
        for (char c : input) {
            if (isdigit(c)) {
                result += c;
            }
        }
        return result;
    }

    void _write_first_result_line()
    {
        _drawing += _result;
    }

    void _write_second_result_line()
    {
        if ((_first_expression.get_opr() != '*') || ((_first_expression.get_opr() == '*') && (_removeNonDigits(_second_expression.get_expression()).size() == 1)))
            return;

        _jump_line();
        _drawing += _result2;
        _jump_line();
    }

    void get_second_result_line()
    {
        std::vector<std::string> lines;
        std::istringstream ss(_result);
        std::string line;
        std::string result = "0";
        std::string temp = "0";

        if ((_first_expression.get_opr() != '*') || ((_first_expression.get_opr() == '*') && (_removeNonDigits(_second_expression.get_expression()).size() == 1)))
            return;

        while (std::getline(ss, line, '\n'))
        {
            lines.push_back(line);
        }

        for (int i = 0; i < lines.size(); i++)
        {
            std::string dozens = std::string(i, '0');
            result = _sum_string(result, lines[i] + dozens, '+');
        }

        _result2 =  result;

    }

    void _assing_expression()
    {
        char opr = 0;
        std::string expr_1, expr_2;

        if (_raw_drawing.find('+') != std::string::npos)
            opr = '+';
        else if (_raw_drawing.find('-') != std::string::npos)
            opr = '-';
        else if (_raw_drawing.find('*') != std::string::npos)
            opr = '*';

        expr_1 = _raw_drawing.substr(0, _raw_drawing.find(opr));
        expr_2 = _raw_drawing.substr(_raw_drawing.find(opr)+1);

        _first_expression.set_expression_number(1);
        _first_expression.set_opr(opr);
        _first_expression.set_expression(expr_1);

        _second_expression.set_expression_number(2);
        _second_expression.set_opr(opr);
        _second_expression.set_expression(expr_2);

    }
};


std::string print_drawing(std::string raw_expression)
{
    ArithDrawing drawing(raw_expression);

    return drawing.get_drawing();

}

int main() {

    int t;
    std::cin >> t;
    std::vector<std::string> expression(t);

    for (int i = 0; i < t; i++)
    {
        std::cin >> expression[i];
    }

    for (int i = 0; i < t; i++)
    {
        std::cout << print_drawing(expression[i]) <<endl;
    }
    return 0;
}