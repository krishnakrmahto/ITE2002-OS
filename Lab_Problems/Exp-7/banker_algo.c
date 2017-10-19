#include<stdio.h>
#include<stdlib.h>
#define RESOURCE_TYPES_NUM 3
#define NUM_OF_PROCESSES 5

int available[RESOURCE_TYPES_NUM];
int allocation[NUM_OF_PROCESSES][RESOURCE_TYPES_NUM];
int max[NUM_OF_PROCESSES][RESOURCE_TYPES_NUM];
int need[NUM_OF_PROCESSES][RESOURCE_TYPES_NUM];

/* safety algorithm */

int safety_algorithm()
{
int finish[NUM_OF_PROCESSES],work[RESOURCE_TYPES_NUM];
int i,j,count=0;

/*initialising work and finish arrays */
for(i=0;i<RESOURCE_TYPES_NUM;i++) // work = available
work[i]=available[i];

for(i=0;i<NUM_OF_PROCESSES;i++) // finish = false for all processes
finish[i] = 0;

/* second step */

for(i=0;i<NUM_OF_PROCESSES;i++)
{
if(finish[i] == 0)
for(j=0;j<RESOURCE_TYPES_NUM;j++)
if(need[i][j] <= work[j])
continue;
else
{
count++;
break;
}

else
count++ ;
}

if(count==NUM_OF_PROCESSES)
for(i=0;i<NUM_OF_PROCESSES;i++)
if(finish[i] == 1)
continue;

else
{
puts("System is not in safe state!");
break;
}




int main(int argc,char **args)
{

int i;
puts("Enter the num of resources for each type: ");
for(i=0;i<RESOURCE_TYPES;i++)
scanf("%d",&available[i]);
puts("");

puts("Enter the maximum demand of each process:");
for(i=0;i<NUM_OF_PROCESSES;i++)
for(j=0;j<RESOURCE_TYPES_NUM;j++)
scanf("%d",&max[i][j]);
puts("");

puts("Fill the allocation matrix: ");
for(i=0;i<NUM_OF_PROCESSES;i++)
for(j=0;j<RESOURCE_TYPES_NUM;j++)
scanf("%d",&allocation[i][j]);
puts("");

/* NEED MATRIX */
for(i=0;i<NUM_OF_PROCESSES;i++)
for(i=0;i<RESOURCE_TYPES_NUM;i++)
need[i][j] = max[i][j] - allocation[i][j];

puts("Checking if the state is safe...");
safety_algorithm();
