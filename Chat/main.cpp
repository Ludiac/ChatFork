// #include "vld.h" memory leakage check
#include "User.h"
#include "Users.h"
#include "Message.h"
#include "Chat.h"
#include "UI.h"
#include "TrieNode.h"

int main()
{
	//autocomplete test functionality
	TrieNode* dictionary = getNewNode();
	insert(dictionary, "hello");
	insert(dictionary, "dear");
	insert(dictionary, "zebra");
	insert(dictionary, "skillfactory");
	//

	mainMenu(dictionary);
	delete dictionary;
}