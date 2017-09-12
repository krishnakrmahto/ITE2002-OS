#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>

int main(int c,char **argv)
{
pid_t pid;

pid=fork();

if(pid==0)
{
//child process
printf("I am child and my pid is %d and my parent's pid is: %d\n\n ",getpid(),getppid());
sleep(10); //child goes to sleep
}

else
{
//parent process

printf("I am parent process and my pid is: %d\n",getpid());

/*as the parent will exit in the next line and the child process will still be running the sleep() system call, the child will become orphan.*/

exit(0);
}

return 0;

}
