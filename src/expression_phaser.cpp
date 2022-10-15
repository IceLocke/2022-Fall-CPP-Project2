// Code Reference: https://blog.csdn.net/qq_45768060/article/details/105414612

#include "../include/expression_phaser.h"
#include <map>
#include <stack>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <functional>

using std::isdigit;
using std::function;
using std::string;
using std::vector;
using std::stack;
using std::cerr;
using std::cout;
using std::endl;
using std::map;

ExpressionPhaser::ExpressionPhaser(map<string, number> *vari, map<string, function<number(number)>> *func){
    this->var = vari;
    this->functions = func;
}

bool is_operator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
           ch == '%' || ch == '^' || ch == '(' || ch == ')';
}

bool is_function(string s) {
    if (s == "sin" || s == "cos" || s == "arctan" || s == "ln" || s == "exp")
        return true;
    else return false;
}

// Divide string to parts: numbers, variables, functions, and operators
// Consider situations that may occur in the input
// 1 - Numbers: directly convert to 'number' class
// 2 - Variables: use the map to convert to number
// 3 - Operators: +, -, *, /, and ()
// 4 - Math functions
// assume that input is valid
void ExpressionPhaser::divide_string(expression e) {
    cout << "dividing string" << endl;

    string &str = e.str;
    string num, word;
    bool is_variable = false;
    strings.clear();
    string_types.clear();

    int len = str.length(), i = 0;
    while (i < len) {
        if (isspace(str[i])) {
            i++;
            continue;
        }
        if (isdigit(str[i]) || str[i] == '.') {
            num.push_back(str[i]);
        }
        else {
            if (num.length()) {
                strings.push_back(num);
                string_types.push_back(NUMBER);
                num.erase();
            }
            // funtion name or variable name
            if (isalpha(str[i]))
                word.push_back(str[i]);
            else {
                if (word.length()) {
                    strings.push_back(word);
                    cout << word << endl;
                    if (var->count(word))
                        string_types.push_back(VARIABLE);
                    else if (is_function(word))
                        string_types.push_back(FUNCTION);
                    else {
                        cerr << word << ": Undefined function or variable!" << endl;
                        return;
                    }
                    word.erase();
                }
                if (is_operator(str[i])) {
                    strings.push_back(str.substr(i, 1));
                    string_types.push_back(OPERATOR);
                }
                else {
                    if (!isspace(str[i]))
                        cerr << "Expression have undefined character!" << endl;
                }
            }
        }
        i++;
    }
    if (num.length()) strings.push_back(num);
    if (word.length()) strings.push_back(word);

    cout << strings.size() << endl;
    for (int i = 0; i < strings.size(); i++)
        cout << strings.at(i) << " ";
    cout << endl;
    for (int i = 0; i < strings.size(); i++)
        cout << string_types[i] << " ";
    cout << endl;
}

bool ExpressionPhaser::is_equation(expression e) {
    string &str = e.str;
    int len = str.length();

    for (int i = 0; i < len; i++)
        if (str[i] == '=') return true;

    return false;
}

void ExpressionPhaser::calculate_top(bool is_function) {
    cout << "caculate" << endl;
    if (is_function) {
        function<number(number)> func = (*functions)[operators.top()];
        number top_num = nums.top();
        nums.pop();
        nums.push(func(top_num));
        operators.pop();
        return;
    }

    // from left to right, get numbers from up to down
    char op = operators.top()[0];
    operators.pop();
    number b = nums.top();
    nums.pop();
    number a = nums.top();
    nums.pop();
    switch (op) {
        case '+': nums.push(a + b); break;
        case '-': nums.push(a - b); break;
        case '*': nums.push(a * b); break;
        case '/': nums.push(a / b); break;
        case '%': nums.push(a % b); break;
        case '^': nums.push(a ^ b); break;
        default:
            cerr << "Unkown operator!" << endl;
            break;
    }
}

ExpressionPhaser::OperatorPriority ExpressionPhaser::operator_priority(char ch) {
    if (ch == '+' || ch == '-')
        return LOW;
    if (ch == '*' || ch == '/' || ch == '%')
        return MEDIUM;
    if (ch == '^')
        return HIGH;
    return NOT_OPERATOR;
}

number ExpressionPhaser::calculate_expression(expression e) {
    divide_string(e);
    int strings_size = strings.size();
    for (int i = 0; i < strings_size; i++) {
        cout << "start priority processing " << i << endl;
        cout << nums.size() << " " << operators.size() << endl;
        if (string_types[i] == OPERATOR || string_types[i] == FUNCTION) {
            // pass low priority operators, deal with medium priority
            if (operator_priority(strings[i][0]) == LOW) {
                while (!operators.empty() && operators.top()[0] != '(')
                    calculate_top(false);
                operators.push(strings[i]);
            }
            // deal with operators with higher priority
            else if (operator_priority(strings[i][0]) == MEDIUM) {
                while (!operators.empty() && operator_priority(operators.top()[0]) == MEDIUM)
                    calculate_top(false);
                operators.push(strings[i]);
            }
            else if (operator_priority(strings[i][0]) == HIGH)
                operators.push(strings[i]);
            else if (strings[i][0] == '(')
                operators.push(strings[i]);
            else if (strings[i][0] == ')') {
                while (operators.top() != "(")
                    calculate_top(false);
                operators.pop();
                if (!operators.empty())
                    if (is_function(operators.top()))
                        calculate_top(true);
            }
            else if (is_function(strings[i]))
                operators.push(strings[i]);
        }
        else {
            number num;
            cout << string_types[i] << " "<< endl;
            if (var->count(strings[i]))
                num = (*var)[strings[i]];
            else
                num = number(strings[i]);
            cout << "push number " << num.to_string() << endl;
            nums.push(num);
        }
    }
    while (!operators.empty())
        calculate_top(false);
    
    number res = nums.top();
    nums.pop();

    return res;
}