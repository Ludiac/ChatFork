#include "Users.h"
#include "User.h"
#include <fstream>
#include <sstream>

Users::Users()
{
	std::ifstream readFromDB;
	readFromDB.open("users.mdf", std::ios::in);
	if (!readFromDB.is_open())
		std::ofstream outfile("users.mdf"); //create file in case it's not there
	else
	{
		while (!readFromDB.eof())
		{
			std::string userRecord;

			std::getline(readFromDB, userRecord);
			if (!userRecord.empty())
			{
				std::istringstream ss(userRecord);
				std::string token;
				int i = 0; // iterator for while
				std::string array[3];
				while (std::getline(ss, token, '\t'))
				{
					array[i] = token;
					++i;
				}
				User tempUser = { array[0], array[1], array[2] };
				users.push_back(tempUser);
			}
		}
	}
}

bool Users::uniqueLogin(std::string const& login) // check login for uniqueness
{
	for (auto& i : users)
	{
		if (i.getLogin() == login)
			return false;
	}

	return true;
}

void Users::printUsers() // just prints all user names and logins
{
	for (auto i : users)
		std::cout << "User: " << i.getLogin() << ", Name: " << i.getUserName() << '\n';
}

bool Users::loginAndPasswordMatch(User const& _user) // check is login matching the password
{
	for (auto& i : users)
	{
		if (i.getLogin() == _user.getLogin() && i.getPassword() == _user.getPassword())
			return true;
	}

	return false;
}