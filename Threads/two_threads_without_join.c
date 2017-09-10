#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<sys/types.h>

typedef struct args //structure to be used to form arguments for each thread
{
char ch;
int num;
}ARG;

/*thread function in unix environment returns void*, accepts void *parameters*/
void* print_chars(void *parameters)
{
ARG *parame=(ARG*)parameters; //typecasting from void to type for struct args typedef'd as ARG
int i;

for(i=0;i<parame->num;i++)
fputc(parame->ch,stderr); //writing to the stderr stream used by error printing func's like fprintf etc.

return NULL;
}

int main(int argc,char **argv)
{
pthread_t *thread_1, *thread_2; //thread ID pointer variables

thread_1=(pthread_t*)malloc(sizeof(pthread_t)); //initialising the pointer variables
thread_2=(pthread_t*)malloc(sizeof(pthread_t)); 

ARG *arg_1,*arg_2;

arg_1=(ARG*)malloc(sizeof(ARG));
arg_2=(ARG*)malloc(sizeof(ARG));

arg_1->ch='x';
arg_2->ch='o';

arg_1->num=10000;
arg_2->num=20000;

pthread_create(thread_1,NULL,&print_chars,arg_1);
pthread_create(thread_2,NULL,&print_chars,arg_2);

return 0;
}

