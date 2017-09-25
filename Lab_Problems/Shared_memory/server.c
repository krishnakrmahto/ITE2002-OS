#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h> //for shmget
#include<unistd.h> //for sleep
#include<sys/stat.h>
#include<sys/types.h>

int main(int argc, char **argv)
{

key_t key=5678;
int i;
unsigned int *addr_attach_shm; //ptr to be used to receive the process address space where the shared memory is attached. Any type of pointer can be used and accordingly the return value of shmat can be typecasted

size_t page_size=getpagesize();

mode_t mode=S_IWUSR | S_IRUSR | S_IROTH | IPC_CREAT; // permissions list for segment

int shmid=shmget(key,4096,mode);

if(shmid<0) // if shmget() fails
{
perror("shmget");
exit(1);
}


/*In the following, arg2 is NULL so that kernel decides the address in program data space for attaching, arg3 specifies flags such as read-only or whether the address of the memory space is rounded down to page address; but b'coz address of pgm memory space is NULL and we don't want it to be read-only type for the server, we keep it as 0. */

addr_attach_shm=shmat(shmid,NULL,0); //by default a ptr is an unsigned int type, so return value need not be type casted

if(addr_attach_shm<0)
{
perror("shmat");
exit(2);
}

char *char_ptr_addr_space=(char*)addr_attach_shm;
char ch='a';

for(i=0;i<26;i++)
*(char_ptr_addr_space+i)=ch++;

*(char_ptr_addr_space+i)='\0';

puts("Server wrote: ");
for(ch=*char_ptr_addr_space,i=0;ch!='\0';++i,ch=*(char_ptr_addr_space+i))
printf("%c ",ch);
puts("");
/* now this process should wait for the other process to read the shared memory. */

sleep(10);

shmdt(addr_attach_shm); // afte the job is done, detach from the shared mem

shmctl(shmid,IPC_RMID,NULL);

return 0;
}
