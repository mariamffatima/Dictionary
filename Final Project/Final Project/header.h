
#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

const int TABLE_SIZE = 60689;
const int ALPHABET_SIZE = 26;

class WordNode
{
public:
	string word;
	string meaning;
	WordNode* next;

	WordNode(const string& w, const string& m);
};
class TrieNode
{
public:
	TrieNode* children[ALPHABET_SIZE];
	bool EndOfWord;

	TrieNode();
	~TrieNode();
};

class DictTrie
{
public:
	TrieNode* root;

	DictTrie();
	~DictTrie();

	void insert(const string& word);

	bool search(const string& word);
	void getSuggestionsUtil(TrieNode* node, const string& prefix, string currentWord, int& curr);

	void getSuggestions(const string& prefix);
};

class DictHash
{

	WordNode* table[TABLE_SIZE];

public:
	DictHash();

	int hashFunction(const string& word);
	void insertWord(const string& word, const string& meaning);
	void displayMeaning(const string& word); // gets the meaning of the word
	void searchWord(const string& word);
	void deleteWord(const string& word);
	~DictHash();
	void addWord(const string& word, const string& meaning);
	void saveToFile();
};


#endif
