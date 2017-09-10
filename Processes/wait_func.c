#include<stdio.h>
#include<sys/types.h> //for pid_t type
#include<stdlib.h> //for exit() func
#include<unistd.h> //for fork() func
#include<sys/wait.h> //for wait
int main()
{
int child_status;
pid_t pid=fork();

if(pid==0) //child process
{
int i;
printf("I am child with pid: %d and my parent's pid(ppid) is: %d\n",(int)getpid(),getppid());

for(i=0;i<2;i++)
{
sleep(i);
printf("slept for %d sec.\n",i);
}

exit(1);
}

else
{
printf("I am parent of child with pid: %d. I will wait for my child. My pid is: %d",pid,getpid());
/* &child_status  is an argument to wait() system call. wait will assign value to *child_status */

wait(&child_status);

if(WIFEXITED(child_status))
puts("My child has exited normally");
else
puts("My child was forced to exit without his will!");

}

return 0;

}

