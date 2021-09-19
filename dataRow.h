#pragma once
#include "Account.h"
#include <vector>

class DataRowCustom {
public:
	int id;
	char* username;
	char* password;
	std::string accounts;

	std::vector<Account> accs;

	DataRowCustom(): id(-1), username(nullptr), password(nullptr), accounts(nullptr) {}

	DataRowCustom(int idG, char* usernameG, char* passwordG, std::string accountsG): id(idG), username(usernameG), password(passwordG), accounts(accountsG){
		char* cstr = new char[accounts.length() + 1];
		strcpy(cstr, accounts.c_str());
		
		char* token = strtok(cstr, ":");
		while (token != NULL) {
			std::vector<std::string> accInfo;
			char* tempB = strtok(token, ",");
			while (tempB != NULL) {
				accInfo.push_back(std::string(tempB));
				tempB = strtok(NULL, ",");
			}
			accs.push_back(Account(accInfo.at(0), accInfo.at(1), accInfo.at(2), accInfo.at(3)));
			token = strtok(NULL, ":");
		}
	}

	int includes(std::string toLookFor) {
		for (int i = 0; i < accs.size(); i++) {
			if (accs.at(i).includes(toLookFor)) {
				return i;
			}
		}
		return -1;
	}
};