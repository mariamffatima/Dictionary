// Main.cpp
#include<iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "header.h"

using namespace std;

void loadDictionary(DictHash& h, DictTrie& trie, string filename)
{
	cout << "Dictionary loading.....\n";
	ifstream file(filename);
	if (!file.is_open())
	{
		cout << "Error opening file: " << filename << endl;
		return;
	}

	string line, word, meaning;
	while (getline(file, line))
	{
		istringstream iss(line);
		if (iss >> word >> meaning)
		{
			h.insertWord(word, meaning);
			trie.insert(word);
		}
	}

	//file.close();
	cout << "Dictionary loaded successfully!" << endl;
	 
	
}

void menuFunction(DictTrie& trie, DictHash& h)
{
	cout << "Enter 1 to Insert a word and meaning" << endl;
	cout << "Enter 2 to Delete a word " << endl;
	cout << "Enter 3 to Search a word" << endl;
	cout << "Enter 4 to get suggestions" << endl;
	cout << "Enter 0 to Exit" << endl;

	char choice;
	cin >> choice;
	cin.ignore();
	
	switch (choice)
	{
	case '1':
	{
		string word, meaning;
		cout << "Enter word : ";
		getline(cin, word);
		cout << "Enter meaning : ";
		getline(cin, meaning);
		h.addWord(word, meaning);
		
		
		break;
	}

	case '2':
	{
		string word;
		cout << "Enter word you want to delete : ";
		getline(cin, word);
		h.deleteWord(word);
		 
		
		break;
	}

	case '3':
	{
		string word;
		cout << "Enter Text you want to search: ";
		getline(cin, word);
		if (trie.search(word))
		{
			cout << word << " found !" << endl;
			h.displayMeaning(word);
		}
		else
		{
			cout << word << " not found !" << endl;
		}
		 
		
		break;
	}

	case '4':
	{
		string prefix;

		cout << "Enter the prefix for suggestions: ";
		getline(cin, prefix);
		
		int count = 0;
		string newPrefix;
		char* ch = new char[4];
		for (char c : prefix)
		{
			if (count == 0)
			{
				continue;
			}
			else
				ch[count] = c;
			count++;
		}
		newPrefix = ch;
		trie.getSuggestions(newPrefix);
		break;
	}

	case '0':
		//h.saveToFile();
		cout << "Program Ending..." << endl;
		 
		return;

	default:
		cout << "Invalid Input" << endl;
		 
		
		break;
	}

	menuFunction(trie, h);
}

int main()
{
	DictTrie trie;
	DictHash h;
	loadDictionary(h, trie, "Dictionary.txt");
	menuFunction(trie, h);
	return 0;
}
