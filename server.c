#include <stdio.h>
#include "server.h"
#include <string.h>
float nbalance;
char stop_index;
ST_transaction transactions[255] = {0};

ST_accountsDB_t database[255] = { {4000,"1234567891234567"},{3231,"9876543217654321"},{100,"112233445566667788"} };
EN_transState_t recieveTransactionData(ST_transaction_t* transData) {
	if (isValidAccount(&transData->cardHolderData) != OK) {
		transData->transState = DECLINED_STOLEN_CARD;
		saveTransaction(transData);
		return DECLINED_STOLEN_CARD;
	}

	if (isAmountAvailable(&transData->terminalData) != OK) {
		transData->transState = DECLINED_INSUFFECIENT_FUND;
		saveTransaction(transData);
		return DECLINED_INSUFFECIENT_FUND;
	}

	updateBalance(temp_current_card_index, transData->terminalData.transAmount);

	transData->transState = APPROVED;

	if (saveTransaction(transData) != OK) {
		return INTERNAL_SERVER_ERROR;
	}


	return APPROVED;

}
EN_serverError_t isValidAccount(ST_cardData_t* cardData) {
	//database[i].balance or .primaryAccountNumber for selsect element in array
	//use built in function to compare database with the user input 
	for (int i = 0; i < 250; i++) {
		if (strcmp(database[i].primaryAccountNumber, cardData->primaryAccountNumber) == 0) {
			stop_index = i;
			nbalance = database[i].balance;
			return ok;
		}
	
	
	}
	return DECLINED_STOLEN_CARD;
}
EN_serverError_t isAmountAvailable(ST_trminalData_t* termData) {

	if (nbalance > 0 && nbalance >= termData->transAmount) {
		return OK;
	}
	return LOW_BALANCE;
}
}

EN_serverError_t saveTransaction(ST_transaction_t* transData) {

	for (int i = 0; i < 255; i++) {
		if (transactions[i].transactionSequenceNumber == 0 && transactions[i].cardHolderData.primaryAccountNumber[0] == '\0') {

			transactions[i] = *transData;
			transData->transactionSequenceNumber = i;

			return OK;
		}
	}

	return SAVING_FAILED;

}

