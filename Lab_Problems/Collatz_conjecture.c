#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(int argc,int **argv)
{
int n=argc;
if(n<0)
{
puts("Please enter a positive number and come back.\nExiting...");
exit(1);
}

int child_status;
pid_t pid=fork();

if(pid==0) //child process
{
printf("I am child process with pid: %d and ppid: %d\n\n",(int)getpid(),(int)getppid());

puts("The series: ");
for(;n!=1;)
{
if(n%2==0)
{
printf("%d, ",n);
n=n/2;
}
else
{
printf("%d, ",n);
n=(3*n)+1;
}
}
printf("%d\n",n);

return 0;
}

else //parent process
{
printf("I am parent and I am waiting for the child to return, my pid: %d\n",(int)getpid());

wait(&child_status); //waiting for the child to come

puts("My child has come! I too am leaving!!");

}

return 0;
}
