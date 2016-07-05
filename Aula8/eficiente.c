#include <stdio.h>
int div=0;
int c = 0;
int f = 0;
int p(int n){

    if(n < 2)
        return 0;

    int array[n+1];

    array[0] = 0;
    array[1] = 0;

    for(int i = 2; i<=(n+1)/2; i++) {
            array[0] = 0;
            f = i/2;
            c = (i+1)/2;
            div += 2;
            array[i] = c + f + array[c] + array[f];
            printf("%d\n", array[i-1]);
    }

    array[n] = n/2 + (n+1)/2 + array[n/2] + array[(n+1)/2];
    div += 2;

    return array[n];
}

int main(void){

    int x = p(8);

    printf("%s%d", "Result: ", x);
    printf("%s%d", "\nDiv: ", div);

}