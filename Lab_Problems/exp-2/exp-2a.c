/* This file calls a helloExec file and passes directory path as args that  will use directory access commands to access that directory. */

#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h> // for fork, stat
#include<sys/types.h> //for closedir,opendir,pid_t
#include<dirent.h> // for opendir,closedir,DIR*

int main(int argc,char **argv)
{
pid_t pid=fork();
int child_status=0;
if(pid==0) // if child process
{

/* child process will ask a brand new process to replace itself. */
printf("I am child process with pid %d and ppid %d, I am going to replace myself with helloExec.\n\n",(int)getpid(),(int)getppid());

char *args[]={"./helloExec","~/VBShare",NULL}; //an argument for the new process;  as a convention first arg is name of the file to be executed

execvp("./helloExec",args); //passing arg to the new process- helloExec
fprintf(stderr,"execvp failed!\n\n"); //no conditional block is required for fprintf as execvp returns only if it fails
exit(1);
}

else
{

printf("I am parent with pid %d, waiting for child with pid %d to return.\n",(int)getpid(),(int)pid);
wait(&child_status);
}
return 0;
}
