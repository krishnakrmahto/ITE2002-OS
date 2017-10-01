#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

float *initial_appointments(int *num_patients)
{
int i,n=0;
puts("Enter the number of patients:");
scanf("%d",&n);

float patients_array[n];

puts("Enter estimated consultation time for each patient: ");
for(i=0;i<n;i++)
scanf("%f"&patients_array[i]);

*num_patients=n;
return patients_array;
}

void send_in(float *patients_queue,int *num_patients)
{
printf("Patient number %d has been sent for consultation.\n",*num_patients);
sleep(*(patients_queue+(*num_patients)));
printf("Patient number %d has finished.\n\n",(*num_patients)--);
}

void new_appointment(float *patients_queue,int *num_patients)
{
puts("Enter the estimated consultation time:");
scanf("%f",*(patients_queue+(++(*num_patients)));
}

void show_queue(int *patients_queue,int num_appointments)
{
int i;
for(i=0;i<=num_appointments;i++)
printf("Patient %d:\nConsultation time: %f\n\n",i,*(patients_queue+i));
}

int main(int argc,char **argv)
{
float *patients_queue,num_patients=0,choice=0;

patients_queue=initial_appointments(&num_patients);

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
	send_in(patients_queue,&num_patients);
	break;

	case 2:
	new_appointment(patients_queue,&num_patients);
	break;

	case 3:
	show_queue(patients_queue,num_patients);
	break;
}
}

return 0;
}
