#include<stdio.h>
#include<stdlib.h>

#define MAX 5
#define false 0
#define true 1

//n = number of processes
//m = number of resource types
//compare = matrix comparator

int available[MAX]; //holds available number of instances for each resource i
int max[MAX][MAX]; //n*m matrix holds max demand for each process
int allocation[MAX][MAX]; //n*m matrix holds number of resources of each type allocated to each process
int need[MAX][MAX]; //n*m matrix remaining resource need for each process
int n,m;
int request[MAX];

int compare(int need[],int work[])
{
	int i;
	for(i=0;i<n;i++)
	{
		if(need[i]<=work[i])
			continue;
		else
			return 0;
	}
	if(i==n-1)
		return 1;
}

int safety_algorithm()
{
	int finish[n], *work, i, j, flag = false, safe = true;

	work = available;
	for(i=0;i<n;i++)
		finish[i]=false;
	for(i=0;i<n;i++)
	{
		if((finish[i]==false) && compare(need[i],work))
		{
			flag = true;
			for(j=0;j<m;j++)
				work[j] += allocation[i][j];
			finish[i] = true;
			continue;
		}
		
		else if(i<n-1)
			continue;
	}

	if(flag == false)
		for(i=0;i<n;i++)
			finish[i]=true;

	for(i=0;i<n;i++)
		if(finish[i] == false)
		{
			safe = false;
			break;
		}

	return safe;

}



int main(int argc,char *argv[])
{

	int i,j,n,m,requesting_process,safe; //i for iterating through n processes and j for iterating through m processes

	puts("Enter the number of processes: ");
	scanf("%d",&n);
	puts("");

	puts("Enter the number of resource types: ");
	scanf("%d",&m);
	puts("");

	puts("Enter the Available matrix");
	for(j=0;j<m;j++)
	{
		printf("Resource %d: ",j);
		scanf("%d",&available[j]);
	}
	puts("");

	puts("Enter the Max matrix: ");
	for(i=0;i<n;i++)
	{
		printf("Process %d\n",i);
		for(j=0;j<m;j++)
			scanf("%d",&max[i][j]);
		puts("");
	}
	puts("");

	puts("Enter the Allocation matrix:");
	for(i=0;i<n;i++)
	{
		printf("Process %d\n",i);
		for(j=0;j<m;j++)
			scanf("%d",&allocation[i][j]);
		puts("");
	}
	puts("");

	for(i=0;i<n;i++)
		for(j=0;j<m;j++)
			need[i][j]=max[i][j]-allocation[i][j];
	puts("");

	safe = safety_algorithm();

	if(safe == false)
	{
		puts("System is in unsafe state!");
		puts("Exiting...");
		exit(1);
	}
	
	else
	{
		puts("Enter the process requesting: ");
		scanf("%d",&requesting_process);

		puts("Enter the Request matrix: ");
		for(j=0;j<m;j++)
			scanf("%d",&request[j]);

		if(compare(request,need[requesting_process]))
		{
			if(compare(request,available))
			{
				for(j=0;j<m;j++)
				{
					available[j] = available[j]-request[j];
					allocation[requesting_process][j] = allocation[requesting_process][j] + request[j];
					need[requesting_process][j] = need[requesting_process][j] - request[j];
				}
				safe = safety_algorithm();

				if(safe) 
				{
					puts("Resources allocated successfully.");
					exit(0);
				}
				else
				{
					//restore to previous allocation state
					available[j] = available[j] + request[j];
					allocation[requesting_process][j] = allocation[requesting_process][j] - request[j];
					need[requesting_process][j] = need[requesting_process][j] + request[j];
				}

			}
			else
			{
				printf("Process_%d must wait\n",requesting_process);
				exit(1);
			}
		}
		else
		{
			puts("Maximum request limit exceeded");
			exit(1);
		}
	}
	return 0;
}