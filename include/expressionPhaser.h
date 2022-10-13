#include <map>
#include "expression.h"

void divide_string(expression e);
bool is_equation(expression e);
number caculate_expression(expression e, map<string, number> &variables);