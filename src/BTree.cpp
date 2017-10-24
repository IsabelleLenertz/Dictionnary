#include "BTree.h"

BTree::BTree() {
	this->root = nullptr;
}

BTree::BTree(const BTree& other) {
	// Recursively copy of the children
	this->root = equalHelper(other.root);
}
// copy constructor TBT


BTree::~BTree() {
	deleteAll(this->root);
	return;
}

void BTree::deleteAll(BNode* ptr) {
	if (ptr != nullptr) {
		if (ptr->smaller != nullptr) deleteAll(ptr->smaller);
		if (ptr->bigger != nullptr) deleteAll(ptr->bigger);
		delete ptr;
	}
	return;
}


bool BTree::find(string target) {
	return this->findHelper(this->root, target);
	// TBD
}

bool BTree::findHelper(BNode* nodeptr, string target) {
	// if reach the end of the tree, signifies the node was not found (exit case 1)
	if (nodeptr == nullptr) {
		return false;
	// if the target if smaller than the one in the node, goes to the left (recursive case)
	} else if (nodeptr->value > target) {
		return this->findHelper(nodeptr->smaller, target);
	// if the target is bigger than the one in the node goes to the right (recursive case)
	} else if (nodeptr->value < target) {
		return this->findHelper(nodeptr->bigger, target);
	// if the value if the sams as the target, signifies the string was found (exit case 2)
	} else {
		return true;
	}
	// TBT
}

void BTree::insert(string newValue) {
	// Creats a new node for the value.
	BNode* newptr = new BNode;
	newptr->value = newValue;
	newptr->bigger = nullptr;
	newptr->smaller = nullptr;
	
	// Adds it into the tree recursively
	this->root = insertHelper(newptr, this->root);

	// Exit
	return;
}

// With the help of Corano's algorithms.
BNode* BTree::insertHelper(BNode* newnodeptr, BNode* subtreeptr) {
	// Exit case
	if (subtreeptr == nullptr) {
		return newnodeptr;
	// Recursive cases
	} else if (subtreeptr->value > newnodeptr->value) {
		BNode* tempPtr = insertHelper(newnodeptr, subtreeptr->smaller);
		subtreeptr->smaller = tempPtr;
	} else {
		BNode* tempPtr = insertHelper(newnodeptr, subtreeptr->bigger);
		subtreeptr->bigger = tempPtr;
	}
	return subtreeptr;
}

BNode* BTree::removeValue(BNode* subTreePtr, string target, bool& success) {
	if (subTreePtr == nullptr){
		success = false;
		return nullptr;
	} else if(subTreePtr->value == target){
		subTreePtr = removeNode(subTreePtr); // remove the item
		success = true;
		return subTreePtr;
	}
	else if (subTreePtr->value > target) {
		subTreePtr->smaller = removeValue(subTreePtr->smaller, target, success);
		return subTreePtr;
	} else {
		subTreePtr->bigger = removeValue(subTreePtr->bigger, target, success);
		return subTreePtr;
	}
}

BNode* BTree::removeNode(BNode* nodePtr) {
	// If node is a leaf
	if (nodePtr->smaller == nullptr && nodePtr->bigger == nullptr) {
		delete nodePtr;
		nodePtr = nullptr;
		return nodePtr;
	// If node has only one child
	} else if (nodePtr->smaller == nullptr || nodePtr->bigger == nullptr) {
		if (nodePtr->smaller != nullptr) {
			// replaces the value of smaller node by the one to delete
			nodePtr->value = nodePtr->smaller->value;
			delete nodePtr->smaller;
			nodePtr->smaller = nullptr;
			return nodePtr;
		}
		else {
			// replaces the value of bigger node by the one to delete
			nodePtr->value = nodePtr->bigger->value;
			delete nodePtr->bigger;
			nodePtr->bigger = nullptr;
			return nodePtr;
		}
	// If node has two children
	} else {
		//Find the inorder sucessor of the entry in node (N): it is the lefts subtree rooted at N's right child
		string newNodeValue;
		nodePtr->bigger = removeLeftmostNode(nodePtr->bigger, newNodeValue);
		nodePtr->value = newNodeValue;
		return nodePtr;
	}
}

BNode* BTree::removeLeftmostNode(BNode* nodePtr, string& inorderSuccessor) {
	if (nodePtr->smaller == nullptr) {
			// this is the node you want; it has ne left child but might have a right subtree
			inorderSuccessor = nodePtr->value;
			return removeNode(nodePtr);
	} else {
		nodePtr->smaller = removeLeftmostNode(nodePtr->smaller, inorderSuccessor);
		return nodePtr;
	}

}

bool BTree::remove(string target) {
	bool success = false;
	removeValue(this->root, target, success);
	return success;
}


// OPERATOR OVERLOADS
const BTree& BTree::operator= (const BTree& other) {

	// Recursively copy of the children
	this->root = equalHelper(other.root);

	// Exit
	return (*this);
}

BNode* BTree::equalHelper(BNode* original) {
	BNode* duplicate = nullptr;

	// Base cases
	if (original == nullptr) {
		return nullptr;
	}
	// if the node is a leaf
	if (original->smaller == nullptr && original->bigger == nullptr) {
		duplicate = new BNode;
		duplicate->value = original->value;
		duplicate->smaller = nullptr;
		duplicate->bigger = nullptr;
	// Recursive Case
	} else {
		duplicate = new BNode;
		duplicate->value = original->value;
		duplicate->smaller = equalHelper(original->smaller);
		duplicate->bigger = equalHelper(original->bigger);
	}
	return duplicate; 
}

// FRIEND FUNCTIONS
ostream & operator<<(ostream & out, const BTree & myTree) {
	out << myTree.outputHelper(myTree.root);
	return out;
}

/// <summary>
/// Recursive function sending the tree in alphabetical order to a stramm
/// </summary>
/// <param name="ptr">ptr to the root of the subtree to send to the stream.</param>
/// <note> Called by operator<< </note>
/// <returns></returns>
string BTree::outputHelper(const BNode* ptr) const {
	string temp;

	// Go left
	if (ptr->smaller != nullptr) {
		temp += outputHelper(ptr->smaller);
	}

	// Add current value
	temp += ptr->value;
	temp += " ";

	// Go right
	if (ptr->bigger != nullptr) {
		temp += outputHelper(ptr->bigger);
	}

	// Exit
	return temp;
}
