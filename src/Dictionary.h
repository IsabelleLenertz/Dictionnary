#pragma once
#ifndef DICTIONARY_H
#define DICTIONARY_H


#include <string>
#include "AnagramSet.h"
using namespace std;

class Dictionary
{
	friend ostream & operator<<(ostream &, const Dictionary &);

private:
	//table
	AnagramSet** tablePtr;	// pointer to a table to be allocated dynamically
	int size;				// size of the previous table
	int numOfWords;			// number of words stored into the dictionary

	// private member function
	unsigned  hashFunction(const LetterBag& s);

    void initilize();

public:
	// Default constructor
	// Default size of array = 100
	Dictionary();

	//Overwritten constructor
	// string: array of words to put into the dictionary
	// int: size of the previous arrau
	// int: size of the table to be created to store the words
	Dictionary(string words[], int numberOfWords, int sizeOfHashTable);

	//Overwritten constructor
	// int: size of the table to be created to store the words
	Dictionary(int sizeOfHashTable);

	// Destructor
	virtual ~Dictionary();		

	// member functions
    void insert(const string&);
    void remove(string);        // TBT
    AnagramSet getSet(string);  // TBT
    void print();               
    bool contains(string);

	// Operator overload


};


#endif // !DICTIONARY_H

