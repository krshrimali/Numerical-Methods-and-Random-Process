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
    if(argc != 2) {
        cerr << "Give proper arguments " << endl;
        exit(1);
    }
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

    int max = 10;
    int min = -10;
    int temp = N;
    float sum_final_positive = 2147483.0;
    float sum_final_negative = -2147483.0;
    float sum_previous_positive = 2147483.0;
    float sum_previous_negative = -2147483.0;

    while(min <= max) {
        float sum = function_value(min, temp, coefficients);
        if(sum == 0){
            cout << "Solution is: " << min << endl;
            return -1;
        }
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
            // else
            //     sum_final_negative = sum_previous_negative;
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

    float avg;
    int count = 0;
    float solution;
    float flag_a = 0;
    float flag_b = 0;
    while(true) {
        // cout << " a b " << a << b << endl;
        // if(count > 1) {
        //     if(flag_a == 1) {
        //         avg = (a + b)/2.0;
        //     }
        //     else if(flag_b == 1) {
        //         avg = (a + b)/2.0;
        //     }
        // }
        // else {
        //     avg = (a + b)/2.0;
        // }
        if(count == 0) avg = (a + b)/2.0;
        // cout << x << endl;
        float sum_new = function_value(avg, N, coefficients);
        cout << avg << " " <<  sum_new << endl;
        if(sum_new * function_value(a, N, coefficients) < 0) {
            cout << "function_value(a, N, coefficients) " << function_value(a, N, coefficients) << endl;
            // solution = x;
            b = avg;
            avg = (a + avg)/2.0;
            flag_b = 1;
            flag_a = 0;
        }
        else if(sum_new * function_value(b, N, coefficients) < 0) {
            cout << "function_value(b, N, coefficients) " << function_value(b, N, coefficients) << endl;
            // solution = x;
            a = avg;
            avg = (b + avg)/2.0;
            flag_a = 1;
            flag_b = 0;
            // solution = x;
            // b = x;
        }
        else if(sum_new == 0) {
            // cout << "Solution is: " << x << endl;
            return -1;
        }
        cout << "x is: " << avg << endl;
        // cout << x << " a is: " << a << " b is: " << b << endl;
        // cout << " " << function_value(x, N, coefficients) << endl;;
        // cout.precision(atoi(argv[1]));
        count += 1;
        if(count == 20) {
            break;
        }
    }
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