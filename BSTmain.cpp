//BSTmain.cpp
// Project: CSIS 3400 Assignment 7
//Author: Arsh Jain

#include "BST.h"

int main()
{
	//Sample Implementation
	TreeType<char> charBST;
	char ch[] = "ABC+*";
	charBST.addItem(ch ,5);

	charBST.printTree();
	
	cout << "\nPostfix print: \n";
	charBST.printPost();
	
	cout << "\nPrefix Print: \n";
	charBST.printPre();

	cout << "\nInfix Print: \n";
	charBST.printIn();
	

	system("PAUSE");
	return 0;
}