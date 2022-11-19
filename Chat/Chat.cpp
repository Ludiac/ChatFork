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
        std::ofstream out ("messages.mdf", std::ios::app);
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

    Chat(int _id1, int _id2) // for private chat
    {
        std::ifstream readFromDB;
        readFromDB.open("messages.mdf", std::ios::in);
        std::string array[5];
        int i = 0; // iterator for while
        while (!readFromDB.eof()) 
        {
            i = 0; // iterator for while
            std::string msg;
            std::getline(readFromDB, msg);

            std::istringstream ss(msg);
            std::string token;

            while (std::getline(ss, token, '$')) 
            {
                array[i] = token;
                ++i;
            }
            
            if ((std::stoi(array[2]) == _id1 && std::stoi(array[3]) == _id2) || (std::stoi(array[2]) == _id2 && std::stoi(array[3]) == _id1))
                buffer.push_back("From: " + array[2] + " To: " + array[3] + " Message: " + array[4]);
        }
    }

    Chat(std::string _chatName) //for public chat
    {
        std::ifstream readFromDB;
        readFromDB.open("messages.mdf", std::ios::in);
        std::string array[5];
        int i = 0; // iterator for while
        while (!readFromDB.eof())
        {
            i = 0; 
            std::string msg;
            std::getline(readFromDB, msg);

            std::istringstream ss(msg);
            std::string token;

            while (std::getline(ss, token, '$'))
            {
                    array[i] = token;
                    ++i;
            }
           if (array[0] == _chatName)
            buffer.push_back("Public chat: " + array[0] + " From: " + array[2] + " Message: " + array[4]);
        }
    }

    std::list<std::string> getChat() { return buffer; }

    void print()
    {

        for (auto const& i : buffer) {
            std::cout << i << std::endl;
        }
    }
};

int main()
{
    //std::cout << "Hello World!\n";
    Message test = { 1, 2, "hello world!"};
    test.sendMessage();
    Chat ch = {1, 2};
    ch.print();
    Chat common = { "00-general" };
    common.print();
    Message testGroup = { true, "00-general", 3, "public chat TEST message" };
    testGroup.sendMessage();

}
