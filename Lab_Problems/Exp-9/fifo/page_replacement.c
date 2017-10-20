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
	int frames[MAX] = {0};
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
	int frames[MAX] = {0}, min, present=0, i, j, k, k_min = 0, new_start;

	for(k=0,i=0;k<fr;k++,i++)
	{
		frames[k] = pages[i];
		puts("Page miss");
		print_frames(frames,fr);
	}
	
	//remain_page = n-fr;

	new_start = k;

	for(i=new_start;i<n;i++)
	{
		min = MAX; //for each page[i] reset min (holds the page index of lr element)
		present = 0;
		for(k=0;k<fr;k++)
		{
			if(pages[i]==frames[k])
			{
				present = 1;
				puts("Page hit");
				break;
			}
		}
		
		if(present == 0)	
		{
			puts("Page miss");
				for(k=0;k<fr;k++)
				{
					for(j=i-1;j>=0;j--)
					{
						if(frames[k] == pages[j])	
						{
							if(j<=min)
							{
								min = j;
								k_min = k;
							}
							break;
						}
					}
				}
				frames[k_min] = pages[i];
				print_frames(frames,fr);
	
		}
		else
			print_frames(frames,fr);
	}
}

void opt(int pages[],int n, int fr)
{
	int frames[MAX] = {0}, max=0, present=0, i, j, k, k_max = 0, new_start, unused_in_future;

	for(k=0,i=0;k<fr;k++,i++)
	{
		frames[k] = pages[i];
		puts("Page miss");
		print_frames(frames,fr);
	}
	
	//remain_page = n-fr;

	new_start = k;

	for(i=new_start;i<n;i++)
	{
		max = 0; //for each page[i] reset min (holds the page index of lr element)
		present = 0;
		for(k=0;k<fr;k++)
		{
			if(pages[i]==frames[k])
			{
				present = 1;
				puts("Page hit");
				break;
			}
		}
		
		if(present == 0)	
		{
			puts("Page miss");
				for(k=0;k<fr;k++) // for each frame..
				{
					unused_in_future = 1; //for frame (to check if unused in future)
					for(j=i+1;j<n;j++) // ..for each page after current page being allocated..
					{
						if(frames[k] == pages[j]) // ..check if frame will be used afterwards by comparing with each pages[j] ..
						{
							unused_in_future = 0;
							if(j>=max)
							{
								max = j;
								k_max = k;
							}
							break;
						}
					}
					if(unused_in_future == 1) // if frame unused in future, stop comapring other frames...
					{
						k_max = k;
						break;
					}
				}
				frames[k_max] = pages[i];
				print_frames(frames,fr);
	
		}
		else
			print_frames(frames,fr);
	}
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