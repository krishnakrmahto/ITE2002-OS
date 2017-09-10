#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<sys/types.h>
typedef struct args
{
int to_account;
int to_account_balance;
int from_account;
int from_account_balance;
float trans_amnt;
}TRANSDETAILS;

void* bank_transaction(void *trans_det) // thread function for carrying out bank transactions
{
int default_canceltype; //it shall be used to store the default cancellation type.

TRANSDETAILS *trans_details=(TRANSDETAILS*)trans_details;
if(trans_details->from_account<trans_details->trans_amnt)
return 1;

/*since the transaction is about to be started, the following section should be invincible to cancellation attempts made by any other thread*/

pthread_setcanceltype(PTHREAD_CANCEL_DISABLE,&default_canceltype); //setting cancellation for the transaction part disabled

trans_details->to_account+=trans_details->trans_amnt;
trans_details->from_accounte-=trans_details->trans_amnt;

pthread_canceltype(defaul_canceltype,NULL); // resetting the cancellation type

int return_val=0;
return (void*)&return_val;
}

int main(int argc,char **argv)
{
TRANSDETAILS *transdets;
pthread_t *thread_id;
int trans_status;

transdets=(TRANSDETAILS*)malloc(sizeof(TRANSDETAILS));
puts("Enter source account number:");
scanf("%d",&(transdets->from_account));
puts("");
puts("Enter source account balance: ");
scanf("%d",&(transdets->from_account_balance));
puts("");
puts("Enter the destination account number:");
scanf("%d",&(transdets->to_account));
puts("");
puts("Enter the destination account balance:");
scanf("%d",&(transdets->to_account_balance));
puts("");
puts("Enter the amount to be transferred:");
scanf("%d",&(transdets->trans_amnt));

pthread_create(thread_id,NULL,&bank_transaction,transdets);

puts("Transaction thread is going on...");

pthread_join(trans_id,(void*)trans_status);

if(trans_status==0) 

else
{
puts("Source acc balance is not sufficient!");
exit(1);
}
return 0;
}
