#ifndef LETTERBAG_H
#define LETTERBAG_H

#include <vector>
#include <iostream>
#include<cstring>

using namespace std;

class LetterBag {
	friend ostream & operator<<(ostream & out, const LetterBag & myBag);
public:

	// no-parameter constructor for an empty LetterBag.
	LetterBag();

	// initialize using letters in v, omitting non-alphabetical chars
	// input = v, vector of char, have to be alphabetical chars
	// output = nothing
	LetterBag(const vector<char> & v);

    // initialize using letters in s, omitting non-alphabetical chars
	// input = s, string, have to be alphabetical chars
	// output = nothing
	LetterBag(const string& s);

	// return true iff *this equals other
	bool operator==(const LetterBag & other) const;

	// return false iff *this equals other
	bool operator!=(const LetterBag & other) const;

	// return the current size of the LetterBag
	int getCurrentSize() const;

	// return true iff the LetterBag is empty
	bool isEmpty() const;


	// function = add an occurrence of c to the LetterBag
	// input = c, an alphabetical char (ie between 'a' and 'z' or 'A' and 'Z')
	// output = a reference to the same updated bag
	// special cases=
	//		throw "charfull" is no more room for that char
	//		throw "bagfull" is no more room in the bag
	//		throw "wronginput" if the input was not an alphabetical char
	LetterBag & add(char c);

	// remove one occurrence of c (if there is one).
	// input = c, an alphabetical char (ie between 'a' and 'z' or 'A' and 'Z')
	// output = a reference to the same updated bag
	// special cases=
	//		throw "wronginput" if the input is not an alphabetical char
	//		throw "nochar" if there is no char to remove
	LetterBag & remove(char c);

	// remove all occurrences of all letters
	LetterBag & clear();

	// function = count occurrences of c
	// input = char between 'a' and 'z' or 'A' and 'Z'
	// output = integer, number of occurance in the bag
	// special cases = 
	//		throw "wrongInput" if the input was not alphabetical
	int getFrequency(char c) const;

	// return a vector with the letters in this object, in sorted order.
	vector<char> toVector() const;

	// return true if *this is a subbag of other. 
	bool isSubbag(const LetterBag & other) const;

	// prints the letters in the bag in alaphabetical order.
	void print(ostream & out);

	// replace the letters by the new string
	void set(const string & s);

	// converts to a string in alphabetical order
	string toString() const;


private:

	// holds the number of each letter
	int counts[26];					// no need to make 26 a named constant since the English alphabet never changes size
									// total number of letters in the bag, has to be updated by the add and remove methods
	int size;

	// return true iif the char is aplhabetical (ie a<= c <= z OR A <= c <= Z )
	static bool inRange(char c);




};

#endif