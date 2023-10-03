/*
Transform the algebraic expression with brackets into RPN form (Reverse Polish Notation). Two-argument operators: +, -, *, /, ^ (priority from the lowest to the highest), brackets ( ). Operands: only letters: a,b,...,z. Assume that there is only one RPN form (no expressions like a*b*c).

Input
t [the number of expressions <= 100]
expression [length <= 400]
[other expressions]
Text grouped in [ ] does not appear in the input file.

Output
The expressions in RPN form, one per line.
Example
Input:
3
(a+(b*c))
((a+b)*(z+x))
((a+t)*((b+(a+c))^(c+d)))
Output:
abc*+
ab+zx+*
at+bac++cd+^*
*/
#include <iostream>
#include <vector>
#include <string>

using namespace std;


#define OPERATORS "+-*/^" /* Keep the most priority on the end*/
#define MAX_EXPRESSIONS_SIZE 400

class Stack
{
public:

    std::vector<std::string> get_stack()
    {
        return _raw_stack;
    }

    void set_stack(std::string stack)
    {
        std::vector<std::string> splited_stack;

        if (stack.size() > 0)
        {
            splited_stack.resize(stack.size());
        }

        for (size_t i = 0; i < splited_stack.size(); i++)
        {
            splited_stack[i] = stack[i];
        }


        _raw_stack = splited_stack;

        _raw_stack.insert(_raw_stack.begin(), "(");
        _raw_stack.push_back(")");
        _update_stack_size();
    }

    std::string resolve()
    {
        _resolve_brackets();
        return _raw_stack[0];
    }

private:
    std::vector<std::string> _raw_stack;

    size_t _stack_size = 0;

    void _resolve_brackets()
    {
        int start = 0, end = 0, i = 0;
        std::string temp_str = "";

        while (_is_breackets(_raw_stack))
        {
            temp_str = "";

            if (_raw_stack[i] == "(") /* mark the start of brackets*/
            {
                start = i;
            }
            else if (_raw_stack[i] == ")")
            {
                end = i;
                _resolve(start, end);
                i = 0;
                continue;
            }
            i++;
        }
    }

    void _update_stack_size()
    {
        _stack_size = _raw_stack.size();
    }

    void _resolve(int start, int end)
    {
        std::string _operators = OPERATORS;
        std::vector<std::string> op_str(_operators.size());
        std::string str = "", operators = "", operands = "";
        size_t inx_operators = _operators.size() - 1;
        bool is_operand = true;

        for (size_t i = 0; i < _operators.size(); i++)
        {
            op_str[i] += _operators[i];
        }

        for (int i = start + 1 ; i < end; i++)
        {
            is_operand = true;

            for (int j = inx_operators; j >= 0; j--)
            {
                if (_raw_stack[i] == op_str[j])
                {
                    operators += _raw_stack[i];
                    is_operand = false;
                    break;
                }
            }
            if (is_operand)
            {
                operands += _raw_stack[i];
            }
        }

        str = operands + operators;
        _raw_stack.erase(_raw_stack.begin() + start , _raw_stack.begin() + end + 1);
        _raw_stack.insert(_raw_stack.begin() + start, str);
    }

    bool _is_breackets(std::vector<string> str)
    {
        for (size_t i = 0; i < str.size(); i++)
        {
            if ((str[i] == "(") || (str[i] == ")"))
                return true;
        }

        return false;
    }
};

int main()
{
    std::vector<string> str(0);
    Stack stack;
    int t = 0;

    cin >> t;

    if (t >= 1)
        str.resize(t);

    for (int i = 0; i < t; i++)
    {
        cin >> str[i];
    }

    for (int i = 0; i < t; i++)
    {
        stack.set_stack(str[i]);
        cout << stack.resolve() << endl;
    }

    return 0;
}