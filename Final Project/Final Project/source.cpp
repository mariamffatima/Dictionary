#include "header.h"
#include<iostream>
void DictTrie::insert(const string& word)
{
    TrieNode* node = root;
    for (char c : word)
    {
        if (isalpha(c)) 
        {
            int index = tolower(c) - 'a';
            if (!node->children[index])
            {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        }
    }
    node->EndOfWord = true;
}
DictTrie::DictTrie()
{
    root = new TrieNode();
}
DictTrie::~DictTrie()
{
    delete root;
}
void DictHash::saveToFile()
{
    ofstream file("Dictionary.txt");
    if (!file.is_open())
    {
        cout << "Error!! Dictionary not saved " << endl;
        
        return;
    }

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        WordNode* current = table[i];
        while (current != nullptr)
        {
            file << current->word << " " << current->meaning << "\n";
            current = current->next;
        }
    }

//     file.close();
//     cout << "Dictionary saved successfully!" << endl;
    
}
void DictHash::addWord(const string& word, const string& meaning)
{

    string newWord;
    for (char c : word)
    {
        if (isalpha(c))
        {
            newWord += tolower(c);
        }
    }

    int key = hashFunction(newWord);
    WordNode* current = table[key];

    while (current != nullptr)
    {

        if (current->word == newWord)
        {
            cout << "Word already exists in the dictionary." << endl;
            cout << "Do you want to update meaning ? " << endl;
            cout << "Enter 'y' for yes and 'n' for no : " << endl;
            char c;
            cin >> c;
            cin.ignore();

            if (c == 'y')
            {
                string newMeaning;
                cout << "Enter new meaning:" << endl;
                getline(cin, newMeaning);
                current->meaning = newMeaning;
                cout << "Word updated successfully!" << endl;

                ofstream file("Dictionary.txt");
                for (int i = 0; i < TABLE_SIZE; i++)
                {
                    WordNode* node = table[i];
                    while (node != nullptr)
                    {
                        file << node->word << " " << node->meaning << endl;
                        node = node->next;
                    }
                }
                //file.close();
            }
            return;
        }
        current = current->next;
    }

    insertWord(newWord, meaning);
    cout << "Word added successfully!" << endl;
    /* ofstream file("Dictionary.txt", ios::app);
     file << newWord << " " << meaning << endl;
     file.close();*/
    //saveToFile();
}

DictHash::~DictHash()
{
    saveToFile();
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        WordNode* current = table[i];
        while (current != nullptr)
        {
            WordNode* next = current->next;
            delete current;
            current = next;
        }
    }
}
void DictHash::deleteWord(const string& word)
{
    int key = hashFunction(word);
    WordNode* current = table[key];
    WordNode* prev = nullptr;

    while (current != nullptr && current->word != word)
    {
        prev = current;
        current = current->next;
    }

    if (current == nullptr)
    {
        cout << "Word not found for deletion: " << word << endl;
        return;
    }

    if (prev == nullptr)
    {
        table[key] = current->next;
    }
    else
    {
        prev->next = current->next;
    }

    cout << "Deleted: Word = " << current->word << ", Meaning = " << current->meaning << " at hash index " << key << endl;
    delete current;
    saveToFile();
}
void DictHash::displayMeaning(const string& word) // gets the meaning of the word
{
    int key = hashFunction(word);
    WordNode* current = table[key];

    while (current != nullptr)
    {
        if (current->word == word)
        {
            cout << "Meaning for '" << word << "': " << current->meaning << endl;
            return;
        }
        current = current->next;
    }

    cout << "Meaning not found for '" << word << "'" << endl;
}

void DictHash::insertWord(const string& word, const string& meaning)
{
    int key = hashFunction(word);
    WordNode* newNode = new WordNode(word, meaning);
    newNode->next = table[key];
    table[key] = newNode;
}
int DictHash::hashFunction(const string& word)
{
    int hash = 0;
    for (char c : word)
    {
        hash = (hash * 31 + tolower(c)) % TABLE_SIZE;
    }
    return hash;
}

DictHash::DictHash()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        table[i] = nullptr;
    }
}
void DictTrie::getSuggestions(const string& prefix)
{
    TrieNode* node = root;
    string currentWord = "";
    int curr = 0;

    for (char c : prefix) // finds words with the prefix
    {
        int index = tolower(c) - 'a';
        if (!node->children[index])
        {
            return; // not found
        }
        node = node->children[index];
        currentWord += c;
    }
    getSuggestionsUtil(node, prefix, currentWord, curr);
}
void DictTrie::getSuggestionsUtil(TrieNode* node, const string& prefix, string currentWord, int& curr)
{

    if (node->EndOfWord)
    {
        cout << "Suggestion " << curr + 1 << ": " << currentWord << endl;
        curr++;
    }

    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        if (node->children[i])
        {
            getSuggestionsUtil(node->children[i], prefix, currentWord + char('a' + i), curr);
            if (curr >= 10) // termination condition for 10 suggestions
            {
                return;
            }
        }
    }
}

bool DictTrie::search(const string& word)
{
    TrieNode* node = root;
    for (char c : word)
    {
        int index = tolower(c) - 'a';
        if (!node->children[index])
        {
            return false; // word not found
        }
        node = node->children[index];
    }
    return node->EndOfWord;
}
//void DictHash::searchWord(const string& word)
//{
//	int key = hashFunction(word);
//    HashData()
//    while (current != nullptr)
//    {
//
//    }
//	newNode->next = table[key];
//	table[key] = newNode;
//}
TrieNode::TrieNode()
{
    EndOfWord = false;
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        children[i] = nullptr;
    }
}
TrieNode::~TrieNode()
{
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        delete children[i];
    }
}
WordNode::WordNode(const string& w, const string& m)
{
    word = w;
    meaning = m;
    next = nullptr;
}
