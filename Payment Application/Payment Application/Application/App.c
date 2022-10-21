#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Server/server.h"
#include "app.h"



void appStart(ST_transaction_t* transData)
{
    ST_transaction_t Transaction_Data;
   
    while (1)
    {
        if (getCardHolderName(&Transaction_Data.cardHolderData) != CARD_OK)
        {
            printf("\nCardholder's name is between 20 characters to 24 .try agin!\n");
            continue;
        }
        else
        {
            break;
        }
    }
    while (1)
    {
        if (getCardExpiryDate(&Transaction_Data.cardHolderData) != CARD_OK)
        {
            printf("\nWrong date format .try agin!\n");
            continue;
        }
        else
        {
            break;
        }
    }
    while (1)
    {
        if (getCardPAN(&Transaction_Data.cardHolderData) != CARD_OK)
        {
            printf("\ncard's Primary Account Number is between 16 characters to 19 .try agin!\n");
            continue;
        }
        else
        {
            break;
        }
    }
    printf("\nCARD module done \n");

    while (1)
    {
        if (getTransactionDate(&Transaction_Data.terminalData) != CARD_OK)
        {
            printf("\nWrong date format .try agin!\n");
            continue;
        }
        else
        {
            break;
        }
    }
                   
            if (isCardExpired(Transaction_Data.cardHolderData, Transaction_Data.terminalData) == TERMINAL_OK)
            {
                if(getTransactionAmount(&Transaction_Data.terminalData) == TERMINAL_OK)
                {
                    if (setMaxAmount(&Transaction_Data.terminalData) == TERMINAL_OK)
                    {
                        if (isBelowMaxAmount(&Transaction_Data.terminalData) == TERMINAL_OK)
                        {
                            printf("\nTerminal module done \n");
                            recieveTransactionData(&Transaction_Data);
                        }
                        else
                        {
                            printf("\nDECLINED Amount Exceeding Limit ");
                        }
                    }
                }
            }
            else
            {
                printf("\nDECLINED EXPIRED CARD ");
            }
          
                     
}