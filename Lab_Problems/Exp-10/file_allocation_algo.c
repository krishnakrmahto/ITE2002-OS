#include<stdio.h>
#include<stdlib.h>

// 1 disk unit each of MAX_DISK_DISK is equal to 512 Bytes
#define MAX_DISK 5
#define occupied 1
#define free 0


// 1 index location represents 1 block of disk = 512 Bytes
int disk[MAX_DISK];
int file_size = 2;


void contiguous()
{
	int i,flag[MAX_DISK];

	for(i=0;i<MAX_DISK;i++)
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

void indexed()
{
	int file_index[2], i, j=0,limit = file_size;

	for(i=0;i<MAX_DISK && limit;i++)
	{
		if(disk[i] == free)
		{
			disk[i] = occupied;
			file_index[j++] = i;
			limit--;
		}
	}
	if(j==2)
	{
		puts("File allocation successful");
		printf("Following is the status of the file index:\nfile 1: %d\nfile 2: %d\n",file_index[0],file_index[1]);
		return ;
	}
	else
	{
		puts("Indexed allocation not possible.");
		return ;
	}


}

void linked()
{
	typedef struct linked_disk
	{
		int space;
		struct linked_disk* next;
	}LD;

	LD *head, *new;

	head = (LD*)malloc(sizeof(LD));
	head->space = occupied;
	head->next = NULL;

	new = (LD*)malloc(sizeof(LD));
	new->space = occupied;
	new->next = NULL;
	head->next = new;

	LD *temp;

	puts("File allocation completed.");
}

int main(int argc, char* argv[])
{
	int choice,i,j;

	puts("Vacant disk locations type:\n1. Contiguous?\n2. Non-contiguous?");
	scanf("%d",&choice);

	switch(choice)
	{
		case 1:
		for(i=0;i<MAX_DISK;i++)
			disk[i] = free;
		break;

		case 2:
		for(i=0;i<MAX_DISK;i++)
		{
			if(i%2 == 0)
				disk[i] = occupied;
			else
				disk[i] = free;
		}

	}
	
	do
	{

		puts("");

		puts("Select allocation type:\n1. Contiguous\n2. Indexed\n3. Linked\n4. Exit");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
			contiguous();
			break;

			case 2:
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