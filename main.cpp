#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include "Hash.h"
using namespace std;



int main()
{
	ifstream myfile;
	HashClass* list;
	myfile.open("Dictionary.txt");
	list = new HashClass;
	list->ReadFile(myfile);
	char option = ' ';
	while (option != 'T')
	{
		list->DisplayMenu();
		cin >> option;			
		clearFunction();
		option = toupper(option);
		list->menuFunction(option, list);
	}
	myfile.close();
	return 0;
}

void HashClass::menuFunction(const char option, HashClass* list)
{
	switch (option)
	{
	case 'E':
		cout << endl;
		cout << "Please enter the scrambled word now\n";
		list->unscramble();
		clearFunction();
		break;
	case 'D':
		list->Print();
		clearFunction();
		break;
	case 'T':
		cout << "Goodbye!!";
		break;
	default:
		cout << "Unrecognized option; please try again.";
		clearFunction();
		break;
	}
}

void HashClass::DisplayMenu()
{
	cout << setw(25) << setfill('*') << endl;
	cout << "WELCOME TO THE UNSCRAMBLER PROGRAM\n";
	cout << endl;
	cout << "The following options are available\n";
	cout << endl;
	cout << "(E)nter scrambled word\n";
	cout << "(D)isplay the current dictionary\n";
	cout << "(T)erminate program\n";
	cout << setw(25) << setfill('*') << endl;
}

HashClass::HashClass()
{
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		HashTable[i] = new NODE;
		HashTable[i]->key = 0;
		HashTable[i]->word = "  ";
		HashTable[i]->next = NULL;
	}
}

void HashClass::ReadFile(ifstream& myfile)
{

	string word;
	int result = 0;
	//int collision = 0;

	for (int i = 0; i < TABLE_SIZE; i++)
	{
		while (!myfile.eof())
		{
			ptr = new NODE;
			getline(myfile, ptr->word);
			result = HashFunc(ptr->word);
			ptr->key = result;				
			if (HashTable[result]->word == "  ")
			{
				HashTable[result]->key = ptr->key;
				HashTable[result]->word = ptr->word;
				HashTable[result]->next = NULL;
			}
			else
			{
				ptr->next = HashTable[result];
				HashTable[result] = ptr;
				//collision++;
			}
		}
	}
	//cout << "There were " << collision << " collisions in the dictionary\n";     To keep track of the number of collisions
}
int HashClass::HashFunc(string word)
{
	int seed = 3;
	int hashNum = 0;
	int wordVal = 0;

	for (unsigned int i = 0; i < word.length(); i++)
	{
		wordVal = word[i] + wordVal;
	}
	hashNum = (((wordVal * seed) % 919393) % TABLE_SIZE);
	return hashNum;
}
void HashClass::unscramble()
{
	string word;
	string sortedWord;
	string scrambledSortedWord;
	int i = 0;
	int result = 0;
	NODE *temp;
	NODE *current;
	temp = new NODE;
	bool wordOut = false;
	getline(cin, temp->word);
	scrambledSortedWord = temp->word;
	sort(scrambledSortedWord.begin(), scrambledSortedWord.end());
	cout << endl;
	result = HashFunc(temp->word);
	temp->key = result;
	
	while (i < TABLE_SIZE && wordOut == false)
	{
		current = HashTable[i];						//Set pointer to point at the index of the Hash table
		if (temp->key == HashTable[i]->key)
		{
			while (current != NULL)					//Loop to cycle through all nodes at location in Hash table
			{
					sortedWord = current->word;
					sort(sortedWord.begin(), sortedWord.end());
					if (scrambledSortedWord == sortedWord)
					{
						cout << "Word Found!" << endl;
						cout << "Your unscrambled word is: ";
						cout << current->word << endl;
						wordOut = true;
					}
					current = current->next;
			}
			if (current == NULL) 
			{
				break;
			}
		}
		else
		{
			i++;
		}	
	}	
	if (wordOut == false || i == TABLE_SIZE -1)
	{
		cout << "Not Found" << endl;
	}
	cout << "\nPress enter to continue\n";
}
void HashClass::Print()
{
	string word[TABLE_SIZE];
	int i = 0;
	ifstream myfile;
	myfile.open("Dictionary.txt");
	
	while (i < TABLE_SIZE)
	{
		getline(myfile, word[i]);
		i++;
	}
	cout << left;
	for (i = 0; i < TABLE_SIZE/3; i++)
	{
		cout << setw(30) << word[i] << setw(25) << setfill(' ') << word[i + 13746] << setw(25) << setfill(' ') << word[i + 27492];   // Set the area to display words with whitespaces in between
	}	
	myfile.close();
}
void clearFunction()
{
	cin.ignore(100, '\n');
	cin.clear();
}
