#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

typedef struct args
{
char *ch;
unsigned int count;
}ARG;

void *print_chars(void *parameters) //thread function. LINUX/UNIX thread functions return void* and accept void* parameters
{
ARG *paramet=(ARG*)parameters; //typecasting
int i;

for(i=0;i<paramet->count;i++)
fprintf(paramet->ch,stderr);

return NULL;
}


int main(int argc,char **argv)
{
pthread_t *thread_1,*thread_2; //pthread_t specifically is a data type for thread id variables.
ARG *arg_1,*arg_2;

pthread_create(thread_1,NULL,&print_chars,arg_1
