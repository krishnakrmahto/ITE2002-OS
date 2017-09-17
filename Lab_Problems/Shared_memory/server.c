#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h> //for shmget

int main(int argc, char **argv)
{

key_t key;
size_t page_size=getpagesize();

int segment_id=shmget(key=IPC_PRIVATE,
int 
