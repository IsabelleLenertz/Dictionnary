#include "Dictionary.h"



Dictionary::Dictionary()
{
    int default = 100;
    this->size = default;
	this->tablePtr = new AnagramSet*[default];
	this->numOfWords = 0;

    this->initilize();
}

void Dictionary::initilize() {

    // goes through the table of pointers and sets them to nullptr
    for (int i = 0; i < this->size; i++) {
        tablePtr[i] = nullptr;
    }
}

Dictionary::Dictionary(string words[], int numberOfWords, int sizeOfHashTable)
{
	// dynamicaly allocats the array
	this->size = sizeOfHashTable;
	this->tablePtr = new AnagramSet*[sizeOfHashTable];
	// creates a letter bag to be used later
	LetterBag tempLB;

    // Initilizes the table to nullptr
    this->initilize();
	this->numOfWords = 0; // will be updated by the add function

	// goes through the array of words
	for (int i = 0; i < numberOfWords; i++) {
        // insert every words in the array
        this->insert(words[i]);
	}

}		
// constructor
// int: size of the table to be created to store the words
Dictionary::Dictionary(int sizeOfHashTable) {

	// dynamicaly allocats the array
	this->size = sizeOfHashTable;
	this->tablePtr = new AnagramSet*[sizeOfHashTable];
	// creates a letter bag to be used later
	LetterBag tempLB;

	// Initilizes the table to nullptr
	this->initilize();
}


// Insert string into it into the table.
void Dictionary::insert(const string& newWord) {
	LetterBag tempLB(newWord);

	if (newWord == "accurse") {
		int a = 5;

	}

    // Uses the hash function to find the location in the table (array index)
    int index = this->hashFunction(tempLB);

	// if collision, goes to the next until getNext()!=nullptr;
    if (this->tablePtr[index] != nullptr) {
		AnagramSet* tempASptr = this->tablePtr[index]->getNext();
		AnagramSet* previousASptr = this->tablePtr[index];

		// if there is only one anagram
		if (tempASptr == nullptr) {
			// if the key is the same adds it
			LetterBag testLB = tablePtr[index]->getKey();
			if (testLB == tempLB) {
				tablePtr[index]->insert(newWord);
				this->numOfWords++;
			}
			// else creates a new anagram set
			else {
				tempASptr = new AnagramSet(newWord);
				tablePtr[index]->setNext(tempASptr);
			}

		}
		// if there is more than one anagram set in the list
		else{
			// while the end of the collision list is not reached
			while (tempASptr != nullptr) {
				// if AnagramSet already exists, add words
				LetterBag testLB = previousASptr->getKey();
				if (testLB == tempLB) {
					previousASptr->insert(newWord);
					this->numOfWords++;
					return;
				}
				// else looks for the next one
				else {
					previousASptr = tempASptr;
					tempASptr = tempASptr->getNext();
				}
			}

			// Check if the last one is the good one.
			LetterBag testLB = previousASptr->getKey();
			if (testLB == tempLB) {
				previousASptr->insert(newWord);
				this->numOfWords++;
				return;
			}

			// if new AnagramSet needed, creates it using the overwritten contructor.
			tempASptr = new AnagramSet(newWord);
			this->numOfWords++;
			previousASptr->setNext(tempASptr);		// connects it to the list
			// connects to the list
		}		
    }
    // if the is no collision
    else {
		this->tablePtr[index] = new AnagramSet(newWord);
		this->numOfWords++;
	}


}


Dictionary::~Dictionary()
{
	AnagramSet* tempptr = nullptr;
	AnagramSet* nextptr = nullptr;
	
	// goes trought the table
	for (int i = 0; i < this->size; i++) {
		// goes throught the chain of AnagramSets
		tempptr = this->tablePtr[i];
		while (tempptr != nullptr) {
			nextptr = tempptr->getNext();
			delete tempptr;
			tempptr = nextptr;
		}
	}

	// TBT
}

unsigned  Dictionary::hashFunction(const LetterBag& lb){
	// converts the letter bag into an alphabetical string
	string s = lb.toString();

	unsigned int h = s[0];
	for (unsigned int i = 1; i < s.length(); i++)
		h += unsigned int (pow(7, (s[i] - 'A')) );
	return h % this->size ;

	// TBD
}

void Dictionary::remove(string word) {
	bool found = false;
	LetterBag target(word);

	// Use the hash function to get the key
	int index = this->hashFunction(target);

	// goes there in the table
	AnagramSet* currentset = this->tablePtr[index];
	AnagramSet* previousset = nullptr;

	// linear search to find the right anagram set
	while (!found) {
		if (currentset == nullptr)	break;
		else if (target == currentset->getKey())	found = true;
		else {
			previousset = currentset;
			currentset = currentset->getNext();
		}
	}

	if (found) {
		currentset->remove(word);
		this->numOfWords--;
		// if the Anagram set is now empty, removes it from the dictionary
		if (currentset->isEmpty()) {
			if (previousset!=nullptr) previousset->setNext(currentset->getNext());
			else this->tablePtr[index] = nullptr;
			delete currentset;
		}
	}
	// exit the function
	return;

}
AnagramSet Dictionary::getSet(string word) {
	
	bool found = false;
	AnagramSet* currentset, nextset;
	AnagramSet returnvalue;
	LetterBag target(word);

	// Use the hash function to get the key
	int index = this->hashFunction(target);

	// goes there in the table
	currentset = this->tablePtr[index];

	// linear search to find the right anagram set
	while (!found) {
		if (currentset == nullptr)	break;
		else if (target == currentset->getKey()) {
			found = true;
			returnvalue = *currentset;
		}
		else {
			currentset = currentset->getNext();
		}
	}

	// returns the anagram set if found, returns and empty anagramset if not found
	return returnvalue;
	
	AnagramSet as;
	return as;
    // TBD
}
void Dictionary::print() {

	AnagramSet* currentASptr = nullptr;
	// goes throught the array
	for (int i = 0; i < this->size; i++) {
		cout << "[" << i << "]";
		// print all linked anagram for each index
		currentASptr = this->tablePtr[i];
		while (currentASptr != nullptr) {
			currentASptr->print(std::cout);
			currentASptr = currentASptr->getNext();
		}
		cout << endl;
	}

	// exit
	return;
}
bool Dictionary::contains(string word) {
	bool returnvalue;
	LetterBag target(word);

	// Use the hash function to get the key
	int index = this->hashFunction(target);

	// goes there in the table
	AnagramSet* currentset = this->tablePtr[index];

	// linear search to find the right anagram set
	while (true) {
		if (currentset == nullptr)	return false;
		else if (target == currentset->getKey()) break;
		else currentset = currentset->getNext();
	}

	// exit the function
	returnvalue = currentset->contains(word);		// make sure the word is in the set found
	return returnvalue;								// returns true if the word was found, else otherwise.
		

}

// FRIEND FUNCTIONS

ostream & operator<<(ostream & out, const Dictionary & dic) {
	bool flag;
	AnagramSet* currentASptr = nullptr;
	// goes throught the array
	for (int i = 0; i < dic.size; i++) {
		// send out all linked anagram for each index
		flag = false;
		currentASptr = dic.tablePtr[i];
		while (currentASptr != nullptr) {
			flag = true;
			currentASptr->print(out);
			currentASptr = currentASptr->getNext();
		}
		if (flag) out << endl;
	}
	return out;
}