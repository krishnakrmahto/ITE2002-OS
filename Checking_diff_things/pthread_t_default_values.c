#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

int main()
{
pthread_t thread_id;
pthread_key_t thread_key;

printf("%d\n%d\n",(int)thread_id,(int)thread_key);

return 0;
}
