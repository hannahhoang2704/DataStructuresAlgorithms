#include <iostream>
#include <ctype.h>
#include "stack.h"
#define MAX_LENGTH 80
void infixTopostfix(char *infix, char *postfix);
int precedence_operator(char oper);
int evaluate_postfix(char *postfix);
int main() {
    char infix[MAX_LENGTH], postfix[MAX_LENGTH];

    cout << "Infix to postfix converter" << endl;
    cout << "Give an infix equation at one line: ";
    cin.getline(infix, MAX_LENGTH);
    infixTopostfix(infix, postfix);
    cout << "Equivalent postfix equation is: " << postfix << endl;
    int result = evaluate_postfix(postfix);
    cout << "And it's value is " << result << endl;
    return 0;
}

void infixTopostfix(char *infix, char *postfix){
    Stack<char> operators;
    int post_idx = 0;

    for (int i = 0; infix[i] != '\0'; ++i) {
        char current = infix[i];
        if (isdigit(current)) {
            postfix[post_idx++] = current;
        } else if (current == '(') {
            operators.push(current);
        } else if (current == ')') {
            char top_val;
            while (!operators.empty() && operators.top_value(top_val) && top_val != '(') {
                operators.pop(top_val);
                postfix[post_idx++] = top_val;
            }
            operators.pop(top_val);
        }else if (current == '+' || current == '-' || current == '*' || current == '/') {
            while (!operators.empty()) {
                char top_val;
                operators.top_value(top_val);
                if (precedence_operator(top_val) >= precedence_operator(current)) {
                    operators.pop(top_val);
                    postfix[post_idx++] = top_val;
                } else {
                    break;
                }
            }
            operators.push(current);
        }
    }

    while (!operators.empty()) {
        char topOperator;
        operators.pop(topOperator);
        postfix[post_idx++] = topOperator;
    }

    postfix[post_idx] = '\0';
}


int precedence_operator(char oper){
    if (oper == '*' || oper == '/') return 2;
    else if (oper == '+' || oper == '-') return 1;
    return 0;
}

int evaluate_postfix(char *postfix) {
    Stack<int> stack;
    int result;
    for (int i = 0; postfix[i] != '\0'; i++) {
        char input = postfix[i];
        if (isdigit(input)) {
            int number = input - '0';
            stack.push(number);
        } else if (input == '*') {
            int nr1, nr2;
            if (stack.pop(nr1) && stack.pop(nr2)) {
                int multiple = nr1 * nr2;
                stack.push(multiple);
            } else {
                cout << "Can't get number in stack to calculate" << endl;
            }
        } else if (input == '/') {
            int nr1, nr2;
            if (stack.pop(nr1) && stack.pop(nr2) && nr1 != 0) {
                int division = nr2 / nr1;
                stack.push(division);
            } else {
                cout << "Can't get number in stack to calculate" << endl;
            }
        } else if (input == '+') {
            int nr1, nr2;
            if (stack.pop(nr1) && stack.pop(nr2)) {
                int sum = nr1 + nr2;
                stack.push(sum);
            } else {
                cout << "Can't get number in stack to calculate" << endl;
            }
        } else if (input == '-') {
            int nr1, nr2;
            if (stack.pop(nr1) && stack.pop(nr2)) {
                int subtract = nr2 - nr1;
                stack.push(subtract);
            } else {
                cout << "Can't get number in stack to calculate" << endl;
            }
        }
    }
    if (stack.pop(result)) return result;
    else return -1;
}
