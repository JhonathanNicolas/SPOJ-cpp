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
        result = "";
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

        _write_first_line();
        _jump_line();
        _write_second_line();
        _jump_line();
        _write_hyphen_line();
        _jump_line();
        _write_result_line();

        return _drawing;
    }

private:
    Expression _first_expression;
    Expression _second_expression;
    uint8_t _size_lagest_expression;
    uint8_t number_of_result;
    std::string result;
    std::string _raw_drawing;
    std::string _drawing;

    void _write_first_line()
    {
        _drawing = _first_expression.get_expression();
    }

    void _write_second_line()
    {
        _drawing += _second_expression.get_expression();
    }

    void _write_hyphen_line()
    {
        std:string result_line(_size_lagest_expression, '-');
        _drawing += result_line;
    }

    void _jump_line()
    {
        _drawing += '\n';
    }

    std::string _get_result()
    {
        //TODO
    }

    void _write_result_line()
    {
        //TODO
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
        std::cout << print_drawing(expression[i]) << endl;
    }

    return 0;
}