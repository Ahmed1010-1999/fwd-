#include <stdio.h>
#include <time.h>
#include "terminal.h"
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	char year, month;
    time_t date;
    time(&date);
    struct tm* mytime = localtime(&date);
    year = (mytime->tm_year + 1900) % 100;//2022 22
    month = mytime->tm_mon + 1;//7
    //int to char by the formula below... 
    termData->transactionDate[0] = month / 10 + '0';
    termData->transactionDate[1] = month % 10 + '0';
    termData->transactionDate[2] = '/';
    termData->transactionDate[3] = year / 10 + '0';
    termData->transactionDate[4] = year % 10 + '0';
    return ok;
}
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData) {
    //string to int by the formula below '12/22'
    char expired_month = (cardData.cardExpirationDate[0] - '0') * 10 + (cardData.cardExpirationDate[1] - '0');//date in this shape pu/nk>>p*10+u=month the same for year
    char expired_year  = (cardData.cardExpirationDate[3] - '0') * 10 + (cardData.cardExpirationDate[4] - '0');
    char current_month = (termData.transactionDate[0] - '0') * 10 + (termData.transactionDate[1] - '0');
    char current_year  = (termData.transactionDate[3] - '0') * 10 + (termData.transactionDate[4] - '0');
    if ((current_year > expired_year)||(current_year == expired_year && current_month > expired_month))
    {
        return EXPIRED_CARD;
    }
    return OK;

}
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData) {
    char stepsum, i = 0, sum = 0;
    while (cardData->primaryAccountNumber[i] != '\0') {
        if (i % 2 == 0) {
            stepsum = ((cardData->primaryAccountNumber[i]) - '0')*2;
            if (stepsum > 9) {
                stepsum = stepsum / 10 + stepsum % 10; //sum of two digits 1+2
            }
        }
        else {
            stepsum = ((cardData->primaryAccountNumber[i]) - '0');
        }
        i = i + 1;
        sum = sum + stepsum;
    }
    if (sum % 10 != 0)
    {
        return INVALID_CARD;
    }

    return OK;

}
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
    printf("enter transaction amount u need");
    scanf("%d", &termData->transAmount);
    if (termData->transAmount <= 0){
        return INVALID_AMOUNT;
    }
    return OK;
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
    if (termData->maxTransAmount< termData->transAmount )
    {
        return EXCEED_MAX_AMOUNT;
    }
    return OK;
}
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData) {
    printf("enter the max amount :");
    scanf_s("%f", &termData->maxTransAmount);
    if (termData->maxTransAmount <= 0)
    {
        return INVALID_MAX_AMOUNT;
    }
    return OK;
}
