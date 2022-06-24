#include "AVLTree.h"
#include <conio.h>

int main()
{
	AVLTree* tree = new AVLTree;

	//Print command list
	tree->PrintCommands();

	//Get command count
	cout << "Number of commands: ";
	string cmdcount;
	getline(cin, cmdcount);
	for (int i = 0; i < stoi(cmdcount); i++)
	{
		//Get command from line
		cout << ">";
		string cmd;
		getline(cin, cmd);

		//Split command
		stringstream stream(cmd);
		getline(stream, cmd, ' ');

		string parameters;
		getline(stream, parameters);

		//Decide what to do
		if (cmd == "insert")
			tree->Insert(parameters);
		else if (cmd == "removeInorder")
			tree->RemoveInOrder(parameters);
		else if (cmd == "remove")
			tree->Remove(parameters);
		else if (cmd == "search")
			tree->Search(parameters);
		else if (cmd == "printInorder")
			tree->PrintInOrder();
		else if (cmd == "printPreorder")
			tree->PrintPreOrder();
		else if (cmd == "printPostorder")
			tree->PrintPostOrder();
		else if (cmd == "printLevelCount")
			tree->PrintLevelCount();
		else
			cout << "unsuccessful - bad command" << endl;
		cout << endl;
	}

	cout << "Press any key to exit..." << endl;
	_getch();

	delete tree;
	return 0;
}