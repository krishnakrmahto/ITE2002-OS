#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

typedef struct args
{
char ch;
int count;
}ARG;

void *print_chars(void *parameters) //thread function. LINUX/UNIX thread functions return void* and accept void* parameters
{
ARG *paramet=(ARG*)parameters; //typecasting
int i;

for(i=0;i<paramet->count;i++)
fputc(paramet->ch,stderr);

return NULL;
}


int main(int argc,char **argv)
{
pthread_t *thread_1,*thread_2; //pthread_t specifically is a data type for thread id variables.
ARG *arg_1=(ARG*)malloc(sizeof(ARG));
ARG *arg_2=(ARG*)malloc(sizeof(ARG));

arg_1->ch='x';
arg_1->count=1000;

arg_2->ch='o';
arg_2->count=2000;

pthread_create(thread_1,NULL,&print_chars,arg_1);
pthread_create(thread_1,NULL,&print_chars,arg_2);

puts("I'll wait for the other threads to return because if I exit, then the args I have passed to the threads will be out of scope for them.");

pthread_join(*thread_1,NULL); //waiting for thread_1 to join
pthread_join(*thread_2,NULL); //waiting for thread_2 to join

return 0;

}
