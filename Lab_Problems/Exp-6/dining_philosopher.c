#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_mutex_t mutex_fork[5]; // 5 mutexes for each fork
pthread_key_t phil_num;

void *philosopher_func(void *arg)
{
//printf("%d\n",*((int*)arg));
pthread_setspecific(phil_num,arg);

printf("Philosopher %d is thinking.\n",*(int*)pthread_getspecific(phil_num));
sleep(3);

/*philosopher number phi_no will now pick up two forks.*/
pthread_mutex_lock(&mutex_fork[*(int*)pthread_getspecific(phil_num)]);
pthread_mutex_lock(&mutex_fork[(*(int*)pthread_getspecific(phil_num)+1)%5]);

printf("Philosopher %d is eating.\n",*(int*)pthread_getspecific(phil_num));
sleep(2);

pthread_mutex_unlock(&mutex_fork[*(int*)pthread_getspecific(phil_num)]);
pthread_mutex_unlock(&mutex_fork[(*(int*)pthread_getspecific(phil_num)+1)%5]);

printf("Philosopher %d finished eating.\n",*(int*)pthread_getspecific(phil_num));

return NULL;
}

int main(int argc,char **argv)
{
pthread_t thread_philosopher[5];
pthread_key_create(&phil_num,NULL);

int* i=(int*)malloc(sizeof(int));
int j;

for(j=0;j<5;j++)
pthread_mutex_init(&mutex_fork[j],NULL);

for(j=0,*i=j;j<5;i++,j++,*i=j)
{
//printf("%d\n",i);
pthread_create(&thread_philosopher[j],NULL,philosopher_func,(void*)i);
}
for(j=0;j<5;j++)
pthread_mutex_destroy(&mutex_fork[j]);// freeing the space occupied by mutex

for(j=0;j<5;j++)
pthread_join(thread_philosopher[j],NULL);

return 0;
}
