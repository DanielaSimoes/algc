//
// Created by Daniela Pereira Simões on 06/06/16.
//

#include <stdio.h>

int main(void){

    int a[] = {1,2,2,2,2,2,3,3,3,8};

    int NumRepts = 0;
    int final = 0;

    for (int i = 0; i < (sizeof(a)/sizeof(a[0])) - 1 ; ++i) {
        if(a[i] == a[i+1]) {
            NumRepts++;

            if (NumRepts == 2) {
                final++;
                NumRepts = 0;
            }
        }
    }

    printf("%d",final);

}