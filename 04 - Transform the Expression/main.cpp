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

class Parents
{
public:

    uint16_t deepth;
    std::string raw_logic;
    std::string resolved_logic;

    Parents()
    {
        deepth = 0;
        raw_logic = "";
        resolved_logic = "";
    }

    void set_deepth(uint16_t num)
    {
        deepth = num;
    }
    void set_logic(std::string logic)
    {
        raw_logic = logic;
    }
    uint16_t get_deepth(uint16_t num)
    {
        return deepth;
    }
    bool get_is_resolved()
    {
        return is_resolved;
    }

    std::string get_operands()
    {
        return operands;
    }

    std::string get_operators()
    {
        return operators;
    }

    std::vector<uint16_t> get_queue()
    {
        return queue;
    }

    bool resolve()
    {
        if (raw_logic.at(0) == '\0')
            return false;
        else
        {
            _find_operators_and_operands(raw_logic);
            resolved_logic = operands + operators;
            is_resolved = true;
            return true;
        }
    }

    std::string get_solution()
    {
        if (resolve())
            return resolved_logic;
        else
            return "";
    }

private:

    std::vector<uint16_t> queue;
    std::string operators = "";
    std::string operands = "";
    bool is_resolved = false;

    void _find_operators_and_operands(std::string str)
    {
        std::string operators = OPERATORS;
        std::string collections_operators = "";
        size_t inx_operators = operators.size() - 1;

        for (int i = 0; i < str.size() - 1; i++)
        {
            for (size_t j = inx_operators; j > 0; j--)
            {
                if (str[i] == operators[j])
                {
                    collections_operators += str[i];
                }
                else
                {
                    operands += str[i];
                }
            }
        }
    }

};

std::vector<Parents> finder_parents(std::string str_logic)
{
    size_t size_str_logic = str_logic.size();
    std::vector<Parents> parents(0);
    size_t temp_in = 0, temp_out = 0;
    uint8_t count = 0;
    size_t i = 0;
    bool opened_parents = false;
    bool closed_parents = false;
    bool detected_interval = false;
    std::string temp_string = "";

    while( (str_logic.find('(') != -1) || (str_logic.find('(') != -1) )
    {

        if (str_logic[i] == '(')
        {
            temp_in = i;
            opened_parents = true;
        }

        else if (str_logic[i] == ')')
        {
            if (opened_parents)
            {
                temp_out = i;
                detected_interval = true;
                opened_parents = false;
            }
        }

        if (detected_interval)
        {
            parents.resize(parents.size() + 1);

            for (size_t j = temp_in + 1; j < temp_out; j++)
            {
                temp_string += str_logic[j];

            }
            
            parents[count].set_deepth(count);
            parents[count].set_logic(temp_string);
            
            temp_string = '(' + temp_string + ')';
            str_logic.replace(temp_in, temp_string.size(), "#" + std::to_string(count));
            temp_string = "";
            count++;
        }
        if (detected_interval)
        {
            i = 0;
            detected_interval = false;
        }
        else
            i++;
    }

    return parents;

}


std::string brackets2rpn(std::string str)
{
    std::vector<Parents> parents;

    parents = finder_parents(str);


    /*
    @TODO: ADICIONAR LÓGICA PARA ORDENAR PARENTS EM PROFUNDIDADE E SUBTITUIR AS STRINGS PELAS LÓGICAS RESOLVIDAS
    */
}

int main()
{

    std::vector<string> str(0);
    uint8_t t = 0;
    cin >> t;

    if (t >= 1)
        str.resize(t);

    for (int i = 0; i < t; i++)
    {
        cin >> str[i];
    }

    for (int i = 0; i < t; i++)
    {
        cout >> str[i];
    }


    return 0;
}