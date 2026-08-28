#include <bits/stdc++.h>
using namespace std;
#include <string>
#include <sstream>
int calculate(int a, int b, char op)
{
    if (op == '+')
    {
        return a + b;
    }
    else if (op == '-')
    {
        return a - b;
    }
    else if (op == '*')
    {
        return a * b;
    }
    else if (b != 0 && op == '/')
    {
        return a / b;
    }
    else if (op == '%')
    {
        if (b != 0)
            return a % b;
    }

    return 0;
}
int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;

    if (op == '*' || op == '/')
        return 2;

    return 0;
}

int calculateTop(stack<int> &Operands, stack<char> &operators)
{
    if (Operands.size() < 2 || operators.empty())
        throw runtime_error("Invalid Expression");

    int right = Operands.top();
    Operands.pop();
    int left = Operands.top();
    Operands.pop();
    char operator_char = operators.top();
    operators.pop();
    return calculate(left, right, operator_char);
}

bool check_precidence(char c, char t)
{
    int cp = precedence(c);
    int tp = precedence(t);
    return cp > tp;
    // it means the upcoming operator have high precendance so push it direcly
}

bool is_openingBracket(char c)
{
    return c == '(' || c == '[' || c == '{';
}
bool is_closingBracket(char c)
{
    return c == ')' || c == ']' || c == '}';
}

int Calculator(string expression, stack<char> &operator_symbol, stack<int> &operand)
{
    for (char c : expression)
    {
        if (isdigit(c))
        {
            operand.push(c - '0');
        }
        else
        {
            if (operator_symbol.empty())
            {
                operator_symbol.push(c);
            }
            else
            {
                if (is_openingBracket(c))
                {
                    operator_symbol.push(c);
                }
                else if (is_closingBracket(c))
                {
                    while (!operator_symbol.empty() && operator_symbol.top() != '(' &&
                           operator_symbol.top() != '[' &&
                           operator_symbol.top() != '{')
                    {
                        operand.push(calculateTop(operand, operator_symbol));
                    }
                    if (!operator_symbol.empty())
                        operator_symbol.pop();
                }
                else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%')
                {

                    if (check_precidence(c, operator_symbol.top()))
                    {
                        operator_symbol.push(c);
                    }
                    else
                    {
                        while (!operator_symbol.empty() && !check_precidence(c, operator_symbol.top()))
                        {
                            operand.push(calculateTop(operand, operator_symbol));
                        }
                        operator_symbol.push(c);
                    }
                }
                else
                {
                    throw runtime_error("Invalid Character");
                }
            }
        }
    }
    while (!operator_symbol.empty())
    {
        if (is_openingBracket(operator_symbol.top()))
            throw runtime_error("Mismatched bracket");

        operand.push(calculateTop(operand, operator_symbol));
    }

    return operand.top();
}

int main()
{
    while (true)
    {
        cout << "Enter 1 to Calculate\n0 to close the program" << endl;
        int a;
        cin >> a;
        if (a == 0)
        {
            cout << "Closing the program..." << endl;
            return 0;
        }
        else if (a == 1)
        {
            cout << "Enter a Valid Expression: ";
            string expression;
            cin >> expression;
            stack<char> operator_symbol;
            stack<int> operand;
            try
            {
                cout << Calculator(expression, operator_symbol, operand) << endl;
            }
            catch (const exception &e)
            {
                cout << "Invalid expression" << endl;
            }
        }
        else
        {
            cout << "Invalid input" << endl;
        }
    }
}
