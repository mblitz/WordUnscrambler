#ifndef Hash_h
#define Hash_h


#include <iostream>
#include <string>
#include <fstream>

using namespace std;
const int TABLE_SIZE = 41238;

class HashClass
{

	struct	NODE
	{
		string word;
		int key;
		NODE* next;

	};

	NODE* HashTable[TABLE_SIZE], *ptr;

public:
	HashClass();
	void DisplayMenu();
	int HashFunc(string word);
	void ReadFile(ifstream& myfile);
	void menuFunction(const char option, HashClass*);
	void unscramble();
	void Print();
	~HashClass();
};
void clearFunction();

#endif Hash_h