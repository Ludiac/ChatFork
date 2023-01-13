#include "Message.h"

Message::Message(std::string const& _sender, std::string const& _recipient, std::string const& _message) : sender(_sender), recipient(_recipient), message(_message) {}

void Message::sendMessage() // push message to data base
{
	std::ofstream out("messages.mdf", std::ios::app);
	if (out.is_open())
	{
		out << sender << "\t" << recipient << "\t" << message << std::endl;
	}
	out.close();
}