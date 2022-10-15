// to be implemented high precision...

#include <cmath>
#include <functional>
#include <map>
#include <cstring>
using std::map;
using std::function;

map<string, function<number(number)>> functions;

number sin_f(number x) {
    return number(std::sin(x.to_longdouble()));
}

number cos_f(number x) {
    return number(std::cos(x.to_longdouble()));
}

number arctan_f(number x) {
    return number(std::atan(x.to_longdouble()));
}

number ln_f(number x) {
    return number(std::log10(x.to_longdouble()));
}

number exp_f(number x) {
    return number(std::exp(x.to_longdouble()));
}

map<string, function<number(number)>> get_functions() {
    function<number(number)> sin_func = sin_f,
                             cos_func = cos_f,
                             arctan_func = arctan_f,
                             ln_func = ln_f,
                             exp_func = exp_f;
    functions["sin"] = sin_func;
    functions["cos"] = cos_func;
    functions["arctan"] = arctan_func;
    functions["ln"] = ln_func;
    functions["exp"] = exp_func;
    return functions;
}