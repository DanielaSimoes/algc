#include <stdio.h>

void trocar(int *i, int *j);
int procurarInd(int v[], int n);
void rodar(int v[], int n);

int main(void){
    printf("HERE");
    int v[6] = {5,6,1,2,3,4};
    int i, n = 6;
    rodar(v,n);
    for(i = 0; i < n; i++)
        printf(" %d ",v[i]);
    return 0 ;
}

void trocar(int *i, int *j){
    int tmp = *i;
    *i = *j;
    *j = tmp;
}

int procurarInd(int v[], int n){
    unsigned int i;
    for(i = 0; i < n-1; i++){
        if(v[i] > v[i+1])
            return i+1;
    }
    return 0;
}

void rodar(int v[], int n){
    int i,j, begin = procurarInd(v,n);
    for(i = 0, j = 0; i < begin; i++, j--)
        trocar(&i,&j);
    for(i = 0, j = begin; i <= begin; i++, j--)
        trocar(&i,&j);
}

