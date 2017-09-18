#include<stdio.h>
#include<sys/types.h> //for size_t
#include<unistd.h> // for getpagesize()
int main()
{
size_t page_size=getpagesize();
printf("size of the page: %d bytes.\n\n",(int)page_size);

return 0;
}
