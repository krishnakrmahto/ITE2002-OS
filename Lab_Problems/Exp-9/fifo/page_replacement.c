#include<stdio.h>
#include<stdio_ext.h>
#include<stdlib.h>
#define MAX 10

void print_frames(int frames[],int fr)
{
	int i;
	for(i=0;i<fr;i++)
		printf("%d\t",frames[i]);
	puts("\n");
}

void fifo(int pages[],int n, int fr)
{
	int frames[MAX];
	int i,j,present=0,fr_index=0;

	for(i=0;i<n;i++)
	{
		present = 0;
		for(j=0;j<fr;j++)
		{
			if(frames[j]==pages[i])
			{
				present = 1;
				puts("Page hit");
				break;
			}
		}

		if(present == 0)
		{
			puts("Page miss");
			frames[fr_index++ % fr] = pages[i];
		}
		print_frames(frames,fr);

	}
}

void lru(int pages[],int n,int fr)
{
	printf("haha");
}

void opt(int pages[],int n, int fr)
{
	puts("hahaha");
}

int main(int argc,char *argv[])
{
	int choice=0, pages[MAX], i,fr=0, n=0;


	puts("Enter the number of pages:");
	scanf("%d",&n);

	puts("Enter the pages:");
	for(i=0;i<n;i++)
		scanf("%d",&pages[i]);

	puts("Enter number of frames: ");
	scanf("%d",&fr);

	puts("Choose scheduling algorithm:");
	puts("1. FIFO");
	puts("2. LRU");
	puts("3. OPT");

	scanf("%d",&choice);

	switch(choice)
	{
		case 1:
		fifo(pages,n,fr);
		break;

		case 2:
		lru(pages,n,fr);
		break;

		case 3:
		opt(pages,n,fr);
		break;
	}

	return 0;
}