#pragma once

const int ALPHABET_SIZE = 26;

// Структура узела дерева 
struct TrieNode
{
	struct TrieNode* children[ALPHABET_SIZE];
	// isEndOfWord - true, если ключ является концом слова
	bool isEndOfWord;
	int freq;
};

TrieNode* getNewNode(void);
void insert(TrieNode*, std::string);
bool search(TrieNode*, std::string);
bool isEmpty(TrieNode*);
TrieNode* remove(TrieNode*, std::string, int depth = 0);
void findMinPrefixes(TrieNode*, char[], int, std::string&);
void printAutoSuggestions(TrieNode*, const std::string&, std::string*);
void autocomplete(TrieNode* root, std::string, const std::string&, std::string*);