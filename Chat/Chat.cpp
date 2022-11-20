#include <iostream>
#include <fstream>
#include <list>
#include <sstream>

struct Message
{
private:
	bool groupChat;
	int idSender, idRecipient;
	std::string message, chatName;

public:
	Message(int _idSender, int _idRecipient, std::string _message) : idSender(_idSender), idRecipient(_idRecipient), message(_message)
	{
		groupChat = false;
		chatName = "-";
	}

	Message(bool _groupChat, std::string _chatName, int _idSender, std::string _message) : groupChat(_groupChat), chatName(_chatName), idSender(_idSender), message(_message)
	{
		idRecipient = 0; //need to reserve 0 for public chat
	}

	void sendMessage() // push message to data base
	{
		std::ofstream out("messages.mdf", std::ios::app);
		if (out.is_open())
		{
			out << chatName << "$" << groupChat << "$" << idSender << "$" << idRecipient << "$" << message << std::endl;
		}
		out.close();
	}
};

struct Chat
{
	std::list<std::string> buffer;

	Chat(int _id1, int _id2) // private chat constructor
	{
		std::ifstream readFromDB;
		readFromDB.open("messages.mdf", std::ios::in);

		while (!readFromDB.eof())
		{
			std::string array[5];
			std::string msg;

			std::getline(readFromDB, msg);
			if (!msg.empty())
			{
				std::istringstream ss(msg);
				std::string token;
				int i = 0; // iterator for while
				while (std::getline(ss, token, '$'))
				{
					array[i] = token;
					++i;
				}
				// showing messages linked with current users
				if ((std::stoi(array[2]) == _id1 && std::stoi(array[3]) == _id2) || (std::stoi(array[2]) == _id2 && std::stoi(array[3]) == _id1))
					buffer.push_back("From: " + array[2] + " To: " + array[3] + " Message: " + array[4]);
			}
		}
	}

	Chat(std::string _chatName) // public chat constructor
	{
		std::ifstream readFromDB;
		readFromDB.open("messages.mdf", std::ios::in);
		std::string array[5];

		while (!readFromDB.eof())
		{
			std::string msg;
			std::getline(readFromDB, msg);

			if (!msg.empty())
			{
				std::istringstream ss(msg);
				std::string token;
				int i = 0; // iterator for while
				while (std::getline(ss, token, '$'))
				{
					array[i] = token;
					++i;
				}

				if (array[0] == _chatName) // showing messages linked with current chat
					buffer.push_back("Public chat: " + array[0] + " From: " + array[2] + " Message: " + array[4]);
			}
		}
	}

	// std::list<std::string> getChat() { return buffer; } not used

	void print()
	{
		for (auto const& i : buffer) {
			std::cout << i << std::endl;
		}
	}
};

int main()
{
	Message test = { 56, 65, "hello world!" };
	test.sendMessage();
	Chat ch = { 56, 65 };
	ch.print();

	Message testGroup = { true, "00-general", 3, "public chat \"TEST message" };
	testGroup.sendMessage();
	Chat common = { "00-general" };
	common.print();
}
