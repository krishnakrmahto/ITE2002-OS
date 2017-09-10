#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
pid_t pid;
pid=fork();

if(pid==0) //Child process
{
printf("I am child with ID and PID: %d and %d respectively\n",(int)getpid(),(int)getppid());
exit(1); //Child process exits immediately
}
else //Parent process
{
sleep(60); //Parent sleeps for 60s
printf("I am parent and my ID is:%d and child ID is: %d\n",(int)getpid(),(int)pid);
}

return 0;
}
