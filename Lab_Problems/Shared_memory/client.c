#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<unistd.h>
#include<ctype.h>

int main(int argc, char** argv)
{

key_t key=5678;

int i;

unsigned int *attach_to_address_space;

mode_t mode=S_IWUSR | S_IRUSR | S_IROTH;

int shmid=shmget(key,4096,mode);
if(shmid<0)
{
perror("shmid");
exit(1);
}

attach_to_address_space=shmat(shmid,NULL,0); //attach the shm for read only

char *char_attach_to_address_space=(char*)attach_to_address_space;
for(i=0;i<26;i++)
printf("%c",toupper(*(char_attach_to_address_space+i)));

shmdt(attach_to_address_space);

shmctl(shmid,IPC_RMID,NULL);

return 0;

}
