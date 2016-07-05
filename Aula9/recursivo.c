//
// Created by Daniela Pereira Simões on 02/05/16.
//

#include <stdio.h>
int mult = 0;

int Catalan(int num){
    if(num == 0){
        return 1;
    }

    int result = 0;

    for (int i = 0; i < num ; i++) {
        result += Catalan(i)*Catalan(num - i - 1);
        mult = mult + 1;
    }

    return result;
}

int main(void){
    printf("\n%s%d", "Resultado: ", Catalan(10));
    printf("\n%s%d", "Mults: ", mult);

    return 0;
}