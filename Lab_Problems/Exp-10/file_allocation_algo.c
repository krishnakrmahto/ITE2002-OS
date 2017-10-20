#include<stdio.h>
#include<stdlib.h>

// 1 disk unit each of MAX_DISK is equal to 512 Bytes
#define MAX_DISK 5
#define occupied 1
#define free 0


// 1 index location represents 1 block of disk = 512 Bytes
int disk[MAX];


void contiguous()
{
	int i,flag[MAX];

	for(i=0;i<MAX && ;i++)
	{
		if(disk[i] == free)
		{
			disk[i] = occupied;
			flag[i] = 1; // indicates ith disk space got occupied
			if(i != 0 && flag[i-1] == 1)
			{
				puts("File allocation completed");
				return ;
			}
			continue;
		}
		if(disk[i] == occupied && flag[i-1] == 1)
		{
			puts("Contiguous allocation not possible.");
			return ;
		}
	}
}

int main(int argc, char* argv[])
{
	int choice,i,j;

	puts("Vacant disk locations type:\n1. Contiguous?\n2. Non-contiguous?");
	scanf("%d",&choice);

	switch(choice)
	{
		case 1:
		for(i=0;i<MAX;i++)
			disk[i] = free;
		break;

		case 2:
		for(i=0;i<MAX;i++)
		{
			if(i%2 == 0)
				disk[i] = occupied;
			else
				disk[i] = free;
		}

	}

	puts("");

	puts("Select allocation type:\n1. Contiguous\n2. Indexed\n3. Linked\n4. Exit");
	scanf("%d",&choice);

	do
	{
		switch(choice)
		{
			case 1:
			contiguous();
			break;

			case 2;
			indexed();
			break;

			case 3:
			linked();
			break;

			case 4:
			exit(0);
		}
	}while(1);

	return 0;
}