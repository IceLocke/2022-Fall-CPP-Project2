#include <map>
#include <functional>

using std::map;
using std::function;

number sin(number x);
number cos(number x);
number arctan(number x);
number ln(number x);
number exp(number x);
map<string, function<number(number)>> get_functions();

