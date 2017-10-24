#pragma once
#include <string>
#include <iostream>
using namespace std;

struct BNode{
	BNode* smaller;
	BNode* bigger;
	string value;
};

class BTree
{
friend ostream & operator<<(ostream & out, const BTree & myTree);

private:
	BNode* root;
	int size;

	BNode* insertHelper(BNode*, BNode*);
	void deleteAll(BNode*);

	/// <summary>
	/// Recursive function sending the tree in alphabetical order to a stramm
	/// </summary>
	/// <param name="ptr">ptr to the root of the subtree to send to the stream.</param>
	/// <note> Called by operator<< </note>
	/// <returns></returns>
	string outputHelper(const BNode*) const;

	/// <summary> recursive function used to find a target.</summary>
	/// <param name="nodeptr">A ptr to the root of the subtree.</param>
	/// <param name="target">The target to be found.</param>
	/// <returns>True iif the target was found</returns>
	bool findHelper(BNode* nodeptr, string target);

	// Written with Corrano's algorithm
	BNode* removeValue(BNode* subTreePtr, string target, bool& success);
	BNode* removeNode(BNode* nodePtr);
	BNode* removeLeftmostNode(BNode* nodePtr, string& inorderSuccessor);

	BNode* equalHelper(BNode* original);






public:
	BTree();
	BTree(const BTree & other);	// copy constructor
	virtual ~BTree();


	/// <summary>
	/// Inserts the specified new value.
	/// </summary>
	/// <param name="">The .</param>
	void insert(string);
	bool remove(string);

	/// <summary> Verify is a specific string is stored in the binary tree.</summary>
	/// <param name=""> the target to be found.</param>
	/// <returns>true iif the target was found</returns>
	bool find(string);

	// Operator overloards
	const BTree& operator= (const BTree& other);
};



