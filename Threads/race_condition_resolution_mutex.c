#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<malloc.h>
typedef struct jobnode
{
int job;
struct jobnode* next;
}JOB;

JOB *head=NULL,*tail=NULL,*new_job,*traverse;

/* Initialising mutex variable globally, out of the thread function because if it were defined inside the thread function then each thread, whenever enters the thread function, would initialise the mutex lock, repeatedly changing the value of mutex- undesirable. It is also not being defined inside main, because then it would be local to main and we would have to pass it to the thread function thereafter- clumsy. */


//pthread_mutex_init(&mutex,NULL); //second argument is supposed to be a pointer to a mutex attribute object, passing NULL means default attributes are employed
/* alternative definition of mutex:*/
 pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

void *job_checking(void *arg)
{
for(;traverse!=NULL;traverse=traverse->next)
{
pthread_mutex_lock(&mutex);
printf("Job %d got checked by thread id: %d.\n",traverse->job,(int)pthread_self());
pthread_mutex_unlock(&mutex);
}
pthread_mutex_unlock(&mutex);
}

void create_job_queue(JOB* head)
{
int i,j;

head=(JOB*)malloc(sizeof(JOB));
head->job=1;
tail=head;
traverse=head;
tail->next=NULL;

for(i=0,j=2;i<4;i++,j++)
{
new_job=(JOB*)malloc(sizeof(JOB));
new_job->job=j;
tail->next=new_job;
tail=new_job;
tail->next=NULL;
}
}

int main(int argc,char **argv)
{
int i;

create_job_queue(head); //pass the head and it'll create the list of jobs

pthread_t thread_id[4];

//four threads will execute the same function
for(i=0;i<4;i++)
pthread_create(&thread_id[i],NULL,job_checking,NULL);

for(i=0;i<4;i++)
pthread_join(thread_id[i],NULL);

return 0;

}
