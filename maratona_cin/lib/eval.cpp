#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define INF 1e18
const ll MOD = 1e9+7;

long long eval(string expression) {
    stack<long long> numbers;
    stack<char> operators;

    auto calculate = [&]() {
        long long secondNumber = numbers.top();
        numbers.pop();

        long long firstNumber = numbers.top();
        numbers.pop();

        char currentOperator = operators.top();
        operators.pop();

        if (currentOperator == '+') numbers.push(firstNumber + secondNumber);
        else if (currentOperator == '-') numbers.push(firstNumber - secondNumber);
        else if (currentOperator == '*') numbers.push(firstNumber * secondNumber);
        else if (currentOperator == '/') numbers.push(firstNumber / secondNumber);
    };

    auto priority = [&](char currentOperator) {
        if (currentOperator == '+' || currentOperator == '-') return 1;
        if (currentOperator == '*' || currentOperator == '/') return 2;
        return 0;
    };

    for (int position = 0; position < (int)expression.size(); position++) {
        char currentCharacter = expression[position];

        if (isspace(currentCharacter)) continue;

        if (isdigit(currentCharacter)) {
            long long currentNumber = 0;

            while (position < (int)expression.size() && isdigit(expression[position])) {
                currentNumber = currentNumber * 10 + expression[position] - '0';
                position++;
            }

            numbers.push(currentNumber);
            position--;
        }
        else if (currentCharacter == '(') {
            operators.push(currentCharacter);
        }
        else if (currentCharacter == ')') {
            while (!operators.empty() && operators.top() != '(') {
                calculate();
            }
            operators.pop();
        }
        else {
            while (!operators.empty() && operators.top() != '(' &&
                   priority(operators.top()) >= priority(currentCharacter)) {
                calculate();
            }
            operators.push(currentCharacter);
        }
    }

    while (!operators.empty()) {
        calculate();
    }

    return numbers.top();
}

void solve() {}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) {solve();}
}