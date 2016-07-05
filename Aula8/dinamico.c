#include <stdio.h>
int div=0;

int p(int n){


    if(n < 2)
        return 0;

    int array[n+1];

    array[0] = array[1] = 0;

    for(int i = 2; i<=n; i++) {
        int x = i/2;
        int x1 = (i+1)/2;
        div = div + 2;
        array[i] = x + x1 + array[x1] + array[x];
    }

    return array[n];
}

int main(void){

    int x = p(11);

    printf("%s%d", "Result: ", x);
    printf("%s%d", "\nDiv: ", div);

}