#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<unistd.h>
#include<semaphore.h>

sem_t num_of_connections;

int server(int client_fd)
{
char buffer[20];
sleep(2);
read(client_fd,buffer,20);
printf("%s \n",buffer);

if(strcpy(buffer,"exit")==0)
{
free(buffer);
return 1;
}

free(buffer);

return 0;
}

int main(int argc,char* const argv[])
{

const char* const socket_name=argv[1]; // const char* = value pointed by the pointer is const. const socket_name = the pointer variable name socket_name is also constant

int n=0,exit=0;
puts("Enter the number of connections that the server should handle at a time: \n");
scanf("%d",&n);

sem_init(&num_of_connections,0,n);

int server_fd;
struct sockaddr_un name; // address structure holds the socket address for binding 

server_fd = socket(PF_LOCAL,SOCK_STREAM,0); //protocol parameter = 0 for local namespace, PF_LOCAL indicates that the server socket will follow local namespace, this information is for the reference of server socket itself

/* filling values into address structure of the server */

name.sun_family = AF_LOCAL; //indicates that the address structure is of local namespace. this information is used by client when client stores server's address to maintain that server follows local namespace, this information is for the reference of client socket
strcpy(name.sun_path,socket_name);

/* bind the server socket fd with the server socket address */

bind(server_fd,&name,SUN_LEN(&name));

/* server should now listen for connections from clients */

listen(server_fd,5); // the max number of requests that can stay in waiting queue= 5

do
{
int client_fd;
struct sockaddr_un client_name;
socklen_t client_name_len;

sem_wait(&num_of_connections);
client_fd = accept(server_fd,&client_name,&client_name_len);

/*handle the connection*/

server(client_fd);

/*close connection for client that returns */

exit=close(client_fd);
}while(exit!=1);

close(server_fd);
unlink(socket_name);

return 0;
}
