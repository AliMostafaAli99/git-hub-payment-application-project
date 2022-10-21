/*server.h*/

#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Application/app.h"
#include <stdint.h>
#ifndef server
#define server


typedef enum EN_transState_t
{
	APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD, INTERNAL_SERVER_ERROR, DECLINED_BLOCKED_ACCOUNT
}EN_transState_t;

typedef struct ST_transaction_t
{
	ST_cardData_t cardHolderData;
	ST_terminalData_t terminalData;
	EN_transState_t transState;
	uint32_t transactionSequenceNumber;
}ST_transaction_t;

typedef enum EN_accountState_t
{
	RUNNING,
	BLOCKED
}EN_accountState_t;

typedef enum EN_serverError_t
{
	SERVER_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE, BLOCKED_ACCOUNT
}EN_serverError_t;

typedef struct ST_accountsDB_t
{
	float balance;
	EN_accountState_t state;
	uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;

extern ST_accountsDB_t arr_valid_accounts_database[255];
extern int acount_num;
extern ST_transaction_t arr_transactions_database[255];
extern uint32_t sequence_number ;


EN_transState_t recieveTransactionData(ST_transaction_t* transData);
EN_serverError_t isValidAccount(ST_cardData_t cardData, ST_accountsDB_t accountRefrence[]);
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence[]);
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData);
EN_serverError_t saveTransaction(ST_transaction_t* transData);
EN_serverError_t getTransaction(int transactionSequenceNumber, ST_transaction_t* transData);

#endif /*server.h*/
