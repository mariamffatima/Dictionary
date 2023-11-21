#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
#pragma warning(disable : 4996)
const int MAX_WORDS = 1000;
const int MAX_WORD_LENGTH = 50;
const int MAX_MEANING_LENGTH = 200;

class Dictionary
{
private:
    char words[MAX_WORDS][MAX_WORD_LENGTH];
    char meanings[MAX_WORDS][MAX_MEANING_LENGTH];
    int wordCount;

public:
    Dictionary() : wordCount(0) {}

    void loadDictionary(const char* filename)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cout << "Error opening file: " << filename << endl;
            return;
        }

        while (file >> words[wordCount] >> meanings[wordCount])
        {
            wordCount++;
        }

        cout << "Dictionary loaded successfully." << endl;
    }

    void addWord(const char* word, const char* meaning)
    {
        if (findWordIndex(word) != -1)
        {
            cout << "Word already exists in the dictionary." << endl;
        }
        else
        {
            if (wordCount < MAX_WORDS)
            {
                strcpy(words[wordCount], word);
                strcpy(meanings[wordCount], meaning);
                wordCount++;
                cout << "Word added successfully." << endl;
            }
            else
            {
                cout << "Dictionary is full. Cannot add more words." << endl;
            }
        }
    }

    void searchWord(const char* word)
    {
        int index = findWordIndex(word);
        if (index != -1)
        {
            cout << "Meaning: " << meanings[index] << endl;
        }
        else
        {
            cout << "Word not found in the dictionary." << endl;
        }
    }

    void deleteWord(const char* word)
    {
        int index = findWordIndex(word);
        if (index != -1)
        {
            cout << "Do you want to delete the word '" << word << "'? (Yes/No): ";
            char response[5];
            cin >> response;
            if (strcmp(response, "Yes") == 0 || strcmp(response, "yes") == 0)
            {
                removeWord(index);
                cout << "Word deleted successfully." << endl;
            }
            else
            {
                cout << "Word deletion canceled." << endl;
            }
        }
        else
        {
            cout << "Word not found in the dictionary." << endl;
        }
    }

    void updateWord(const char* word, const char* newMeaning)
    {
        int index = findWordIndex(word);
        if (index != -1)
        {
            cout << "Do you want to update the meaning of '" << word << "'? (Yes/No): ";
            char response[5];
            cin >> response;
            if (strcmp(response, "Yes") == 0 || strcmp(response, "yes") == 0)
            {
                strcpy(meanings[index], newMeaning);
                cout << "Meaning updated successfully." << endl;
            }
            else
            {
                cout << "Meaning update canceled." << endl;
            }
        }
        else
        {
            cout << "Word not found in the dictionary." << endl;
        }
    }

    void wordSuggestion(const char* prefix)
    {
        cout << "Word suggestions starting with '" << prefix << "':" << endl;
        int count = 0;
        for (int i = 0; i < wordCount; ++i)
        {
            if (strncmp(words[i], prefix, strlen(prefix)) == 0)
            {
                cout << words[i] << endl;
                if (++count == 10)
                {
                    break; // Limit suggestions to 10
                }
            }
        }

        if (count == 0)
        {
            cout << "No suggestions found." << endl;
        }
    }

private:
    int findWordIndex(const char* word)
    {
        for (int i = 0; i < wordCount; ++i)
        {
            if (strcmp(words[i], word) == 0)
            {
                return i;
            }
        }
        return -1;
    }

    void removeWord(int index)
    {
        if (index >= 0 && index < wordCount)
        {
            for (int i = index; i < wordCount - 1; ++i)
            {
                strcpy(words[i], words[i + 1]);
                strcpy(meanings[i], meanings[i + 1]);
            }
            wordCount--;
        }
    }
};

int main()
{
    Dictionary dictionary;
    dictionary.loadDictionary("Dictionary.txt");

    int choice;
    char word[MAX_WORD_LENGTH], meaning[MAX_MEANING_LENGTH];

    do
    {
        cout << "\nMENU:" << endl;
        cout << "1. Add Word" << endl;
        cout << "2. Search Word" << endl;
        cout << "3. Delete Word" << endl;
        cout << "4. Update Word" << endl;
        cout << "5. Word Suggestion" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter word and meaning to add (separated by space): ";
            cin >> word >> meaning;
            dictionary.addWord(word, meaning);
            break;

        case 2:
            cout << "Enter word to search: ";
            cin >> word;
            dictionary.searchWord(word);
            break;

        case 3:
            cout << "Enter word to delete: ";
            cin >> word;
            dictionary.deleteWord(word);
            break;

        case 4:
            cout << "Enter word to update: ";
            cin >> word;
            cout << "Enter new meaning: ";
            cin.ignore(); // Ignore any remaining newline characters
            cin.getline(meaning, MAX_MEANING_LENGTH);
            dictionary.updateWord(word, meaning);
            break;

        case 5:
            cout << "Enter prefix for word suggestion: ";
            cin >> word;
            dictionary.wordSuggestion(word);
            break;

        case 6:
            cout << "Exiting program." << endl;
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }

    } while (choice != 6);

    return 0;
}
#pragma warning(disable : 4996)