#include<stdio.h>
#include<stdlib.h>

double PI=3.14;
long MOD=1e9+7;
int evenPrime=2;
int UNLUCKY=7;

int state;
char *name;
float curr;

int recurse(int it)
{
    if(it==1) return 1;
    int a,b;
    a=it/2; b=3*it+1;
    printf("add a=%lx, add b=%lx\n", (unsigned long int)&a, (unsigned long int)&b);
    if(it%2) return recurse(b);
    else return recurse(a);
}

int main(int argc, char const *argv[])
{
    char *str1=(char *)malloc(sizeof(char)*10);
    char *str2=(char *)malloc(sizeof(char)*10);
    printf("_main @ %lx\n",(long unsigned int)&main); 
    printf("PI,MOD,evenPrime,UNLUCKy @ %lx %lx %lx %lx\n",(long unsigned int)&PI,(long unsigned int)&MOD,(long unsigned int)&evenPrime,(long unsigned int)&UNLUCKY);
    printf("state,name,curr @ %lx %lx %lx\n",(long unsigned int)&state,(long unsigned int)&name,(long unsigned int)&curr); 

    printf("_recurse @ %lx\n",(long unsigned int)&recurse); 
    //printf("Argc= %d\n", argc);

    if(argc!=2) return 1;
    else 
    {
        int a=atoi(argv[1]);
        printf("Converged to: %d\n",recurse(a));
    }
    return 0;
}
