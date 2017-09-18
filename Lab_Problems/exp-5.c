#include<stdio.h>
#include<semaphore.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<pthread.h>
#include<sys/stat.h> //for mode_t

int shmid; // for storing return value from shmget; declaring globally so that each thread func can access it without needing to pass it as arg
sem_t semaphore;

void *producer_thread(void *arg)
{


return NULL;
}

int main(int argc,char **argv)
{

sem_init(&semaphore,0,0);

int i;
key_t key=5678;

size_t shm_size=4096;

mode_t mode=S_IwUSR | S_IRUSR | S_IROTH | IPC_CREAT; //IPC_CREAT for creating a new shm

shmid=shmget(key,size,mode);

if(shmid<0)
{
perror("shmget");
exit(1);
}

unsigned int *attached_addr_space_ptr=shmat(shmid,NULL,0);

if(attached_addr_space_ptr<0)
{
perror("shmat");
exit(2);
}

/* ---till now shared memory has been made by the server and it has been attached to the server's addr space--- */
/* ---now producer should add content--- */
/* -- one thread shall act as a producer, the other shall act as a consumer. -- */

pthread_t producer_id, consumer_id;

pthread_create(&producer_id,NULL,producer_thread,NULL);
pthread_create(&consumer_id,NULL,consumer_thread,NULL);

pthread_join(producer_id,NULL);
pthread_join(consumer_id,NULL);
