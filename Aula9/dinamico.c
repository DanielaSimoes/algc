//
// Created by Daniela Pereira Simões on 02/05/16.
//

#include <stdio.h>
int mult;

int Catalan(int n){

    int array[n+1];
    int result = 0;

    array[0] = 1;

    for(int i = 1; i <= n; i++) {
        array[i] = 0;
        for (int j = 0; j < i ; ++j) {
            mult++;
            array[i] += array[j]*array[i-j-1];
        }
    }

    return array[n];
}

int main(void){

    printf("%s%d", "Result: ", Catalan(12));
    printf("%s%d", "\nDiv: ", mult);

}
