//
// Created by Daniela Pereira Simões on 11/04/16.
//

#include <stdio.h>

int mults;

double powerRec(double num, unsigned int exp){
    if(exp==0){
        return 1;
    }
    if(exp == 1){
        return num;
    }

    if(exp%2==0){
        mults++;
        return powerRec(num*num, exp/2);
    }else{
        mults = mults + 2;
        return num*powerRec(num*num, exp/2);
    };
}

int main(void){

    double x = powerRec(0.5, 16);

    printf("%s%f", "Result: ", x);
    printf("%s%d", "\nMults: ", mults);

}

