#include <iostream>
#include <cctype>
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
    std::stack<double> numbers;  // num stack
    std::stack<char> operators;   // operator stack

    for (int i = 0; i < expr.length(); i++) {
        if (isspace(expr[i])) continue; // takes spaces out of account

        if (isdigit(expr[i])) { // makes sure its a num
            double num = 0;
            while (i < expr.length() && isdigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            numbers.push(num); // adds num to stack
            i--; 
        } else if (expr[i] == '(') { // handles paren
            operators.push(expr[i]);
        } else if (expr[i] == ')') { // handles paren
            while (!operators.empty() && operators.top() != '(') {
                double b = numbers.top(); numbers.pop();
                double a = numbers.top(); numbers.pop();
                char op = operators.top(); operators.pop();
                numbers.push(calc(a, b, op));
            }
            operators.pop(); // pop the paren
        } else { // uses pemdas to evaluate what to do first and pushes to stack
            while (!operators.empty() && pemdas(operators.top()) >= pemdas(expr[i])) {
                double b = numbers.top(); numbers.pop();
                double a = numbers.top(); numbers.pop();
                char op = operators.top(); operators.pop();
                numbers.push(calc(a, b, op));
            }
            operators.push(expr[i]);
        }
    }

    while (!operators.empty()) { // all remaining op are applied to stack
        double b = numbers.top(); numbers.pop();
        double a = numbers.top(); numbers.pop();
        char op = operators.top(); operators.pop();
        numbers.push(calc(a, b, op));
    }

    return numbers.top(); // answer to eq aka last num in stack 

}

int main() { // gets user input that can be taken out for UI 
    std::string input; 
    std::cout << "Enter an equation: ";
    std::getline(std::cin, input); // reads input line 

    double result = evaluate(input); // calls the eval func
    std::cout << "Answer: " << result << std::endl; // prints answer

    return 0;
}