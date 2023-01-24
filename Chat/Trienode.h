#pragma once

const int ALPHABET_SIZE = 26;

struct TrieNode
{
	TrieNode* children[ALPHABET_SIZE];
	bool isEndOfWord;
	int freq;

	~TrieNode();
};

TrieNode* getNewNode(void);
void insert(TrieNode*, const std::string&);
void printAutoSuggestions(TrieNode*, const std::string&, std::string*);
void autocomplete(TrieNode* root, std::string, const std::string&, std::string*);