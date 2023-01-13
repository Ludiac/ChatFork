#pragma once
#include <sstream>
#include <fstream>
#include <conio.h>
#include "Chat.h"
#include "Users.h"
#include "Message.h"
#include "TrieNode.h"

User input();
bool signUp();
User signIn();
void messageMenu(bool, bool, std::string const&, std::string const&, TrieNode*); // part of UI logic

void mainMenu(TrieNode*);