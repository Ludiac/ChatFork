#include "UI.h"

User input()
{
	std::string login, password;
	User tempUser;

	std::cout << "Enter login: ";
	try // just because we can and it is in task
	{
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(std::cin, login, '\n');
		if (login == "_all")
			throw (login);
	}

	catch (std::string const& login)
	{
		std::cout << "Exception! Please don't use " + login + " as login, it is hardcoded!\n";
	}

	std::cout << '\n';
	tempUser.setLogin(login);

	if (!tempUser.loginValid()) // check login is valid or not
	{
		std::cout << "Invalid Login.\n";
		return User();	// return empty User in order to check it on next steps
	}

	std::cout << "Enter password: ";
	std::getline(std::cin, password, '\n'); // here and below getline is used to get string with spaces
	std::cout << '\n';
	tempUser.setPassword(password);

	if (!tempUser.passwordValid(password)) // check password is valid or not
	{
		std::cout << "Invalid password.\n";
		return User();	// return empty User in order to check it on next steps
	}
	return tempUser;
}

bool signUp()
{
	User user = input();
	Users g_loadedUsers = Users();   // read database of users and put to Users object

	if (!g_loadedUsers.uniqueLogin(user.getLogin()) || user.getLogin().empty()) // if login is empty or user with inputed login is already in database, return false
	{
		std::cout << "Invalid Login.\n";
		return false;
	}

	std::string name;
	std::cout << "Enter your name: ";
	std::getline(std::cin, name, '\n');
	user.setUserName(name);
	std::cout << '\n';

	std::cout << "Check your entries.\nYour login: " << user.getLogin()
		<< "\nYour password: is hidden" // << user.getPassword()
		<< "\nYour name: " << user.getUserName()
		<< "\nare those correct? Enter 'y' to proceed, any other button to abort: ";
	std::string input;
	std::cin >> input;
	if (input != "y")
	{
		std::cout << "Operation cancelled\n";
		return false;
	}

	std::ofstream out("users.mdf", std::ios::app); // add user record to data base
	if (out.is_open())
	{
		out << user.getLogin() + "\t" + user.getPassword() + "\t" + user.getUserName() << std::endl;  //add new user to file
		std::cout << "Success! You are registered.\n";
		return true;
	}

	else
	{
		std::cout << "Something went wrong.\n";
		return false;
	}
}

User signIn() {
	User user = input();
	Users g_loadedUsers = Users();   // read database of users and put to Users object

	if (g_loadedUsers.uniqueLogin(user.getLogin()))
	{
		std::cout << "Such user doesn't exist.\n";
		user.setLogin("");
		return user;
	}

	if (!g_loadedUsers.loginAndPasswordMatch(user))
	{
		std::cout << "Invalid password.\n";
		user.setLogin("");
	}

	return user;
}

void messageMenu(bool openChat, bool openSession, std::string const& current_user, std::string const& inputRecipient, TrieNode* dictionary) // part of UI logic
{
	while (openChat && openSession) {
		std::cout << '\n' << "Last messages in chat: \n";
		Chat tempChat = { current_user, inputRecipient };
		tempChat.printChat();
		std::cout << '\n' << "Type your message here: \n";
		//std::string inputMessage;
		//std::cin.ignore();
		//std::getline(std::cin, inputMessage, '\n');

		std::string inputMessage;

		for (;;)
		{
			int keycode = _getch(); //gets the code

			if (keycode != 13 && keycode != 9)
			{
				std::cout << static_cast<char>(keycode);
				//std::cout << (keycode);
				inputMessage += keycode;
			}
			else if (keycode == 9)
			{
				std::string prefix;
				for (int i = inputMessage.size() - 1; i >= 0 && !std::isspace(inputMessage[i]); --i)
					//for (int i = inputMessage.size() - 1; i >= 0; --i)
				{
					//	if (std::isspace(inputMessage[i])) break;
					prefix += inputMessage[i];
				}
				std::reverse(prefix.begin(), prefix.end());

				printAutoSuggestions(dictionary, prefix, &inputMessage);
			}
			else break;
		}

		Message tempMessage = { current_user, inputRecipient, inputMessage };
		tempMessage.sendMessage();
		std::cout << '\n' << "Your message has been sent. 50 cents will be debited from your account.\n\nEnter '1' to type new message or 'q' to exit to chat menu\n";
		char messageMenuChoice;
		std::cin >> messageMenuChoice;
		switch (messageMenuChoice)
		{
		case 'q':
		{
			openChat = false;
			break;
		};
		default: continue;
		}
	}
}

void mainMenu(TrieNode* dictionary)
{
	Users g_loadedUsers = Users();

	char input;
	bool alive = true;
	bool openSession = false;
	bool openChat = false;
	std::cout << "\nWelcome to Stack, past generation messenger!\n\n";
	while (alive)
	{
		std::cout << "\nPress\n '1' for sign in\n '2' for sign up\n 'q' for exit\n";
		std::cin >> input;
		switch (input)
		{
		case '1': {
			User currentUser = signIn();
			if (currentUser.getLogin().empty()) break;
			openSession = true;


			while (openSession) {
				std::cout << "\nRegistered users:\n";
				g_loadedUsers.printUsers();
				std::cout << "\n";
				std::cout << "Hi, " << currentUser.getLogin() << ", please type recipient name or 'p' for public chat or 'q' to exit to main menu: ";
				std::string inputRecipient;
				std::cin >> inputRecipient;

				if (inputRecipient == "q")
				{
					inputRecipient.clear();
					openSession = false;
					break;
				}

				if (inputRecipient == "p")
				{
					messageMenu(true, openSession, currentUser.getLogin(), "_all", dictionary);
					continue;
				}

				else
					openChat = true;

				if (!g_loadedUsers.uniqueLogin(inputRecipient)) messageMenu(openChat, openSession, currentUser.getLogin(), inputRecipient, dictionary);
				else
				{
					openChat = false;
					std::cout << "User " << inputRecipient << " not found, please try again \n";
				}
			}
		}; break;
		case '2':
		{
			if (signUp())
			{
				g_loadedUsers = Users();
				break;
			}
		}; break;
		case 'q':
		{
			openSession = false;
			alive = false;
		}; break;
		default: std::cout << "Invalid input\n"; break;
		}
	}
}