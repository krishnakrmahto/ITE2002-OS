#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

typedef struct args
{
int to_account;
int from_account;
float trans_amnt;
}TRANSDETAILS;

void* bank transaction(void *trans_det) // thread function for carrying out bank transactions
{
int default_canceltype; //it shall be used to store the default cancellation type.

TRANSDETAILS *trans_details=(TRANSDETAILS*)trans_details;
if(trans_details->from_account<trans_details->trans_amnt)
return 1;

/*since the transaction is about to be started, the following section should be invincible to cancellation attempts made by any other thread*/

pthread_setcanceltype(PTHREAD_CANCEL_DISABLE,&default_canceltype)

trans_details->to_account+=trans_details->trans_amnt;
trans_details->from_account-=trans_details->trans_amnt;

return 0;
}



