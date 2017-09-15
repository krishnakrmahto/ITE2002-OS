/* The following program aims at appending time to a file (existent or non-existent just before the time of execution by using open,write,closesystem calls. */

#include<stdio.h>
#include<time.h> // for time-related functions
#include<sys/types.h> // for size_t,open sys call
#include<fcntl.h> // for open system call
#include<unistd.h> // for write, close system calls
#include<sys/stat.h> // for open system call

char *
