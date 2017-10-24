#include "LetterBag.h"

// no-parameter constructor for an empty LetterBag.
LetterBag::LetterBag() {
	// Initialize  the number of all letters to 0
	this->clear();
	this->size = 0;
}

// initialize using letters in v, omitting non-alphabetical chars
// input = v, vector of char, have to be alphabetical chars
// output = nothing
/// <summary>
/// Initializes a new instance of the <see cref="LetterBag"/> class.
/// </summary>
/// <param name="v">The v.</param>
LetterBag::LetterBag(const vector<char> & v) {
	// Initialize  the number of all letters to 0
	this->clear();
	this->size = 0;

	// Goes trough the vector and adds all the letters into the bag
	for (unsigned int i = 0; i < v.size(); i++) {
		// adds the letter to the bag
		try {
			this->add(v[i]);
		}
		catch (const char*) {
		}
	}

}

// initialize using letters in s, omitting non-alphabetical chars
// input = s, string, have to be alphabetical chars
// output = nothing
LetterBag::LetterBag(const string & s) {
    	// Initialize  the number of all letters to 0
	this->clear();
	this->size = 0;

	// Goes trough the vector and adds all the letters into the bag
	for (unsigned int i = 0; i < s.size(); i++) {
		// adds the letter to the bag
		try {
			this->add(s[i]);
		}
		catch (const char*) {
		}
	}

}

// return true iff *this equals other
bool LetterBag::operator==(const LetterBag & other) const {
	bool returnvalue = true;		// initilize the return value to true (ie the bags are equal until proven to be the different)

									// for the 27 letters of the alphabet
	for (int i = 0; i < 26; i++) {
		// Compare the contant of the two bags (i+65 = ascii value of the letters, getFrency asks for a char)
		if ((this->counts[i]) != (other.getFrequency(i + 65))) {
			// if the two bags do not contain the same amount of a letter, changes the returnvalue and exists the for loop
			returnvalue = false;
			break;
		}
	}
	return returnvalue;
}

// return false iff *this equals other
bool LetterBag::operator!=(const LetterBag & other) const {
	return !(this->operator==(other)); // returns the inverse of ==
}

// return the current size of the LetterBag
int LetterBag::getCurrentSize() const {
	return this->size;
}

// return true iff the LetterBag is empty
bool LetterBag::isEmpty() const {
	bool returnvalue = false;

	// Check if the size is 0
	if (this->getCurrentSize() == 0) {
		// Updates the return value
		returnvalue = true;
	}

	// Exit the function
	return returnvalue;
}

// function = add an occurrence of c to the LetterBag
// input = c, an alphabetical char (ie between 'a' and 'z' or 'A' and 'Z')
// output = a reference to the same updated bag
// special cases=
//		throw "charfull" is no more room for that char
//		throw "bagfull" is no more room in the bag
//		throw "wronginput" if the input was not an alphabetical char
LetterBag & LetterBag::add(char c) {
	// Make the char uppercase and make sure the client entered an alphabetical char
	c = toupper(c);

	if (inRange(c) == false) {
		throw "wronginput";
	}
	int index = c - 'A';
	// Check if there is still room to add the char
	if (counts[index] == LONG_MAX) {
		// does not add a char is the storage is about to overload (mas size of an int)
		throw "charfull";
	}
	// if the bag is not full
	else if (size < LONG_MAX) {
		// Add the char
		this->counts[index] ++;
		// updates the size
		this->size++;
	}
	else {
		// does not add a char is the size of the bag is about to overload (mas size of an int)
		throw "bagfull";
	}

	// Exist the function
	return *this;
}

// remove one occurrence of c (if there is one).
// input = c, an alphabetical char (ie between 'a' and 'z' or 'A' and 'Z')
// output = a reference to the same updated bag
// special cases=
//		throw "wronginput" if the input is not an alphabetical char
//		throw "nochar" if there is no char to remove
LetterBag & LetterBag::remove(char c) {
	c = toupper(c);

	// Make the char uppercase and make sure the client entered an alphabetical char
	if (inRange(c) == false) {
		throw "wronginput";
	}

	// Make sure there is a char before removing it
	if (counts[c - 'A'] == 0) {
		throw "nochar";
	}
	else {
		// Update the size
		this->size--;
		// Remove the cahr
		counts[c - 65] --;
	}
	// Exist the function
	return *this;
}

// remove all occurrences of all letters
LetterBag & LetterBag::clear() {
	// Go through the array of letters and sets them all to 0
	for (int i = 0; i < 26; i++) {
		this->counts[i] = 0;
	}
	this->size = 0;

	return *this;
}


// function = count occurrences of c
// input = char between 'a' and 'z' or 'A' and 'Z'
// output = integer, number of occurance in the bag
// special cases = 
//		throw "wrongInput" if the input was not alphabetical
int LetterBag::getFrequency(char c) const {
	
	c = toupper(c);

	// converts the char to an uppercase
	if (inRange(c) == false) {
		// signifies the client they used an non alphabetical char
		throw "wrongInput";
	}

	return this->counts[c - 'A'];
}

// return a vector with the letters in this object, in sorted order.
vector<char> LetterBag::toVector() const {
	vector<char> returnVector;

	// goes through the bag of letters
	for (int i = 0; i < 26; i++) {
		// Add the  number of the current letter in the bag
		for (int j = 0; j < counts[i]; j++) {
			returnVector.push_back(65 + i);
		}
	}

	// Exit the function
	return returnVector;
}

// return true if *this is a subbag of other. 
bool LetterBag::isSubbag(const LetterBag & other) const {
	bool returnvalue = true;

	// check if for each letter qte(letter in this) <= qte(letter in other)
	for (char i = 'A'; i <= 'Z'; i++) {
		if (this->getFrequency(i) > other.getFrequency(i)) {
			// if the current bage has more of one letter than other, change return value to false
			returnvalue = false;
			// then exist the for loop (no need to compare further, it is not a subbag)
			break;
		}
	}

	return returnvalue;
}

// return true iif the char is aplhabetical (ie a<= c <= z OR A <= c <= Z )
bool LetterBag::inRange(char c) {
	bool returnvalue = false;

	// check if c is an alphabetical character
	if (((c <= 'Z') && (c >= 'A')) || ((c <= 'z') && (c >= 'a'))) {
		returnvalue = true;
	}

	return returnvalue;
}

// prints the letters in the bag in alaphabetical order.
void LetterBag::print(ostream & out) {

	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < counts[i]; j++) {
			char tempChar = i + 'A';
				out << tempChar;
		}
	}
	out << " ";
}

// replace the letters by the new vector
void LetterBag::set(const string & s) {
	// Initialize  the number of all letters to 0
	this->clear();
	this->size = 0;

	// Goes trough the vector and adds all the letters into the bag
	for (unsigned int i = 0; i < s.length(); i++) {
		// adds the letter to the bag
		try {this->add(s[i]);}
		catch (const char*) {}
	}
}

// converts to a string in alphabetical order
string LetterBag::toString() const {

	string returnvalue = "";

	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < counts[i]; j++) {
			returnvalue += i + 'A';
		}
	}
	return returnvalue;
}

// FRIENDS FUNCTIONS

ostream & operator<<(ostream & out, const LetterBag & myBag) {
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < myBag.counts[i]; j++) {
			char tempChar = i + 'A';
			out << tempChar;
		}
	}
	return out;
}