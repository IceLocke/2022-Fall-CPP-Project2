#include <map>
#include "expression.h"

enum stringType {
    NUMBER = 0, 
    VARIABLE = 1, 
    FUNCTION = 2, 
    OPERATOR = 3
};

enum operatorPriority {
    NOT_OPERATOR = 0,
    LOW = 1,
    MEDIUM = 2,
    HIGH = 3
};

void divide_string(expression e);
bool is_equation(expression e);
void caculate(bool is_function);

number caculate_expression(expression e, map<string, number> &variables);