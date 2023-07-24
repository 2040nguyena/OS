#include<stdio.h>
#include<stdlib.h>
//malloc, calloc, realloc, free
int main()
{
    int a[5], i;
    int *p, *temp;
    p = malloc(5*sizeof(int));
    p = a;
    // for(i=0;i<5;i++){
    //     a[i] = i+1;
    // }
    i = 0;
    // for(i=0;i<5;i++){
    //     printf("%d\n", a[i]);
    // }
    //temp = p;
    while(i<5){
        *p = i+1;
       // printf("%d\n",*p);
        p++;
        i++;
    }

    p = temp;
    i = 0;
    realloc(p, 10*sizeof(int));
    while(i<5){
        printf("%d\n",*p);
        p++;
        i++;
    }
    //printf("%d %d", *p, a);
    free(p);
}
//return 0;