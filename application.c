#include "application.h"
#include"card/card.h"
#include"terminal/terminal.h"
#include"server/server.h"
#include <stdio.h>

void appStart(void) {

    ST_cardData_t visacard;
    EN_cardError_t  cardError = getCardData(&visacard);
    if (cardError != OK) {
        return;
    }
    ST_terminalData_t visa_data;
    EN_terminalError_t terminalError = runTerminal(&visa_data, &visacard);
    if (terminalError != OK) {
        return;
    }
    ST_transaction_t newTransaction;
    newTransaction.cardHolderData = visacard;
    newTransaction.terminalData = visa_data;
    runServer(&newTransaction);

}

EN_cardError_t getCardData(ST_cardData_t* cardData) {
    printf("data of holder\n");
    EN_cardError_t card_mistake;
    card_mistake = getCardHolderName(cardData);
    if (card_mistake != OK) {
        printf("\n name is wrong");
        return card_mistake;
    }
    card_mistake = getCardExpiryDate(cardData);
    if (card_mistake != OK)
    {
        printf("\ndata is wrong");
        return card_mistake;
    }
    card_mistake = getCardPAN(cardData)
    if (card_mistake != OK)
    {
        printf("\npan is wrong");
        return card_mistake;
    }
    return OK;
}
EN_terminalError_t Terminal_note(ST_terminalData_t* termData, ST_cardData_t* cardData) {
    printf("\nTERMINAL information\n");
    EN_terminalError_t terminal_mistake;
    getTransactionDate(termData);
    setMaxAmount(termData);
    terminal_mistake = isCardExpired(*cardData, *termData);
    if (terminal_mistake != OK)
    {
        printf("\nCard is Expired");
        return terminal_mistake;
    }
    terminal_mistake = isValidCardPAN(cardData);
    if (terminal_mistake != OK)
    {
        printf("\nCard is not Valid");
        return terminal_mistake;
    }
    terminal_mistake = getTransactionAmount(termData);
    if (terminal_mistake != OK)
    {
        printf("\nInvalid Amount");
        return terminal_mistake;
    }
    terminal_mistake = isBelowMaxAmount(termData);
    if (terminal_mistake != OK){
        printf("\nExceeded the Maximum");
        return terminal_mistake;
    }
    return OK;
}
EN_transState_t Servernote(ST_transaction_t* transData) {
    printf("SERVER is fine \n");
    EN_transState_t type_of_server_error = recieveTransactionData(transData);
    switch (type_of_server_error) {
    case DECLINED_INSUFFECIENT_FUND:
        printf("INSUFFECIENT FUND");
        break;
    case DECLINED_STOLEN_CARD:
        printf("it is decclined cause Stolen Card");
        break;
    case INTERNAL_SERVER_ERROR:
        printf("INTERNAL SERVER ERROR cant be saved ");
        break;
    case APPROVED:
        printf("process done");
        break;
    default:
        printf(" error happened");
    }

}