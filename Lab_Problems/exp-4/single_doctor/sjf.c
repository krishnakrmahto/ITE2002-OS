#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#define MAX 100

float patients_array[MAX];

void initial_appointments(int *num_patients)
{
int i,n=0;
puts("Enter the number of patients:");
scanf("%d",&n);

puts("Enter estimated consultation time for each patient: ");
for(i=0;i<n;i=(i+1)%MAX)
scanf("%f",&patients_array[i]);

*num_patients=n;
}

/* comparator for qsort() */
int comparator(const void *x,const void *y)
{
float *xx=(float*)x;
float *yy=(float*)y;
if(*xx>*yy)
return 1;
if(*xx<*yy)
return -1;

return 0;
}

int send_in(int *num_patients)
{
static int send=0;

if(send==(((*num_patients)+1)%MAX))
{
puts("No more patients!");
return MAX;
}

printf("Patient number %d has been sent for consultation.\n",send);
sleep(patients_array[send]);
printf("Patient number %d has finished.\n\n",send=(send+1)%MAX);

return send;// return the patient number which will be sent
}

void new_appointment(int *num_patients,int send)
{
float consult_time=0;
int i,j;
puts("Enter the consultation time: ");
scanf("%f",&consult_time);

for(i=send;i<=*num_patients;i=(i+1)%MAX)
{
if(patients_array[i]>consult_time)
continue;// compare with the next element in the array

else
{

j=*num_patients+1;
for(;j>i;j=(j-1)%MAX)//right shift the contents of array
patients_array[j]=patients_array[j-1];

patients_array[i]=consult_time;
*num_patients=(*num_patients+1)%MAX;

}
}
}

void show_queue(int num_appointments,int send)
{
int i;
for(i=send;i<num_appointments;i=(i+1)%MAX)
printf("Patient %d:\n\tConsultation time:\t %.2f\n\n",i,patients_array[i]);
}

int main(int argc,char **argv)
{
int num_patients=0,choice=0,send=0; // num_patients holds the last patient number in the queue

initial_appointments(&num_patients);
show_queue(num_patients,send);
qsort((void*)patients_array,sizeof(patients_array)/sizeof(float),sizeof(float),comparator);
for(;num_patients+1;) //until num_patients>=0
{
puts("1. Send in");
puts("2. New appointent");
puts("3. Show queue\n");

scanf("%d",&choice);
puts("");
switch(choice)
{
	case 1:
	send=send_in(&num_patients);
	break;

	case 2:
	new_appointment(&num_patients,send);
	break;

	case 3:
	show_queue(num_patients,send);
	break;
}
}

return 0;
}
