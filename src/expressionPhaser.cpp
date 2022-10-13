#include "expressionPhaser.h"
#include "function.cpp"
#include "expression.h"
#include <map>
#include <stack>
#include <vector>
#include <string>
#include <cstring>

using std::isdigit;
using std::string;
using std::vector;
using std::stack;
using std::map;

enum stringType {
    NUMBER = 0, 
    VARIABLE = 1, 
    FUNCTION = 2, 
    OPERATOR = 3
};

stack<string> operators;
stack<number> nums;
vector<string> strings;
vector<stringType> string_types;
map<string, expression> &var;
map<string, bool> &functions;

// Divide string to parts: numbers, variables, functions, and operators
// Consider situations that may occur in the input
// 1 - Numbers: directly convert to 'number' class
// 2 - Variables: use the map to convert to number
// 3 - Operators: +, -, *, /, and ()
// 4 - Math functions: consider as operators, together with (
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

void caculate() {

}

expression caculate_expression(expression e, map<string, expression> &variables) {
    var = variables;
    divide_string(e);

    int strings_size = strings.size();
    for (int i = 0; i < strings_size; i++) {

    }
}