#include<stdio.h>
#include<pthread.h>

void *thread_func(void *arg)
{
int *i=(int*)arg;

*i++;

printf("%d",*i);

return NULL;
}

int main()
{
pthread_t thread1_id,thread2_id;
int arg=3;
pthread_create(&thread1_id,NULL,thread_func,(void*)&arg);
pthread_create(&thread2_id,NULL,thread_func,(void*)&arg);

pthread_join(thread_1,NULL);
pthread_join(thread_2,NULL);

return 0;
}
