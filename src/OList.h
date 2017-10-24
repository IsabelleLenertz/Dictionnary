// Author: Isabelle Delmas
// Lab #5: Ordered list
// Due date: October 11 2016
#ifndef OLIST_H
#define OLIST_H


#include <string>
#include <stdio.h>
#include <iostream>

using namespace std;

template<typename Type>
struct Node {
	Type data;
	Node * pNext;

};

template<typename Type>
class OList
{
	friend ostream & operator<<(ostream & out, const OList<Type> & myList) {
		Node<Type>* currentPtr = myList.head.pNext;
		out << "{ ";
		while (currentPtr != nullptr) {
			if (currentPtr != myList.pTail) {
				out << currentPtr->data << ", ";
			}
			else {
				out << currentPtr->data;
			}
			currentPtr = currentPtr->pNext;
		}
		out << " }";
		return out;
	};
private:
	int size;
	Node<Type> head;		// the head is a dummy node. does not contain any data
	Node<Type> * pTail;

	// Return a pointer to the Node that val should be inserted after.
	// pre represents a node where we start the search.
	// Assumes that the target does not go before the pre pointer sent by the client
	// REturns nullptr if the list is empty
	Node<Type> * findInsertPoint(Node<Type> * pre, Type & val);


	// Assumes that the target in not in the pointer sent by the client
	// returns a pointer to the node before the data the client is looking for
	// throw a logic_error if the list is empty
	// returns nullptr if the target was not found
	Node<Type> * findPrevious(Node<Type> * pre, Type & val);

	// Helper function for printBackwards in order to use recursion
	void printBackwardsRecursion(Node<Type> * currentPtr) const;


public:
	// constuctors
	OList();
	OList(Type unsortedArray[], int size);		// throws bad_alloc if the program could not allocate enough memory
	OList(const OList<Type>& other);			// copy constructor

												// Destructor
	virtual ~OList();

	// Operations
	void print() const;
	void printBackwards() const;
	int getSize() const;
	Type getSmallest() const;
	Type getBiggest() const;
	int find(Type target) const;
	bool insert(Type newElement);
	bool remove(Type target, bool TF = true);
	bool clear();
	bool isEmpty()const;

	// operator overloads
	const OList<Type>& operator=(const OList<Type> & other);
	void operator+=(const OList<Type> &  other);
	OList<Type> operator+(const OList<Type> &  other) const;
	bool operator==(const OList<Type> &  other) const;
	bool operator!=(const OList<Type> &  other) const;


};

template<typename Type>
OList<Type> OList<Type>::operator+(const OList<Type> & other) const {
	// creates a new OList
	OList<Type>  newList = other;
	Node<Type> * pInsertPosition = &(newList.head);		// keeps track of the insert position
	Node<Type> * pCurrent = this->head.pNext;			// keeps track of the element to insert
	Node<Type> * pNewNode = nullptr;
	Node<Type> * tempNextPtr = nullptr;

	// Calculates the new size
	newList.size = other.size + this->size;

	// for the all the elements in the list (this)
	while (pCurrent != nullptr) {
		// Creates a copie of the new Node
		try {
			pNewNode = new Node<Type>;
		}
		catch (bad_alloc) {
			// exits if the allocation fails, and return false.
			throw runtime_error("running out of memory");
		}
		pNewNode->data = pCurrent->data;

		// Looks where to insert the node
		Type temp = pCurrent->data;
		pInsertPosition = newList.findInsertPoint(pInsertPosition, temp);

		// Inserts the node
		tempNextPtr = pInsertPosition->pNext;			// saves teh next
		pInsertPosition->pNext = pNewNode;				// inserts the new node
		pNewNode->pNext = tempNextPtr;						// connects the new node to the end of the list

															// check if the node was added to the end of the list
		if (tempNextPtr == nullptr) {
			// updates the tail
			newList.pTail = pNewNode;
		}
		pCurrent = pCurrent->pNext;
	}

	return newList;
	// TBD
}


// constuctors
template<typename Type>
OList<Type>::OList() {
	this->size = 0;
	this->head.pNext = nullptr;
	this->pTail = nullptr;
}
template<typename Type>
// throw bad_alloc if the program could not allocate enough memory
OList<Type>::OList(Type unsortedArray[], int size) {
	// goes thought the array and adds every elements
	for (int i = 0; i < size; i++) {
		if ((this->insert(unsortedArray[i])) == false) { throw runtime_error("not enough memory"); }
	}

}

// copy constructor
template<typename Type>
OList<Type>::OList(const OList<Type>& other) {
	this->size = 0;
	this->head.pNext = nullptr;
	this->pTail = nullptr;

	// used the asigment operator
	this->operator=(other);
	//TBT
}


// Destructor
template<typename Type>
OList<Type>::~OList() {
	this->clear();
}

// Operations

template<typename Type>
// prints using cout
void OList<Type>::print() const {

	Node<Type>* currentPtr = this->head.pNext;

	// goes through the entire list
	// prints: 
	//			position (starting at 1): element
	cout << "{ ";
	while (currentPtr != nullptr) {
		if (currentPtr != this->pTail) {
			cout << currentPtr->data << ", ";
		}
		else {
			cout << currentPtr->data;
		}
		currentPtr = currentPtr->pNext;
	}
	cout << " }" << endl;
}

template<typename Type>
// using recursion
void OList<Type>::printBackwards() const {
	printBackwardsRecursion(this->head.pNext);
	cout << " }" << endl;
}

template<typename Type>
// Helper function to use reusion for printBackwards.
void OList<Type>::printBackwardsRecursion(Node<Type> * currentPtr) const {
	// Recursive case
	if (currentPtr != nullptr) {
		printBackwardsRecursion(currentPtr->pNext);
		// prints the data, stating by the ned of the list
		if (currentPtr != this->head.pNext) {
			cout << currentPtr->data << ", ";
		}
		else {
			cout << currentPtr->data;
		}
	}
	else {
		cout << "{ ";
	}

	// Exit
	return;
}

template<typename Type>
int OList<Type>::getSize() const {
	return (this->size);
}

template<typename Type>
Type OList<Type>::getSmallest() const {
	if (this->isEmpty() == true) {
		throw logic_error("The List is empty");
	}
	else {
		return (this->head.pNext->data);
	}
}

template<typename Type>
Type OList<Type>::getBiggest()const {
	if (this->isEmpty() == true) {
		throw logic_error("The List is empty");
	}
	else {
		return (this->pTail->data);
	}
}

template<typename Type>
// returns the inde of the element
// returns -1 if the element was not found.

int OList<Type>::find(Type target) const {
	Node<Type>* currentPtr = nullptr;
	int counter = 0;

	if (this->isEmpty() == false) {
		currentPtr = this->head.pNext;
	}


	while (currentPtr != nullptr) {
		if (currentPtr->data < target) {
			// moves on to the next node
			currentPtr = currentPtr->pNext;

			// increases the counter
			counter++;
		}
		else if (currentPtr->data == target) {
			// found it !
			// leaves the counter unchanged
			break;
		}
		else {
			// went to far, it's not here
			counter = -1;
			break;
		}
	}// end of while

	 // check if we reached the end of the list
	if (currentPtr == nullptr) { return -1; }	// Target was not found
	else { return counter; }					// REturns the counter with the index or -1
}

template<typename Type>
bool OList<Type>::insert(Type newElement) {
	Node<Type> * pNewNode = nullptr;
	// Create a new node with a temp pointer
	try {
		pNewNode = new Node<Type>;
	}
	catch (bad_alloc) {
		// exits if the allocation fails, and return false.
		return false;
	}
	pNewNode->data = newElement;

	// Get the insertion position (returns nullptr if the list is empty)
	Node<Type> * pInsertPosition = this->findInsertPoint(&head, newElement);

	// If the insertPosition was found (ie if the list is not empty)
	if (pInsertPosition != nullptr) {
		// Saves the next
		Node<Type> * pTemp = pInsertPosition->pNext;
		// Places the new node after the insert position
		pInsertPosition->pNext = pNewNode;
		// Connects to the rest of the list
		pNewNode->pNext = pTemp;

		// updates the size
		this->size++;

		// Check if the the tail needs to be updated
		if (pInsertPosition == this->pTail) {
			pTail = pInsertPosition->pNext;
		}
	}
	// if findInsertPoint retured nullptr (ie if the list is empty)
	else {
		// puts the new node after the head
		this->head.pNext = pNewNode;
		pNewNode->pNext = nullptr;
		this->size++;
		// updates the tail
		this->pTail = pNewNode;
	}

	return true;
}

template<typename Type>
bool OList<Type>::remove(Type target, bool TF = true) {
	bool returnValue = true;			// true if at least one element was removed
	int counter = 0;					// counts the number of elements removed
	Node<Type> * previous = &(this->head);
	Node<Type> * next = nullptr;

	// removes at least one occurence if found
	do {
		// find the position of the previous node (starting either at the head, or at the position found in the previous occuence of the loop
		// previous will be nullptr if the target was not found
		previous = this->findPrevious(previous, target);
		if (previous == nullptr) {
			TF = false;
			break;
		}
		// Saves the next
		next = previous->pNext->pNext;
		// Deletes the node
		delete previous->pNext;
		// Reconnects the list
		previous->pNext = next;

		// updates the size
		this->size--;

		// Updates the counter
		counter++;

		// Check if the tail has to be udated
		if (next == nullptr) {
			this->pTail = previous;
		}

	} while (TF == true && size != 0); // do it again if the user asked for every occurence to be removed

									   // Exit wiht the appropriate message
	if (counter == 0) { returnValue = false; }

	return returnValue;
}

template<typename Type>
bool OList<Type>::clear() {
	Node<Type> * currentPtr = this->head.pNext;
	Node<Type> * nextPtr = nullptr;

	// delaocates all the dynamicaly allocated memory
	while (currentPtr != nullptr) {
		nextPtr = currentPtr->pNext;
		delete currentPtr;
		currentPtr = nextPtr;
	}

	// Reinitializes the head
	this->size = 0;
	this->head.pNext = nullptr;
	this->pTail = nullptr;

	return true;
}

template<typename Type>
bool OList<Type>::isEmpty() const {
	return (this->size == 0);
}

// operator overloads
template<typename Type>
const OList<Type>& OList<Type>::operator=(const OList<Type> & other) {
	Node<Type> * insertPtr = &(this->head);		// used to keep track of the last insertion position in the new list
	const Node<Type> * currentPtr = &(other.head);	// used to keep track of the current element in the other list
	Node<Type> * tempPtr = nullptr;

	// makes sure the lists are not identical before doing any assigment
	if (this->operator==(other) == true) {
		// exits
		return *this;
	}
	else {
		// Clears the list
		this->clear();

		// Copies the size
		this->size = other.size;

		// Copies the other list into the new list
		currentPtr = currentPtr->pNext;	// get the first element
		while (currentPtr != nullptr) {
			// Creates a new node
			Node<Type> * pNewNode = nullptr;
			try {
				pNewNode = new Node<Type>;
			}
			// Makes sure there is enough memory available
			catch (bad_alloc) {
				throw runtime_error("not enough memory, cannot create new Node");
			}
			pNewNode->data = currentPtr->data;

			// Connects the new Node to the end of new list (no need to sort, the data is already sorted in the other list)
			insertPtr->pNext = pNewNode;

			// Goes to the next element
			currentPtr = currentPtr->pNext;
			insertPtr = insertPtr->pNext;
		}

		//Updates the tail
		this->pTail = insertPtr;
		insertPtr->pNext = nullptr;
	}// end of else

	 // Exit
	return *this;
	// TBT
}
//
template<typename Type>
void OList<Type>::operator+=(const OList &  other) {
	Node<Type> * insertPtr = &(this->head);		// used to keep track of the last insertion position in the original list
	const Node<Type> * currentPtr = &(other.head);	// used to keep track of the current element in the other list
	Node<Type> * tempPtr = nullptr;

	// If the current list is empty
	if (this->size == 0) {
		this->operator=(other);		//	simply copies the list
	}
	// If the list is not empty
	else {
		// Goes trought the new list
		currentPtr = currentPtr->pNext;	// get the next element
		while (currentPtr != nullptr) {
			// Creates a new node
			Node<Type> * pNewNode = nullptr;
			try {
				pNewNode = new Node<Type>;
			}
			// Makes sure there is enough memory available
			catch (bad_alloc) {
				throw runtime_error("not enough memory, cannot create new Node");
			}
			pNewNode->data = currentPtr->data;

			// Find the insertion point
			Type temp = currentPtr->data;
			insertPtr = findInsertPoint(insertPtr, temp);

			// Connects the new Node to the old list
			tempPtr = insertPtr->pNext;
			insertPtr->pNext = pNewNode;
			pNewNode->pNext = tempPtr;

			// Updates the size
			this->size++;

			// Check if the tail needs to be updated
			if (tempPtr == nullptr) {
				pTail = pNewNode;
			}

			// Goes to the next element
			currentPtr = currentPtr->pNext;
		}// end of while
	} // end of else
	  // TBT
}
//


template<typename Type>
bool OList<Type>::operator==(const OList<Type> & other) const {
	bool returnvalue;
	Node<Type> * currentthisPtr = this->head.pNext;
	Node<Type> * currentotherPtr = other.head.pNext;

	// If the sizes are different, the lists are different
	returnvalue = (this->size == other.size);

	// If they have the same size
	if (returnvalue == true) {
		// goes through the lists
		for (int i = 0; i < this->size; i++) {
			// compare each data
			returnvalue = (currentthisPtr->data == currentotherPtr->data);
			if (returnvalue == true) {
				currentthisPtr = currentthisPtr->pNext;
				currentotherPtr = currentotherPtr->pNext;
			}
			// exists as soon as a different data was found
			else {
				break;
			}
		}// end of for
	}
	// end of if
	else {
		returnvalue = false;
	}

	// Exit
	return returnvalue;
}

template<typename Type>
bool OList<Type>::operator!=(const OList & other) const {
	return !(this->operator==(other));
}

// Return a pointer to the Node that val should be inserted after.
// pre represents a node where we start the search.
// returns nullptr is the list is empty
// Assumes that the target does not go before the pre pointer sent by the client
template<typename Type>
Node<Type> * OList<Type>::findInsertPoint(Node<Type> * pre, Type & target) {

	// If the list is empty, return nullptr to signify target has to be inserted at the begining
	if (this->isEmpty() == true) { return  nullptr; }

	// Assumes that the target does not go before the pre pointer sent by the client
	Node<Type> * previousPtr = pre;
	pre = pre->pNext;

	while (pre != nullptr) {
		// if the current data is smaller than the target
		if ((pre->data) < target) {
			// saves the previous node
			previousPtr = pre;
			// moves on to the next node
			pre = pre->pNext;
		}
		else {
			// returns the previous node.
			return previousPtr;
		}
	}
	return previousPtr;
}

// Assumes that the target in not in the pointer sent by the client
// returns a pointer to the node before the data the client is looking for
// throw a logic_error if the list is empty
// returns nullptr if the target was not found
template<typename Type>
Node<Type> * OList<Type>::findPrevious(Node<Type> * pre, Type & target) {

	// If the list is empty, throw an error: there is nothing to remove
	if (this->isEmpty() == true) {
		// throw logic_error("Empty list"); // not handeled by your tester
		return nullptr;
	}

	// Assumes that the target does not go before the pre pointer sent by the client
	Node<Type> * previousPtr = pre;
	pre = pre->pNext;

	while (pre != nullptr) {
		// if the current data is smaller than the target
		if ((pre->data) < target) {
			// saves the previous node
			previousPtr = pre;
			// moves on to the next node
			pre = pre->pNext;
		}
		// if the target was found
		else if (pre->data == target) {
			// returns the previous node.
			return previousPtr;
		}
		// if the current data is bigger than the target, stops searching and signifies the target was not found
		else {
			return nullptr;
		}
	}// end of while

	 // Makes sure the previousPtr is not the end of the list
	 //(ie the previous loop end because it reaches the end of the loop but the data were still smaller than the target)
	if (previousPtr == this->pTail) {
		// signifies the target was not found
		return nullptr;
	}
	else {
		// returns the pointer to the previous
		return previousPtr;
	}
}


#endif


