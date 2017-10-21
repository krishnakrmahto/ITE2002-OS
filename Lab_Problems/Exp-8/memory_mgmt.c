#include<stdio.h>
#include<stdlib.h>

#define MAX_BLOCKS 10
#define MAX_FILES 20


const int hole_size = 1024;
int files[MAX_FILES];

void memory_status(const int blocks[],int blocks_num)
{
	int i;

	puts("Memory status: ");
	for(i=0;i<blocks_num;i++)
		printf("| %d ",blocks[i]);
	puts("|");
}


void first_fit(int blocks[],const int blocks_num,const int files_num)
{
	int i,j,allocated,unallocated[MAX_FILES],unalloc_count=0;

	for(i=0;i<files_num;i++)
	{
		allocated = 0;
		for(j=0;j<blocks_num;j++)
		{
			if(files[i] <= blocks[j])
			{
				blocks[j] -= files[i];
				allocated = 1;
				printf("\nFile %d allocated in block %d\n",i,j);
				break;
			}
			else
				continue;
		}
		if(allocated == 0)
		{
			printf("\nFile %d Cannot be allocated\n",i);
			unallocated[unalloc_count++] = files[i];
		}
		
		memory_status(blocks,blocks_num);
	}
}

void best_fit(int blocks[],const int blocks_num,const int files_num)
{

}

int main(int argc,char *argv)
{
	int blocks[MAX_BLOCKS];
	int blocks_num,choice,blocks_sum=0,files_num,i;

	puts("Enter the number of blocks: ");
	scanf("%d",&blocks_num);
	puts("");

	puts("Enter block sizes:");
	for(i=0;i<blocks_num && blocks_sum <= hole_size;i++)
	{
		if(i == blocks_num-1)
		{
			blocks[i] = hole_size - blocks_sum; //fill the last block automatically
			break;
		}

		scanf("%d",&blocks[i]);
		blocks_sum += blocks[i];
	}
	puts("");

	if(blocks_sum > hole_size)
	{
		printf("Hole size is only: %d\n",hole_size);
		exit(0);
	}
	puts("");

	memory_status(blocks,blocks_num);


	puts("Enter the number of files");
	scanf("%d",&files_num);
	puts("");

	puts("Enter the file sizes: ");
	for(i=0;i<files_num;i++)
		scanf("%d",&files[i]);
	puts("");

	puts("Which algorithm?\n1. First fit\n2. Best fit\n3. Worst fit");
	scanf("%d",&choice);
	puts("");

	switch(choice)
	{
		case 1:
		first_fit(blocks,blocks_num,files_num);
		break;

		case 2:
		best_fit(blocks,blocks_num,files_num);
		break;

		case 3:
		//worst_fit(blocks,blocks_num,files_num);
		break;
	}



	return 0;
}