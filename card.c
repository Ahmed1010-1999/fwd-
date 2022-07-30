#include "card.h"
#include<stdio.h>

EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
	char i;
	printf("enter your name");
	scanf("%s", cardData->cardHolderName);
	
	while (cardData->cardHolderName[i]!=0) {
		i = i + 1;
	}
	if (i < 20 || i>24) {
		return WRONG_NAME;
	}
	return OK;
}
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
	char i,b=0;

	printf(" enter the Expiry date in this format 'MM/YY' : ");
	scanf("%s", cardData->cardExpirationDate);
	//we can use while to count the length like the previos function but we also can use built in function strlen 
	i = strlen(cardData->cardExpirationDate);

	while (cardData->cardExpirationDate[2]==47 &&(cardData->cardExpirationDate[b] >= 47 && cardData->cardExpirationDate[b] <= 57)) {
		b = b + 1;
	}
	if (i !=5&&b!=5) {
		return WRONG_EXP_DATE;
	}

	return OK;



}
EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
	char b = 0;
	printf("enter the card PAN");
	scanf("%s", cardData->primaryAccountNumber);
	char i = strlen(cardData->primaryAccountNumber);
	//asci table
	while ((cardData->primaryAccountNumber[b] >= 48 && cardData->primaryAccountNumber[b] <= 57)&&(b>=16||b<=19)){
		b = b + 1;
	}
	if ((i > 19 || i < 16)&&b<16) {
		return WRONG_PAN;
	}

	return OK;
}

}
