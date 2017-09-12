#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<pthread.h>

void *factorial_thread(void *num_recv)
{
int num=*((int*)num_recv);
int *fact;
int i;
*fact=1;
for(i=num;i>1;i--)
(*(fact))*=i;

printf("The factorial is: %d\n",*fact);

return NULL;
}

int main(int argc,char **argv)
{
int n; //number whose factorial will be calculated
static int *r; //result of the factorial's address
pthread_t thread_id;

puts("Enter any number: ");
scanf("%d",&n);

pthread_create(&thread_id,NULL,&factorial_thread,(void*)&n);
pthread_join(thread_id,NULL);

return 0;
}
