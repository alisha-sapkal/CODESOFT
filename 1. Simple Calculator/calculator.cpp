#include<iostream>
using namespace std;

class calculator{
    public:

    void displayMenu() {
        cout << "Simple Calculator\n";
        cout << "1. Addition\n";
        cout << "2. Subtraction\n";
        cout << "3. Multiplication\n";
        cout << "4. Division\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
    }

    double getOperands(string str){
        double num;
        cout << str ;
        cin >> num;
        return num;
    }

    double calculate(char operation){
        double num1, num2;
        switch(operation){
            case 1 :
                num1 = getOperands("Enter first number: ");
                num2 = getOperands("Enter second number: ");
                return num1+num2;
            case 2 :
                num1 = getOperands("Enter first number: ");
                num2 = getOperands("Enter second number: ");
                return num1-num2;
            case 3 :
                num1 = getOperands("Enter first number: ");
                num2 = getOperands("Enter second number: ");
                return num1*num2;
            case 4:
                num1 = getOperands("Enter first number: ");
                num2 = getOperands("Enter second number: ");
                if (num2 == 0) {
                    cout << "Error: Division by zero is not allowed." << endl;
                    return 0;
                }
                return num1 / num2;

            default :
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
};

int main(){
    calculator cal;
    while(true){
        cal.displayMenu();
        int op;
        cin >> op;
        if(op == 5){
            cout << "Exiting the program." << endl;
            break;
        }
        cout << "Answer = " << cal.calculate(op) << endl;
    }
}