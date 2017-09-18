/* This helloExec will access the directory whose address will be passed by the child process */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h> //for opendir,closedir,pid_t
#include<dirent.h> //for opendir,closedir,DIR*

int main(int argc,char *argv[])
{

int i;

puts("I am helloExec!");
printf("Number of parameters: %d\n",argc);

printf("My pid: %d\n",(int)getpid());

for(i=0;i<argc;i++)
printf("My arguments: %s",argv[i]);

DIR* dir_handle=opendir(argv[1]);
struct dirent *dir_entry;

//do
//{
dir_entry=readdir(dir_handle);
printf("%s\n",dir_entry->d_name);

return 0;
}


