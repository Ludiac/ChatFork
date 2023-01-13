#pragma once
#include <iostream>
#include <list>
#include <fstream>
#include <sstream>

struct Chat
{
private:
	std::list<std::string> buffer;

public:
	Chat(std::string const&, std::string const&); // universal chat constructor

	void printChat(); // just prints all messages in Chat object
};