//
// Created by Daniela Pereira Simões on 18/04/16.
//

#include <stdio.h>
int divs = 0;

int P(int num){
    if(num == 1){
        return 0;
    }

    divs = divs + 2;
    int floor = (num/2);
    int ceil = ((num+1)/2);



    return floor + ceil + P(ceil) + P(floor);
}

int main(void){
    int t = P(12);
    printf("\n%s%d", "Resultado: ", t);
    printf("\n%s%d", "Divisão: ", divs);

    return 0;
}