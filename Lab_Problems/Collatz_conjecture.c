#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>
#include<math.h>

int main(int argc,char** argv)
{
if(*(argv+1)[0]=='-')
{
puts("Please enter a positive number and come back.\nExiting...");
exit(1);
}
int count=0,i=0,num=0,n;

if(*(argv+1)[0]!='+')
{
count=strlen(*(argv+1));

for(i=0;i<count;i++)
num+=((*(argv+1)[count-i-1])-48)*pow(10,i);
}

else
{
count=strlen(*(argv+1));

for(i=0;i<count-1;i++)
num+=((*(argv+1)[count-i-1])-48)*pow(10,i);
}
/* it is important to initialise child_status because it's address will be used in wait() in parent process. Until un-initialised, it will have some garbage value. */

n=num;
int child_status=0;
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
