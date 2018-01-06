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
#include <iomanip>      // std::setprecision

using namespace std;

float function_value(float, int, int*); // to calculate value of the function at given value
int compare(float x, float y, int precision); // to compare two float values with given precision

int main(int argc, char** argv) {
    if(argc != 2) {
        cerr << "Give proper arguments " << endl;
        exit(1);
    }
    // input the polynomial degrees
    int N; cin >> N; // maximum degree
    int* coefficients = new int; // array, and it's memory allocation

    // Input coefficients
    cout << "Input Coefficients: " << endl;
    for(int i = 0; i <= N; i++) {
        cin >> *(coefficients + i);
    }

    cout << endl;

    // Output equation
    cout << "Polynomial is: " << endl;
    for(int i = N; i >= 0; i--) {
        cout << *(coefficients + i) << "*" << "x" << " " << i << " ";
        if(i != 0) {
            cout << "+" << " ";
        }
        else {
            cout << endl;
        }
    }

    // Change range of values, according to the equation
    int max = 10;
    int min = -10;

    int temp = N;
    float sum_final_positive = 2147483.0;
    float sum_final_negative = -2147483.0;
    float sum_previous_positive = 2147483.0;
    float sum_previous_negative = -2147483.0;

    // finding a and b such that f(a) * f(b) < 0
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
    // cout << "sum_final_positive " << sum_final_positive << endl; // a such that f(a) > 0
    // cout << "sum_final_negative " << sum_final_negative << endl; // b such that f(b) < 0

    // for simplicity
    float a = sum_final_positive;
    float b = sum_final_negative;

    float avg;
    int count = 0;
    float solution;
    float flag_a = 0;
    float flag_b = 0;
    float temp_new;
    
    // Bisection part
    while(true) {
        if(count == 0) avg = (a + b)/2.0;
        // cout << x << endl;
        float sum_new = function_value(avg, N, coefficients);
        // cout << avg << " " <<  sum_new << endl;
        if(sum_new * function_value(a, N, coefficients) < 0) {
            // cout << "function_value(a, N, coefficients) " << function_value(a, N, coefficients) << endl;
            // solution = x;
            b = avg;
            avg = (a + avg)/2.0;
            flag_b = 1;
            flag_a = 0;
        }
        else if(sum_new * function_value(b, N, coefficients) < 0) {
            // cout << "function_value(b, N, coefficients) " << function_value(b, N, coefficients) << endl;
            // solution = x;
            a = avg;
            avg = (b + avg)/2.0;
            flag_a = 1;
            flag_b = 0;
            // solution = x;
            // b = x;
        }
        
        // cout << "x is: " << avg << endl;
        temp_new = avg;
        
        count += 1;
        if(count == 10) {
            if(compare(avg, temp_new, atoi(argv[1]))){
                cout << "Solution is: ";
                cout << setprecision(atoi(argv[1]) + 1) << temp_new << endl;
                exit(1);
            }
        }
    }   
}

int compare(float x, float y, int precision = 3) {
    // cout << x * (pow(10, precision) * 1.0) << endl;
    if(x * (pow(10, precision) * 1.0) == y * (pow(10, precision) * 1.0))
        return 1;
    else
        return 0;
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