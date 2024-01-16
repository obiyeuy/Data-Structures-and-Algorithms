#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int f(char *c){
    int nK = 0;
    while(*c){
        nK = nK*10+*c++;
    
    }
    return nK;
}

#include "stdio.h"
#define MAX 40
main()
{
char str[MAX] = {"I like C language!"};
scanf("%s\n",str+7);
printf("%s\n",str);}


