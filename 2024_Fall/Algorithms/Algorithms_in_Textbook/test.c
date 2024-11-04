#include<stdio.h>

#define Parent(x)   (x-1)/2
#define Left(x)     x*2 + 1
#define Right(x)    x*2 + 2



int main(){
    int x = -1;
    printf("%d, %d, %d", Parent(x), Left(x), Right(x));
    return 0;
}