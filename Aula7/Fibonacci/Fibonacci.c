//
// Created by Daniela Pereira Simões on 11/04/16.
//

#include <stdio.h>

int adds = 0;

double Fibonacci(int n){
    if(n==0){
        return 0;
    }
    if(n == 1)
        return 1;

    adds++;
    return Fibonacci(n-1) + Fibonacci(n-2);
}

int main(void){

    double x = Fibonacci(6);

    printf("%s%f", "Result: ", x);
    printf("%s%d", "\nMults: ", adds);

}

