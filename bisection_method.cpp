/* 
Topic: Bisection method, to find roots of an algebraic polynomial equation.
Course: Numerical Methods and Random Process
Course taught by : Dr. Ramakrishnan Bandi
Author: Kushashwa Ravi Shrimali [16100035]
Contributors: (none as of now) [if any]
*/

#include <iostream>
#include <cstdlib>
#include <math.h>

using namespace std;

float function_value(float, int, int*);

int main(int argc, char** argv) {
    // input the polynomial degrees
    int N; cin >> N; // maximum degree
    int* coefficients = new int; // array, and it's memory allocation

    for(int i = 0; i <= N; i++) {
        cin >> *(coefficients + i);
    }

    cout << endl;

    // Output equation
    for(int i = N; i >= 0; i--) {
        cout << *(coefficients + i) << "*" << "x" << " " << i << " ";
        if(i != 0) {
            cout << "+" << " ";
        }
        else {
            cout << endl;
        }
    }

    int max = 100;
    int min = -100;
    int temp = N;
    float sum_final_positive = 2147483.0;
    float sum_final_negative = -2147483.0;
    float sum_previous_positive = 2147483.0;
    float sum_previous_negative = -2147483.0;

    while(min <= max) {
        float sum = function_value(min, temp, coefficients);
        temp = N;
        // cout << "sum is : " << sum  << endl;
        if(sum > 0) {
            if(sum < sum_final_positive)
                sum_final_positive = sum;
            // else
            //     sum_final_positive = sum_previous_positive;
        }
        else if(sum < 0) {
            if(sum > sum_final_negative) 
                sum_final_negative = sum;
            else
                sum_final_negative = sum_previous_negative;
        }
        sum_previous_positive = sum;
        sum_previous_negative = sum;
        min++;
        // cout << sum_final_positive << endl;
    }
    cout << "sum_final_positive " << sum_final_positive << endl;
    cout << "sum_final_negative " << sum_final_negative << endl;

    // for simplicity
    float a = sum_final_positive;
    float b = sum_final_negative;

}

float function_value(float x, int N, int* coefficients){
    // x is value for independent variable
    // N is degree
    // coefficients is the array
    float sum = 0;
    while(N >= 0) {
        sum += *(coefficients + N) * pow(x, N);
        N--;
    }
    return sum;
}