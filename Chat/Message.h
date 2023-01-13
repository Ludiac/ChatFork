#pragma once
#include <iostream>
#include <fstream>

struct Message
{
private:
	std::string sender, recipient, message;

public:
	Message(std::string const&, std::string const&, std::string const&);

	void sendMessage();
};