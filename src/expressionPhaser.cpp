// Code Reference: https://blog.csdn.net/qq_45768060/article/details/105414612

#include "expressionPhaser.h"
#include "function.cpp"
#include "expression.h"
#include <map>
#include <stack>
#include <vector>
#include <string>
#include <cstring>
#include <functional>

using std::isdigit;
using std::function;
using std::string;
using std::vector;
using std::stack;
using std::map;

stack<string> operators;
stack<number> nums;
vector<string> strings;
vector<stringType> string_types;
map<string, expression> &var;
map<string, function<number(number)>> &functions;

// Divide string to parts: numbers, variables, functions, and operators
// Consider situations that may occur in the input
// 1 - Numbers: directly convert to 'number' class
// 2 - Variables: use the map to convert to number
// 3 - Operators: +, -, *, /, and ()
// 4 - Math functions
// assume that input is valid
void divide_string(expression e) {
    string &str = e.str;
    string num, word;
    bool is_variable = false;
    strings.clear();
    string_types.clear();

    int len = str.length(), i = 0;
    while (i < len) {
        if (isdigit(str[i]) || str[i] == '.')
            num.push_back(str[i++]);
        else {
            if (num.length()) {
                strings.push_back(num);
                string_types.push_back(NUMBER);
                num.erase();
            }
            // funtion name or variable name
            if (isalpha(str[i]))
                word.push_back(str[i++]);
            else {
                if (word.length()) {
                    strings.push_back(word);
                    if (var.count(word))
                        string_types.push_back(VARIABLE);
                    if (functions.count(word))
                        string_types.push_back(FUNCTION);
                    word.erase();
                }
                else {
                    // operators and ( )
                    if (!isspace(str[i])) {
                        strings.push_back(str.substr(i, i));
                        string_types.push_back(OPERATOR);
                    }
                }
            }
        }
    }
    if (num.length()) strings.push_back(num);
    if (word.length()) strings.push_back(word);
}

bool is_equation(expression e) {
    string &str = e.str;
    int len = str.length();

    for (int i = 0; i < len; i++)
        if (str[i] == '=') return true;

    return false;
}

bool is_function(string s) {
    if (s == "+" || s == "-" || s == "*" || s == "/" || s == "%" || s == "^" || s == "(" || s == ")")
        return true;
    else return false;
}

void caculate(bool is_function) {
    if (is_function) {
        function<number(number)> &func = functions[operators.top()];
        number top_num = nums.top();
        nums.pop();
        nums.push(func(top_num));
        operators.pop();
        return;
    }
    
    
}

// Priority List:
operatorPriority operator_priority(char ch) {
    if (ch == '+' || ch == '-')
        return LOW;
    if (ch == '*' || ch == '/' || ch == '%')
        return MEDIUM;
    if (ch == '^')
        return HIGH;
    return NOT_OPERATOR;
}

expression caculate_expression(expression e, map<string, expression> &variables) {
    var = variables;
    divide_string(e);

    int strings_size = strings.size();
    for (int i = 0; i < strings_size; i++) {
        if (string_types[i] == OPERATOR) {
            if (operator_priority(strings[i][0]) == LOW) {
                while (!operators.empty() && operators.top()[0] != '(')
                    caculate(false);
                operators.push(strings[i]);
            }
            // *, /, %, high priority
            else if (operator_priority(strings[i][0] == MEDIUM)) {
                while (!operators.empty() && operator_priority(operators.top()[0]) == MEDIUM)
                    caculate(false);
                operators.push(strings[i]);
            }
            else if (operator_priority(strings[i][0] == HIGH))
                operators.push(strings[i]);
            else if (strings[i][0] == '(')
                operators.push(strings[i]);
            else if (strings[i][0] == ')') {
                while (operators.top() != "(")
                    caculate(false);
                operators.pop();
                if (!operators.empty())
                    if (is_function(operators.top()))
                        caculate(true);
            }
        }
    }
}