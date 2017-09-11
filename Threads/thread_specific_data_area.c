/* Situation is, a threre are multiple threads running at a time (5 in this case). In order to illustrate thread specific data area, they'll be made to use the same key in-order-to create instances of the same data type. Note that as each data value created will be a thread-specific one,it's access methodology is different. You don't explicitly define a thread-specific variable, but one key for each thread-specific value. */

/* We'll have one key that'll be used by each thread in order to write the same type of information- log of a file-writing operation. */

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<sys/types.h>

void write_log(pthread_key_t* thread_log_key,const char *log)
{

//getting the thread _specific value back

FILE *fp=(FILE*)pthread_getspecific(*thread_log_key);
fprintf(fp,"%s\n",log);
return;
}

void *log_file_open(void *thread_log_key_received)
{
pthread_key_t* thread_log_key=(pthread_key_t*)thread_log_key_received;

FILE *fp;
char *log_file_name;

sprintf(log_file_name,"thread%d",(int)pthread_self());
fp=fopen(log_file_name,"w");
/* now what I would like to do is, set this file-pointer fp as a specific value for any thread that runs this function, so that each thread will have its own copy of log file pointer. This will enable us to store log file for each thread separately. */

pthread_setspecific(*thread_log_key,(void*)fp); //pthread_setspecific()'s second argument (ie the thread specific value) should be void*
write_log(thread_log_key,"The thread has started.");

/* now thread will continue working and based on that log file can be written using the write_log function. */

return NULL;
}

void clean_up_func(void *fp_rcv) //clean up also receives void* parameters
{
fclose((FILE*)fp_rcv);
}


int main()
{
int i;
pthread_t thread_id[5];

/* under this key, log of each thread will be saved which will be exclusively and independently*/
pthread_key_t thread_log_key;

pthread_key_create(&thread_log_key,clean_up_func); // clean up function will close the FILE opened

for(i=0;i<5;i++)
pthread_create(&thread_id[i],NULL,log_file_open,(void*)&thread_log_key);

for(i=0;i<5;i++)
pthread_join(thread_id[i],NULL);

return 0;
}
