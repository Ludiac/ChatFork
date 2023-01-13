#pragma once
#include <vector>
#include "User.h"

struct Users   // read and store all user records
{
private:
	std::vector<User> users;

public:
	Users();

	bool uniqueLogin(std::string const&);
	void printUsers(); // just prints all user names and logins
	bool loginAndPasswordMatch(User const&); // check is login matching the password
};