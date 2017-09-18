#include<stdio.h>
<<<<<<< HEAD
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
=======
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

#define NUM_OF_JOBS 10

typedef struct jobnode
{
int job;
struct jobnode* next;
}JOB;

int i=1;

JOB *head=NULL,*tail=NULL,*new_job,*traverse;

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

/* globally defining semaphore. why not in the thread function or in main? because defining in the process thread would cause semaphore to be initialised by every thread that starts executing it, that's not what we would like to happen to semaphore. why not in main? because then we would have to pass it to the thread function which we have just avoided by defining sem_t var globally. */

sem_t semaphore;
//sem_init(&semaphore,0,0); //sem_t var should be initialised with 0
int sem_value=0;


void *job_checking(void *arg) // the thread function
{

for(traverse=head;traverse!=NULL;)
{
sem_getvalue(&semaphore,&sem_value);
printf("Semaphore before thread id %d executes sem_wait() is %d",(int)pthread_self(),sem_value);

sem_wait(&semaphore);
pthread_mutex_lock(&mutex);
printf("Job %d processed by thread id: %d\n",traverse->job,(int)pthread_self());
traverse=traverse->next;

pthread_mutex_unlock(&mutex);
sleep(1); //sleeping for 1 sec so that other threads created can also get an opportunity
}
}


void create_job_queue(JOB* head)
{

int i=NUM_OF_JOBS;

if(head==NULL)
{

//if head is NULL, make a head node
new_job=(JOB*)malloc(sizeof(JOB));
new_job->job=i--;
head=new_job;
tail=head;
tail->next=NULL;

//let the sem_t know that a new job is available
sem_post(&semaphore);
}

for(;i>0;i--)
{

new_job=(JOB*)malloc(sizeof(JOB));
new_job->job=i;
tail->next=new_job;
tail=new_job;
tail->next=NULL;

// post job availability to the semaphore.
sem_post(&semaphore);

}
}

int main(int argc,char **argv)
{

sem_init(&semaphore,0,0);
int i;
create_job_queue(head);
pthread_t thread_id[4],last_thread_id;

for(i=0;i<4;i++)
pthread_create(&thread_id[i],NULL,job_checking,NULL);

for(i=0;i<4;i++)
pthread_join(thread_id[i],NULL);

pthread_create(&last_thread_id,NULL,job_checking,NULL);
pthread_join(last_thread_id,NULL);
return 0;

}
>>>>>>> shared_memory
