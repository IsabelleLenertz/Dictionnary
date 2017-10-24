#include "AnagramSet.h"



AnagramSet::AnagramSet()
{
	this->size = 0;
	this->nextptr = nullptr;
}
AnagramSet::AnagramSet(string newWord)
{
	this->insert(newWord);
	this->size = 1;
	this->nextptr = nullptr;
}

// copy constructor
AnagramSet::AnagramSet(const AnagramSet& other) {
	// copy the key
	this->key = other.key;

	// copy the list of words
	this->words = other.words;

	// copy the size
	this->size = other.size;

	// does not connect it to the same list, it will be an independent AnagramSet.
	this->nextptr = nullptr;
}

AnagramSet::~AnagramSet()
{
}

int AnagramSet::getSize() {
	return this->size;
}

void AnagramSet::setNext(AnagramSet* nextptr) {
	this->nextptr = nextptr;
}
AnagramSet* AnagramSet::getNext() {
	return this->nextptr;
}

bool AnagramSet::isEmpty(){
	return (this->size == 0);
}



void AnagramSet::insert(string newWord) {
	// if the anagram set is empty, sets the key
	if (this->isEmpty()) {
		this->setKey(newWord);
	}
	
	// Adds a new word into the list
	this->words.insert(newWord);

	// increase size
	this->size++;
}
void AnagramSet::print(ostream & out) {
	out << "Key: ";
	this->key.print(out);
	out << " Anagrams: " << this->words << " ";
}

void AnagramSet::setKey(const string & newKey) {
	this->key.set(newKey);
}

LetterBag AnagramSet::getKey() const {
	return this->key;
}

const AnagramSet& AnagramSet::operator=(const AnagramSet & other) {
	// copy the key
	this->key = other.key;

	// copy the list of words
	this->words = other.words;

	// copy the size
	this->size = other.size;

	// does not connect it to the same list, it will be an independent AnagramSet.
	this->nextptr = nullptr;

	return *this;
}

// removes a word from the list
void AnagramSet::remove(const string target) {
	this->words.remove(target);
	this->size--;
	return;
}

// returns true if a words is in the set
bool AnagramSet::contains(const string target) {
	// looks for the word in the Binary search tree
	int temp = this->words.find(target);

	return !(temp == -1);						// When using the OList

	 //return (this->words.find(target));		// when using the BTree
}



// FRIEND FUNCTIONS
ostream & operator<<(ostream & out, const AnagramSet & myAnagrams) {
	out << "Key: " << myAnagrams.key << " Anagrams: " << myAnagrams.words;

	return out;
}

void operator>> (AnagramSet & myAnagrams, const string word) {
	myAnagrams.insert(word);
}
