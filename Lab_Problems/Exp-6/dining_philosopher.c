#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_mutex_t mutex_fork[5]; // 5 mutexes for each fork

void *philosopher_func(void *arg)
{
int* phil_no=(int*)(arg);
printf("Philosopher %d is thinking.\n",*phil_no);
sleep(3);

/*philosopher number phi_no will now pick up two forks.*/
pthread_mutex_lock(&mutex_fork[*phil_no]);
pthread_mutex_lock(&mutex_fork[(*phil_no+1)%5]);

printf("Philosopher %d is eating.\n",*phil_no);
sleep(2);

pthread_mutex_unlock(&mutex_fork[*phil_no]);
pthread_mutex_unlock(&mutex_fork[(*phil_no+1)%5]);

printf("Philosopher %d finished eating.\n",*phil_no);

return NULL;
}

int main(int argc,char **argv)
{
pthread_t thread_philosopher[5];
int i;
for(i=0;i<5;i++)
pthread_mutex_init(&mutex_fork[i],NULL);

for(i=0;i<5;i++)
pthread_create(&thread_philosopher[i],NULL,philosopher_func,(void*)&i);

for(i=0;i<5;i++)
pthread_mutex_destroy(&mutex_fork[i]);// freeing the space occupied by mutex

for(i=0;i<5;i++)
pthread_join(thread_philosopher[i],NULL);

return 0;
}
