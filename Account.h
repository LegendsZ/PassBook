#pragma once
#include <string>

class Account {
public:
	std::string domain;
	std::string username;
	std::string password;
	std::string notes;

	Account(std::string domainG,std::string usernameG, std::string passwordG,std::string notesG):domain(domainG),username(usernameG),password(passwordG),notes(notesG){}

	bool includes(std::string toLookFor) {
		if (domain.find(toLookFor) != std::string::npos || username.find(toLookFor) != std::string::npos || password.find(toLookFor) != std::string::npos || notes.find(toLookFor) != std::string::npos) {
			return true;
		}
		return false;
	}
};