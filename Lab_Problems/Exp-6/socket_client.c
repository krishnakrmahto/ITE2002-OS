#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<unistd.h>
#define NUM_OF_CONNECTIONS 20

int main(int argc,char* const argv[])
{
int count=0;
const char* const socket_name = argv[1]; // same as the socket name created by the server

do
{

struct sockaddr_un name;
int client_fd;

client_fd = socket(PF_LOCAL,SOCK_STREAM,0);

/* fill in the server details into client's name structure,ie, client_name= serve_ name */
name.sun_family=AF_LOCAL;
strcpy(name.sun_path,socket_name);

connect(client_fd,(struct sockaddr*)&name,SUN_LEN(&name)); //check symmetry with the accept() sys call in server code
char *buffer;

if(count!=NUM_OF_CONNECTIONS)
{
sprintf(buffer,"Client %d",count++);
write(client_fd,buffer,strlen(buffer));
}
else
{
sprintf(buffer,"exit");
count++;
write(client_fd,buffer,strlen(buffer));
}
close(client_fd);
}while(count<=NUM_OF_CONNECTIONS);

return 0;

}
