#pragma once

#ifndef ANAGRAMSET_H
#define ANAGRAMSET_H

#include <string>
#include "LetterBag.h"
#include "OList.h"

using namespace std;

class AnagramSet
{
	friend ostream & operator<<(ostream & out, const AnagramSet & myAnagrams);
	friend void operator>>(AnagramSet & myAnagrams, const string word);

private:
	LetterBag key;
	OList words;
	int size;
	AnagramSet* nextptr; // used to link anagram sets
	// sets the key, used only when adding the first word
	void setKey(const string&);


public:
	// constructors and destructor
	AnagramSet();
	AnagramSet(string);
	AnagramSet(const AnagramSet& other);			// copy constructor TBT
	virtual ~AnagramSet();

	// Member functions
	int getSize();
	bool isEmpty();
	void insert(string);
	void print(ostream & out);
	void setNext(AnagramSet* nextptr);
	AnagramSet* getNext();
	LetterBag getKey() const;
	void remove(const string);		// TBT
	bool contains(const string);	// TBT

	// Operator overlord
	const AnagramSet& operator=(const AnagramSet & other);


};

#endif // !ANAGRAMSET_H
