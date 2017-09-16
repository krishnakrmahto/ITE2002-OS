/* The following program aims at appending time to a file (existent or non-existent just before the time of execution by using open,write,closesystem calls. */

#include<stdio.h>
#include<time.h> // for time-related functions
#include<sys/types.h> // for size_t,mode_t,open sys call
#include<fcntl.h> // for open system call
#include<unistd.h> // for write, close system calls
#include<sys/stat.h> // for open system call
#include<stdlib.h>
#include<string.h>

void open_file(char *filepath,int *fd_ptr,mode_t mode)
{
*fd_ptr=open(filepath,O_WRONLY|O_APPEND,mode);

if (*fd_ptr==-1) // file opening has failed
{
perror("open");
exit(0);
}
}

int main(int argc,char **argv)
{
char *filepath=(argv[1]);
int fd=0;
mode_t mode=S_IWGRP | S_IRGRP | S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH;

open_file(filepath,&fd,mode);

char *time_buffer;

time_t time_sec=time(NULL); // if instead of NULL, some other time_t* var was passed then the returned secs would be saved there also.

time_buffer=asctime(localtime(&time_sec));

write(fd,time_buffer,strlen(time_buffer));

close(fd);

return 0;
}
