#include<stdio.h>
#include<semaphore.h>
#include<sys/types.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
sem_t semaphore;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER; 
int buffer[100],buff_counter=0;
void *consumer_thread(void *arg)
{
do
{
/*first wait, and then lock the mutex. doing otherwise will create
a deadlock in case when semaphore=0*/
sem_wait(&semaphore);
pthread_mutex_lock(&mutex);
printf("Consumer consumed:\t%d\n",buffer[--buff_counter]);
pthread_mutex_unlock(&mutex);
sleep(1);
}while(buff_counter>0); 
return NULL;
}
void *producer_thread(void *arg)
{
pthread_mutex_lock(&mutex);
buffer[buff_counter]=rand()%100;
printf("Producer produced:\t%d\n",buffer[buff_counter++]);
sem_post(&semaphore);
pthread_mutex_unlock(&mutex); 
return NULL;
}
int main(int argc,char **argv)
{
//int gf=0;
sem_init(&semaphore,0,0);
//sem_getvalue(&semaphore,&gf);
//printf("haha: %d\n\n",gf);
int i,num_prod=101,num_consum=101;
for(;num_prod>100;)
{
puts("Enter the number of producer threads(<=100): ");
scanf("%d",&num_prod);
}
for(;num_consum>100;)
{
puts("Enter the number of consumer threads(<=100): ");
scanf("%d",&num_consum);
}
pthread_t producer_id[num_prod], consumer_id[num_consum];
for(i=0;i<num_prod;i++)
pthread_create(&producer_id[i],NULL,producer_thread,NULL);
for(i=0;i<num_consum;i++)
pthread_create(&consumer_id[i],NULL,consumer_thread,NULL);
for(i=0;i<num_prod;i++)
pthread_join(producer_id[i],NULL);
for(i=0;i<num_consum;i++)
pthread_join(consumer_id[i],NULL);
return 0;
}