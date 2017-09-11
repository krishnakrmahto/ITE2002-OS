/* Situation is, a threre are multiple threads running at a time (5 in this case). In order to illustrate thread specific data area, they'll be made to use the same key in-order-to create instances of the same data type. Note that as each data value created will be a thread-specific one,it's access methodology is different. You don't explicitly define a thread-specific variable, but one key for each thread-specific value. */

/* We'll have one key that'll be used by each thread in order to write the same type of information- log of a file-writing operation. */

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<sys/types.h>

void *write_log(void *thread_log_key_received)
{
pthread_key_t* thread_log_key=(pthread_key_t*)thread_log_key_received;

FILE *fp;
char *log_file_name;

sprintf(log_file_name,"thread%d",(int)pthread_self());

int main()
{
pthread_t thread_id[5];

/* under this key, log of each thread will be saved which will be exclusively and independently*/
pthread_key_t thread_log_key;

pthread_key_create(&thread_log_key,clean_up_func) // clean up function will close the FILE opened.


pthread_create(&thread_id[i],NULL,write_log,(void*)&thread_log_key);


