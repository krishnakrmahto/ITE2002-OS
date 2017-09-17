#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<unistd.h>

int main(int argc, char** argv)
{

int i;

unsigned int *attach_to_address_space;

mode_t mode=S_IWUSR | S_IRUSR | S_IROTH;

int shmid=shmget(5588,26,mode);
if(shmid<0)
{
perror("shmid");
exit(1);
}

attach_to_address_space=shmat(shmid,NULL,SHM_RDONLY); //attach the shm for read only

char *char_attach_to_address_space=(char*)attach_to_address_space;

for(i=0;i<26;i++)
printf("%s",strupr(attach_to_address_space));

shmdt(attach_to_address_space);

shmctl(shmid,IPC_RMID,NULL);

return 0;

}
