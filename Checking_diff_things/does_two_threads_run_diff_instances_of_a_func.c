#include<stdio.h>
#include<pthread.h>

void *thread_func(void *arg)
{
int *i=(int*)arg;
printf("initial: %d\n",*i);

(*i)++;

printf("after: %d\n",*i);

return NULL;
}

int main()
{
pthread_t thread1_id,thread2_id;
int arg=3;
pthread_create(&thread1_id,NULL,thread_func,(void*)&arg);
pthread_create(&thread2_id,NULL,thread_func,(void*)&arg);

pthread_join(thread1_id,NULL);
pthread_join(thread2_id,NULL);

return 0;
}
