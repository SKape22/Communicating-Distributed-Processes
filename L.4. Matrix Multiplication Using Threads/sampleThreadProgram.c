#include<stdio.h>
#include"thread.h"
#include <time.h>
#include <stdlib.h>

typedef enum {false,true} bool;

static void multiply(int n);
static void multiply_seq();
bool verify();


#define NTHREADS 4
#define SIZE 1000

static thread_t threads[NTHREADS];

static float A[SIZE][SIZE];
static float B[SIZE][SIZE];

static float prod[SIZE][SIZE];
static float prod_seq[SIZE][SIZE];

void set_mem()
{
	srand(time(0));
	for(int i=0; i<SIZE; i++)
	{
		for(int j=0; j<SIZE; j++)
		{
			A[i][j]=((float)rand()/RAND_MAX)*(10.0);
			B[i][j]=((float)rand()/RAND_MAX)*(10.0);
		}
	}
}

int main(int argc,char** argv){
	int i;
	long exitValue;

	set_mem();

	for(i=0;i<NTHREADS;i++){
		thread_create(&(threads[i]),&multiply,i);
	}

	for(i=0;i<NTHREADS;i++){
		exitValue=thread_join(threads[i]);
		printf("Thread %d returned with %ld\n",i,exitValue);
	}
	printf("Main thread done.\n");
	multiply_seq();
	if(verify())
	{
		printf("Multiplication verified\n");
	}
	else 
	{
		printf("Verification failed\n");
	}
	return 0;
}

void multiply(int n){
 
    for (int i = n*250; i < (n+1)*250; i++) {
        for (int j = 0; j <SIZE; j++) {
            prod[i][j] = 0;
 
            for (int k = 0; k < SIZE; k++) {
                prod[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void multiply_seq()
{
	for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j <SIZE; j++) {
            prod_seq[i][j] = 0;
 
            for (int k = 0; k < SIZE; k++) {
                prod_seq[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

bool verify()
{
	//bool ans=false;
	for(int i=0; i<SIZE; i++)
	{
		for(int j=0; j<SIZE; j++)
		{
			if(prod[i][j]!=prod_seq[i][j])
			{
				return false;
			}
		}
	}
	return true;
}