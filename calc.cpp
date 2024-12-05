#include <string>
#include <stack>

// checks the operator and creates operands
double calc(double a, double b, char op) {
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    if (op == '*') return a * b;
    if (op == '/') return a / b;
    return 0;
}

// makes sure pemdas is used
int pemdas(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// creates stacks for the nums  and operators to easily store
double evaluate(const std::string& expr) {
    std::stack<double> numbers; 
    std::stack<char> operators; 