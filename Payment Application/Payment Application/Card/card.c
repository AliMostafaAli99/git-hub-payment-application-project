#include <stdio.h>
#include "card.h"
#include <stdint.h>
#include <ctype.h>



EN_cardError_t getCardHolderName( ST_cardData_t* cardData)
{
  
    printf("Please Enter Cardholder's name: ");
    fgets(cardData->cardHolderName, sizeof(cardData->cardHolderName), stdin);
    
    printf("Length of CardHolderName = %zu \n", strlen(cardData->cardHolderName)-1);
   
    if (strlen(cardData->cardHolderName) > 25 || strlen(cardData->cardHolderName) < 21)
        // Every string in C ends with '\0'. that is why we add one in the condition
    {
        printf("WRONG_NAME\n");
        return WRONG_NAME;
    }
    else 
    {
        printf("CARD_OK\n");
        return CARD_OK;
    }
  
}
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{ 
    printf("\nPlease Enter card expiry date in the format MM/YY :");
    fgets(&cardData->cardExpirationDate, sizeof(cardData->cardExpirationDate), stdin);

    if (strlen(cardData->cardExpirationDate) != 6) { printf("WRONG_EXP_DATE!=5"); return WRONG_EXP_DATE;  }
    // Every string in C ends with '\0'. that is why we add one in the condition
    for (int i =0;i<4;i++)
    { if (i == 2) continue;
        if (isdigit(cardData->cardExpirationDate[i]) == 0)
        { 
          printf("digit number %d is not numircal.", i);
          printf("WRONG_EXP_DATE");
          return WRONG_EXP_DATE;
        }
       
    }  
        if (cardData->cardExpirationDate[2] != 47 /*47 equal "/"*/)
        {printf("format in digit number 2 is't  correct.");
            return WRONG_EXP_DATE;
        }
        printf("CARD_OK");
        return CARD_OK; 
}
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
    printf("\nPlease Enter card's Primary Account Number: ");
    fgets(&cardData->primaryAccountNumber, sizeof(cardData->primaryAccountNumber), stdin);

    printf("Length of card's Primary Account Number = %zu \n", strlen((*cardData).primaryAccountNumber) - 1);

    if (strlen(cardData->primaryAccountNumber) > 20 || strlen(cardData->primaryAccountNumber) < 17) // Every string in C ends with '\0'.
    {
        printf("WRONG_PAN\n");
        return WRONG_PAN;
    }
    else
    {
        printf("CARD_OK\n");
        return CARD_OK;
    }
}
