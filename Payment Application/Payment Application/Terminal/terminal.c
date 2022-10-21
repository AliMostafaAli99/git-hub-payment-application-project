#include <stdio.h>
#include "terminal.h"
#include "../Card/card.h"


EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
        printf("\nPlease Enter transaction date in the format DD/MM/YYYY :");
        fgets(&termData->transactionDate, sizeof(termData->transactionDate), stdin);

        if (strlen(termData->transactionDate) != 11) { printf("WRONG_DATE!=10"); return WRONG_DATE; }
        // Every string in C ends with '\0'. that is why we add one in the condition
        for (int i = 0;i < 4;i++)
        {
            if (i == 2 || i == 5) continue;
            if (isdigit(termData->transactionDate[i]) == 0)
            {
                printf("digit number %d is not numircal.", i);
                printf("WRONG_EXP_DATE");
                return WRONG_DATE;
            }

        }
        if (termData->transactionDate[2] != 47 || termData->transactionDate[5] != 47  /*47 equal "/"*/)
        {
            printf("format in digit number 2 or 5 is't  correct.");
            return WRONG_DATE;
        }
        printf("TERMINAL_OK");
        return TERMINAL_OK;
}

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{

   
    if (cardData.cardExpirationDate[3, 4] > termData.transactionDate[8, 9])
    {
        printf("\nvalid year_TERMINAL_OK");
        return TERMINAL_OK;
    }
    if (cardData.cardExpirationDate[3, 4] < termData.transactionDate[8, 9])
    {
        printf("\nEXPIRED_CARD");
        return EXPIRED_CARD;
    }

    if (cardData.cardExpirationDate[3, 4] == termData.transactionDate[8, 9])
    {
       if (cardData.cardExpirationDate[0, 1] >= termData.transactionDate[3, 4])
        {
           printf("\nvalid mounth_TERMINAL_OK");
           return TERMINAL_OK;
        }
       else
       {
           printf("\nEXPIRED_CARD");
           return EXPIRED_CARD;
       }
    }
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	printf("\nPlease Enter the transactionamount:  ");
	scanf_s("%f", &(*termData).transAmount);
	if ((*termData).transAmount <= 0)
	{
		printf("\nINVALID_AMOUNT");
		return INVALID_AMOUNT;
	}
	else
	{
		printf("\nTERMINAL_OK");
		return TERMINAL_OK;
	}
}
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	(* termData).maxTransAmount = 10000; //Assign 10000 for terminal max amount
	return ((*termData).maxTransAmount <= 0) ? INVALID_MAX_AMOUNT : TERMINAL_OK;
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	return ((*termData).transAmount > (*termData).maxTransAmount ) ? EXCEED_MAX_AMOUNT : TERMINAL_OK;
}