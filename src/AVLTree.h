#pragma once
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <sstream>
#include <iostream>
#include <istream>
using namespace std;


class AVLTree
{

private:

	struct Node
	{
		//Data
		int id;
		string name;

		//Meta-Data
		Node* left;
		Node* right;
		int height;

		//Constructor
		Node();
	};

	Node* root;

public:

	//Constructor
	AVLTree();

	//Destructor
	~AVLTree();



	//=========================//
	//=======ACCESSORS=========//
	//=========================//

	//Returns node with an id that matches idP; NULL otherwise
	Node* Search(Node* nodeP, int idP) const;

	//Sets resultP equal to the nth node found in inorder traversal
	void SearchNInOrder(Node* nodeP, int n, int& count, Node*& resultP);

	//Returns recalculation of height at nodeP
	int CalcHeight(Node* nodeP) const;

	//Returns the balance factor of n
	int GetBalanceFactor(Node* nodeP) const;

	//Returns Node of leftmost node from rootP
	Node* FindLeftmost(Node* rootP) const;



	//=========================//
	//========MUTATORS=========//
	//=========================//

	//Returns root of tree; inserts given nodeP into tree and self-balances; asserts there are no duplicates
	Node* Insert(Node* nodeP, Node* rootP);

	//Searches for and removes node with id = idP, starting from rootP; returns root node
	Node* Remove(Node* rootP, int idP);

	//Removes all nodes in the tree
	void RemoveAll(Node* nodeP);

	//Returns Node of new root (of subtree) after right rotation
	Node* RightRotate(Node* parentP);

	//Returns Node of new root (of subtree) after left rotation
	Node* LeftRotate(Node* parentP);

	//Returns Node of new root (of subtree) after left-right rotation
	Node* LeftRightRotate(Node* parentP);

	//Returns Node of new root (of subtree) after right-left rotation
	Node* RightLeftRotate(Node* parentP);



	//=========================//
	//========BEHAVIORS========//
	//=========================//

	//Prints the name associated with int idP in tree and "unsuccessful" otherwise
	void SearchId(int idP);

	//Prints the id associated with string nameP in tree and "unsuccessful" otherwise
	void SearchName(Node* nodeP, string nameP, bool& flag);

	//Prints all names in a preorder traversal
	void PrintPreOrder(Node* nodeP, string& outputP);

	//Prints all names in an inorder traversal
	void PrintInOrder(Node* nodeP, string& outputP);

	//Prints all names in a postorder traversal
	void PrintPostOrder(Node* nodeP, string& outputP);

	//Prints number of levels in the tree
	void PrintLevelCount();



	//=========================//
	//======CMD HANDLERS=======//
	//=========================//

	void Insert(const string parametersP);

	void Search(const string parametersP);

	void Remove(const string parametersP);

	void RemoveInOrder(const string parametersP);

	void PrintPreOrder();

	void PrintInOrder();

	void PrintPostOrder();



	//=========================//
	//=========HELPERS=========//
	//=========================//

	//Outputs a list of commands that can be used on the AVL Tree
	void PrintCommands();

	//Returns whether or not string n contains only alphabetical or space characters
	bool IsValidName(string nameP);

	//Returns whether or not string i contains only digits
	bool IsValidInt(string idP);

	//Returns whether or not string i contains exactly 8 digits
	bool IsValidId(string idP);
};