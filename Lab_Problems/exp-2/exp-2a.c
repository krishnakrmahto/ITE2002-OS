#include<stdio.h>
#include<stdlib.>
#include<unistd.h> // for fork, stat
#include<sys/types.h> //for closedir,opendir,pid_t
#include<dirent.h> // for opendir,closedir,DIR*

int main(int argc,char **argv)
{
pid_t pid=fork();

if(pid==0) // if child process
{

/* child process will ask a brand new process to replace itself. */

char *args=("Child process asked me to replace its instance."); //an argument for the new process

execvp("./helloExec",args); //passing arg to the new process- helloExec; as a convention first arg is name of the file to be executed
fprintf(stderr,"Execution failed!");


