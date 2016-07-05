#include <stdio.h>
#include <stdlib.h>

int recursiveCatalan(unsigned int);
int dynamicCatalan(unsigned int);
int dynamicOptimizedCatalan(unsigned int);

unsigned int count = 0;

int main(){
    unsigned int i;
    int res;

    printf("***************** Dynamic Optimized Catalan *****************\n");
    for(i = 0; i < 13; i++){
        res = dynamicOptimizedCatalan(i);
        printf(" N = %2d -> Result = %6d ; Count = %6d\n", i, res, count);
        count = 0;
    }

    return 0;
}


int dynamicOptimizedCatalan(unsigned int n){
    if(!n) return 1;
    unsigned int i, j, round;
    int *arr = (int *)malloc(sizeof(int) * (n+1));
    arr[0] = 1;
    for(i = 1; i < n+1; i++){
        arr[i] = 0;
        round = i/2;
        for(j = 0; j < round; j++){
            arr[i] += arr[j] * arr[i-j-1] << 1;
            count ++;
        }
        if(i & 1){
            arr[i] += arr[round] * arr[i-round-1];
            count ++;
        }
    }
    int res = arr[n];
    free(arr);
    return res;
}
