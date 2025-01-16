#include <iostream>
#include <ctype.h>
#include "stack.h"

int main() {
    char input;
    Stack<int> stack;
    cout << "This is a RPN calculator. Enter operands and operators:" << endl;
    while (true){
        cin >> input;
        if(isdigit(input)){
            int number = input - 48;
            stack.push(number);
        }else if (input == '+'){
            int nr1, nr2;
            if (stack.pop(nr1) && stack.pop(nr2)){
                int sum = nr1 + nr2;
                stack.push(sum);
            }else{
                cout << "Can't get number in stack to calculate" << endl;
            }
        }else if (input == '-'){
            int nr1, nr2;
            if (stack.pop(nr1) && stack.pop(nr2)){
                int subtract = nr2-  nr1;
                stack.push(subtract);
            }else{
                cout << "Can't get number in stack to calculate" << endl;
            }
        }else if (input == '='){
            int top_val;
            if(stack.top_value(top_val)){
                cout <<"Top value is " << top_val << endl;
            }else{
                cout << "No value in stack" << endl;
            }
        }else if (input == 'Q'){
            cout << "Stack contained " << endl;
            stack.print();
            break;
        }else{
            cout << "Invalid input" << endl;
        }
    }

    return 0;
}
