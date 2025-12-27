#include <iostream>
using namespace std;

extern "C" {
    long long suma(long long a, long long b);
    long long resta(long long a, long long b);
    long long multiplicacion(long long a, long long b);
    long long division(long long a, long long b);
}

int main() {
    long long a, b;

    cout << "Enter the first number: ";
    cin >> a;
    cout << "Enter the second number: ";
    cin >> b;

    cout << "Sum: " << suma(a, b) << endl;
    cout << "Subtraction: " << resta(a, b) << endl;
    cout << "Multiplication: " << multiplicacion(a, b) << endl;

    if (b != 0)
        cout << "Division: " << division(a, b) << endl;
    else
        cout << "Division: Error, division by zero" << endl;

    return 0;
}
