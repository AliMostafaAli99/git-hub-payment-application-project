#include <stdio.h>
#include "../Terminal/terminal.h"
#include "../Card/card.h"
#include "server.h"
#include <stdint.h>


int acount_num ;
uint32_t sequence_number = 0;
ST_accountsDB_t arr_valid_accounts_database[255] = { {2000.0,RUNNING,"8989374615436851"},
													 {100000.0,BLOCKED,"5807007076043875"},
													 {3000.0,RUNNING,"1234567890123456"}, 
													 {50000.0,RUNNING,"6543210987654321"},
													{100000.0,BLOCKED,"1023456789123456"},
													{500750.0,RUNNING,"9638527419638520"} };

ST_transaction_t arr_transactions_database[255]={0};

EN_serverError_t isValidAccount(ST_cardData_t cardData, ST_accountsDB_t accountRefrence[])
{
	
	for ( acount_num = 0;acount_num < 255 ;acount_num++)
	{
		if (strncmp(accountRefrence[acount_num].primaryAccountNumber , cardData.primaryAccountNumber ,16) == 0)
		{
			printf("\nSERVER_OK_from_function_isValidAccount");
			printf("\naccount_num = %d", acount_num);
			/*break;*/
			return SERVER_OK;
			
		}
	}
	printf("\nACCOUNT_NOT_FOUND_isValidAccount");
	return ACCOUNT_NOT_FOUND;
	
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence[])
{
	return (arr_valid_accounts_database[acount_num].state == RUNNING) ? SERVER_OK : BLOCKED_ACCOUNT;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
	return (arr_valid_accounts_database[acount_num].balance < (*termData).transAmount) ? LOW_BALANCE : SERVER_OK;
}

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	if (sequence_number < 255)
	{
		transData->transactionSequenceNumber = sequence_number;
		arr_transactions_database[sequence_number] = *transData;
		sequence_number++;
		printf("\nSERVER_OK_Transaction_Saved");
		return SERVER_OK;
	}
	else
	{
		printf("\nSAVING_FAILED");
		return SAVING_FAILED;
		
	}
}
EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	if (isValidAccount( transData->cardHolderData, arr_valid_accounts_database)== SERVER_OK)	
	{
		printf("\nSERVER_OK----Account is Valid");
		if (isBlockedAccount(arr_valid_accounts_database) == SERVER_OK)
		{
			printf("\nSERVER_OK----Account is runing");
		
					if (isAmountAvailable(&transData->terminalData) == SERVER_OK)
					{
		
						printf("\nSERVER_OK----amount is available");
										if (saveTransaction(&transData) == SERVER_OK)
										{
											printf("\n  your balance equal = %f", arr_valid_accounts_database[acount_num].balance);
											/*printf("\naccount_num = %d", acount_num);*/
											arr_valid_accounts_database[acount_num].balance = arr_valid_accounts_database[acount_num].balance - transData->terminalData.transAmount;
											printf("\nnew balance equal = %f", arr_valid_accounts_database[acount_num].balance);
											printf("\nSERVER_OK---- Transaction saved");
											printf("\nAPPROVED");
											return APPROVED;
										}
										else
										{
											printf("\nINTERNAL_SERVER_ERROR");
											return INTERNAL_SERVER_ERROR;
										}
					}
					else
					{
						printf("\nDECLINED_INSUFFECIENT_FUND");
						saveTransaction(&transData);
						return DECLINED_INSUFFECIENT_FUND;
					}
	    }
		else
		{
			printf("\nDECLINED_BLOCKED_ACCOUNT");
			saveTransaction(&transData);
			return DECLINED_BLOCKED_ACCOUNT;
		}
	}
	else
	{
		printf("\nFRAUD_CARD");
		printf("\nDeclined_Invalid_ACCOUNT");
		return FRAUD_CARD;
	}
}
