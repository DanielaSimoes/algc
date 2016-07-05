#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

int power(int, int);
int addArray(int);
int printArray(void);
static int *four, *init = (int*)calloc(10000000, sizeof(int)*1000);


int check_armstrong(int);
int power(int, int);

int main () {
    int c, a, b;

    printf("Input two integers\n");
    scanf("%d%d", &a, &b);

    for (c = a; c <= b; c++) {
        if (check_armstrong(c) == 1)
            printf("%d\n", c);
    }

    printArray();

    return 0;
}

int check_armstrong(int n) {
    long long sum = 0, temp;
    int remainder, digits = 0;

    temp = n;

    while (temp != 0) {
        digits++;
        temp = temp/10;
    }

    temp = n;

    while (temp != 0) {
        remainder = temp%10;
        sum = sum + power(remainder, digits);
        temp = temp/10;
    }

    if (n == sum) {
        if(n>1000 && n <9999) {
            addArray(n);
        }
            return 1;
    }
    else
        return 0;
}

int  power(int n, int r) {
    int c, p = 1;

    for (c = 1; c <= r; c++)
        p = p*n;

    return p;
}


int addArray(int n){
    *four = n;
    four++;
    return 0;
}

int printArray(void){
        printf("Com 4 digitos: ");
        while(*init!=0) {
            printf("%d ", *init);
            init++;
        }
}
