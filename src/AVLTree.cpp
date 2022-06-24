#include "AVLTree.h"

AVLTree::Node::Node() : id(0), name(""), left(NULL), right(NULL), height(1) {}

AVLTree::AVLTree() : root(NULL) {}

AVLTree::~AVLTree() 
{ 
	RemoveAll(root); 
}

AVLTree::Node* AVLTree::Search(Node* nodeP, int idP) const
{
	if (!nodeP)
		return NULL;
	else if (idP == nodeP->id)
		return nodeP;
	else if (idP < nodeP->id)
		return Search(nodeP->left, idP);
	else
		return Search(nodeP->right, idP);
}

void AVLTree::SearchNInOrder(Node* nodeP, int n, int& count, Node*& resultP)
{
	if (nodeP == NULL)
		return;

	if (count < n)
	{
		SearchNInOrder(nodeP->left, n, count, resultP);

		count++;
		if (count == n)
		{
			resultP = nodeP;
			return;
		}

		SearchNInOrder(nodeP->right, n, count, resultP);
	}
}

int AVLTree::CalcHeight(Node* nodeP) const
{
	if (!nodeP)
		return 0;

	int leftheight = 0;
	if (nodeP->left)
		leftheight = nodeP->left->height;

	int rightheight = 0;
	if (nodeP->right)
		rightheight = nodeP->right->height;

	return 1 + max(leftheight, rightheight);
}

int AVLTree::GetBalanceFactor(Node* nodeP) const
{
	if (!nodeP)
		return 0;

	int leftheight = 0;
	if (nodeP->left)
		leftheight = nodeP->left->height;

	int rightheight = 0;
	if (nodeP->right)
		rightheight = nodeP->right->height;

	return (leftheight - rightheight);
}

AVLTree::Node* AVLTree::FindLeftmost(Node* rootP) const
{
	if (!rootP)
		return NULL;
	if (rootP->left)
		return FindLeftmost(rootP->left);
	return rootP;
}

AVLTree::Node* AVLTree::Insert(Node* nodeP, Node* rootP)
{
	//Making insertion
	if (rootP == NULL)
		return nodeP;

	if (nodeP->id < rootP->id)
		rootP->left = Insert(nodeP, rootP->left);
	else if (nodeP->id > rootP->id)
		rootP->right = Insert(nodeP, rootP->right);


	//Updating rest of path....
	rootP->height = CalcHeight(rootP);

	//Checking balance factors; Rotating as necessary
	int bfroot = GetBalanceFactor(rootP);
	int bfleft = GetBalanceFactor(rootP->left);
	int bfright = GetBalanceFactor(rootP->right);

	//Left Left Case
	if (bfroot == 2 && bfleft == 1)
		rootP = RightRotate(rootP);
	//Right Right Case
	if (bfroot == -2 && bfright == -1)
		rootP = LeftRotate(rootP);
	//Left Right Case
	if (bfroot == 2 && bfleft == -1)
		rootP = LeftRightRotate(rootP);
	//Right Left Case
	if (bfroot == -2 && bfright == 1)
		rootP = RightLeftRotate(rootP);

	return rootP;
}

AVLTree::Node* AVLTree::Remove(Node* rootP, int idP)
{
	if (rootP == NULL)
		return rootP;

	if (idP < rootP->id)
		rootP->left = Remove(rootP->left, idP);
	else if (idP > rootP->id)
		rootP->right = Remove(rootP->right, idP);
	else
	{
		//Two children case
		if (rootP->left != NULL && rootP->right != NULL)
		{
			Node* replacement = FindLeftmost(rootP->right);
			rootP->id = replacement->id;
			rootP->name = replacement->name;
			rootP->right = Remove(rootP->right, replacement->id);
		}
		//Left child only case
		else if (rootP->left != NULL)
		{
			Node* temp = rootP->left;
			*rootP = *temp;
			delete temp;
		}
		//Right child only case
		else if (rootP->right != NULL)
		{
			Node* temp = rootP->right;
			*rootP = *temp;
			delete temp;
		}
		//Leaf case
		else
		{
			Node* temp = rootP;
			rootP = NULL;
			delete temp;
		}
	}

	//Update path
	if (rootP != NULL)
		rootP->height = CalcHeight(rootP);

	return rootP;
}

void AVLTree::RemoveAll(Node* nodeP)
{
	if (nodeP != NULL)
	{
		RemoveAll(nodeP->left);
		RemoveAll(nodeP->right);
		Node* temp = nodeP;
		nodeP = NULL;
		delete temp;
	}
}

AVLTree::Node* AVLTree::RightRotate(Node* parentP)
{
	Node* newroot = parentP->left;
	parentP->left = newroot->right;
	newroot->right = parentP;
	parentP->height = CalcHeight(parentP);
	newroot->height = CalcHeight(newroot);
	return newroot;
}

AVLTree::Node* AVLTree::LeftRotate(Node* parentP)
{
	Node* newroot = parentP->right;
	parentP->right = newroot->left;
	newroot->left = parentP;
	parentP->height = CalcHeight(parentP);
	newroot->height = CalcHeight(newroot);
	return newroot;
}

AVLTree::Node* AVLTree::LeftRightRotate(Node* parentP)
{
	parentP->left = LeftRotate(parentP->left);
	return RightRotate(parentP);
}

AVLTree::Node* AVLTree::RightLeftRotate(Node* parentP)
{
	parentP->right = RightRotate(parentP->right);
	return LeftRotate(parentP);
}

void AVLTree::SearchId(int idP)
{
	Node* node = Search(root, idP);
	if (node != NULL)
		cout << node->name << endl;
	else
		cout << "unsuccessful" << endl;
}

void AVLTree::SearchName(Node* nodeP, string nameP, bool& flag)
{
	if (nodeP == NULL)
		return;

	if (nodeP->name == nameP)
	{
		flag = true;
		cout << nodeP->id << endl;
	}
	SearchName(nodeP->left, nameP, flag);
	SearchName(nodeP->right, nameP, flag);
}

void AVLTree::PrintPreOrder(Node* nodeP, string& outputP)
{
	if (nodeP != NULL)
	{
		outputP += nodeP->name + ", ";
		PrintPreOrder(nodeP->left, outputP);
		PrintPreOrder(nodeP->right, outputP);
	}
}

void AVLTree::PrintInOrder(Node* nodeP, string& outputP)
{
	if (nodeP != NULL)
	{
		PrintInOrder(nodeP->left, outputP);
		outputP += nodeP->name + ", ";
		PrintInOrder(nodeP->right, outputP);
	}
}

void AVLTree::PrintPostOrder(Node* nodeP, string& outputP)
{
	if (nodeP != NULL)
	{
		PrintPostOrder(nodeP->left, outputP);
		PrintPostOrder(nodeP->right, outputP);
		outputP += nodeP->name + ", ";
	}
}

void AVLTree::PrintLevelCount()
{
	cout << (root->height) << endl;
}

void AVLTree::Insert(const string parametersP)
{
	//Cleaning up parameters
	stringstream stream(parametersP.substr(1, parametersP.length() - 1));

	string newname;
	getline(stream, newname, '\"');

	string newid;
	getline(stream, newid);
	newid = newid.substr(1, newid.length());

	if (IsValidName(newname) && IsValidId(newid) && !Search(root, stoi(newid)))
	{
		Node* newnode = new Node();
		newnode->id = stoi(newid);
		newnode->name = newname;
		root = Insert(newnode, root);
		cout << "successful" << endl;
	}
	else
		cout << "unsuccessful" << endl;
}

void AVLTree::Search(const string parametersP)
{
	if (parametersP[0] == '\"')
	{
		string newname = parametersP.substr(1, parametersP.length() - 2);

		if (IsValidName(newname))
		{
			bool flag = false;
			SearchName(root, newname, flag);
			if (flag == false)
				cout << "unsuccessful" << endl;
		}
		else
			cout << "unsuccessful" << endl;
	}
	else
	{
		string newid = parametersP;

		if (IsValidId(newid))
			SearchId(stoi(newid));
		else
			cout << "unsuccessful" << endl;
	}
}

void AVLTree::Remove(const string parametersP)
{
	string newid = parametersP;
	if (IsValidId(newid) && Search(root, stoi(newid)))
	{
		root = Remove(root, stoi(newid));
		cout << "successful" << endl;
	}
	else
		cout << "unsuccessful" << endl;
}

void AVLTree::RemoveInOrder(const string parametersP)
{
	string n = parametersP;
	if (IsValidInt(n) && root != NULL)
	{
		Node* result = NULL;
		int count = -1;
		SearchNInOrder(root, stoi(n), count, result);
		if (result == NULL)
		{
			cout << "unsuccessful" << endl;
		}
		else
		{
			root = Remove(root, result->id);
			cout << "successful" << endl;
		}
	}
	else
	{
		cout << "unsuccessful" << endl;
	}
}

void AVLTree::PrintPreOrder()
{
	string output;
	PrintPreOrder(root, output);
	output = output.substr(0, output.length() - 2);
	cout << output << endl;
}

void AVLTree::PrintInOrder()
{
	string output;
	PrintInOrder(root, output);
	output = output.substr(0, output.length() - 2);
	cout << output << endl;
}

void AVLTree::PrintPostOrder()
{
	string output;
	PrintPostOrder(root, output);
	output = output.substr(0, output.length() - 2);
	cout << output << endl;
}

void AVLTree::PrintCommands()
{
	//im putting this all here just to hide how ugly it is lol
	cout << "====COMMAND LIST====" << endl;
	cout << "insert \"[name]\" [id]\nremove [id]\nremoveInOrder [amount]\nsearch [id]\nsearch \"[name]\"\nprintLevelcount\nprintPreorder\nprintInorder\nprintPostorder\n====================\n" << endl;
}

bool AVLTree::IsValidName(string nameP)
{
	int j = 0;
	while (nameP[j])
	{
		if (!isalpha(nameP[j]) && !isspace(nameP[j]))
			return false;
		j++;
	}
	return true;
}

bool AVLTree::IsValidInt(string idP)
{
	int j = 0;
	while (idP[j])
	{
		if (!isdigit(idP[j]))
			return false;
		j++;
	}
	return true;
}

bool AVLTree::IsValidId(string idP)
{
	return (IsValidInt(idP) && idP.length() == 8);
}

