//BST.h
// Project: CSIS 3400 Assignment 7
//Author: Arsh Jain

#include <iostream>
using namespace std;
#include "QueArr.h"
#include "StackArr.h"
enum OrderType { PRE_ORDER, IN_ORDER, POST_ORDER };
template <class ItemType>
struct TreeNode
{
	ItemType info;
	TreeNode* left;
	TreeNode* right;
};

template <class ItemType>
class TreeType
{
public:
	TreeType();  //Constructor
	~TreeType(); //Destructor
	TreeType(const TreeType& origTree); //Copy COnstructor
	void operator = (const TreeType& origTree); // Assignment operator

	void makeEmpty();
	bool isEmpty() const;
	bool isFull() const;

	int getLength() const;

	ItemType getItem(ItemType item, bool& found);

	void addItem(ItemType item[], int l);

	//void addItemIter(ItemType item);

	void deleteItem(ItemType item);

	//void deleteItemIter(ItemType item);

	void resetTree(OrderType order);

	void printTree();

	ItemType getNextItem(OrderType order, bool& finished);
	void printPre();
	void printPost();
	void printIn();

private:
	TreeNode<ItemType>* root;

	StackArr<TreeNode<ItemType>*> ins;

	QueArr<ItemType> preQue;
	QueArr<ItemType> inQue;
	QueArr<ItemType> postQue;

	void destroy(TreeNode<ItemType>*& tree);
	void copyTree(TreeNode<ItemType>*& copy, const TreeNode<ItemType>* origTree);
	void deleteNode(TreeNode<ItemType>*& tree);
	void printNode(TreeNode<ItemType>*& tree);
	void Delete(TreeNode<ItemType>*& tree, ItemType item);
	int countNodes(TreeNode<ItemType>*& tree);
	void getPredecessor(TreeNode<ItemType>*& tree, ItemType& item);
	void retrieve(TreeNode<ItemType>*& tree, ItemType& item, bool& found);
	void insert(ItemType item);

	void findNode(TreeNode<ItemType>* tree, ItemType item, TreeNode<ItemType>*&
		nodePtr, TreeNode<ItemType>*& parentPtr);
	void preOrder(TreeNode<ItemType>* tree, QueArr<ItemType>& preQue);
	void inOrder(TreeNode<ItemType>* tree, QueArr<ItemType>& inQue);
	void postOrder(TreeNode<ItemType>* tree, QueArr<ItemType>& postQue);

};

template <class ItemType>
TreeType<ItemType>::TreeType()
{
	root = NULL;
}

template <class ItemType>
TreeType<ItemType>::~TreeType()
{
	destroy(root);
}


template<class ItemType>
void TreeType<ItemType>::addItem(ItemType item[], int l)
{
	for (int i = 0; i < l; i++)
		insert(item[i]);
	root = ins.Pop();
}

template<class ItemType>
void TreeType<ItemType>::insert(ItemType item)
{
	TreeNode<ItemType>* rootN, * ln, * rn;
	if (!(item == '+' || item == '-' || item == '*' || item == '/'))
	{
		rootN = new TreeNode<ItemType>;
		rootN->left = rootN->right = NULL;
		rootN->info = item;
		cout << "rootN : " << rootN->info << endl;;
		ins.Push(rootN);
	}
	else
	{
		rootN = new TreeNode<ItemType>;
		rootN->info = item;
		ln = ins.Pop();
		cout << "ln : " << ln->info << endl;;
		rn = ins.Pop();
		cout << "rn : " << rn->info << endl;

		rootN->left = ln;
		rootN->right = rn;

		ins.Push(rootN);
		cout << "rootN : " << rootN->info << endl;;

	}
}


template <class ItemType>
void TreeType<ItemType>::destroy(TreeNode<ItemType>*& tree)
{
	if (tree != NULL)
	{
		destroy(tree->left);
		destroy(tree->right);
		delete tree;
	}
}

template <class ItemType>
TreeType<ItemType>::TreeType(const TreeType& origTree)
{
	copyTree(root, origTree);
}

template<class ItemType>
void TreeType<ItemType>::operator=(const TreeType& origTree)
{
	if (&origTree == this)
		return;
	destroy(root);
	copyTree(root, origTree.root);
}

template<class ItemType>
void TreeType<ItemType>::makeEmpty()
{
	destroy(root);
	root = NULL;
}

template<class ItemType>
inline bool TreeType<ItemType>::isEmpty() const
{

	return root == NULL;
}

template<class ItemType>
bool TreeType<ItemType>::isFull() const
{
	TreeNode<ItemType>* location;
	try
	{
		location = new TreeNode<ItemType>;
		delete location;
		return false;
	}
	catch (std::bad_alloc)
	{
		return true;
	}
}

template<class ItemType>
inline int TreeType<ItemType>::getLength() const
{
	return countNodes(root);
}

template<class ItemType>
ItemType TreeType<ItemType>::getItem(ItemType item, bool& found)
{
	retrieve(root, item, found);
	return item;
}

/*template<class ItemType>
void TreeType<ItemType>::addItemIter(ItemType item)
{
	TreeNode<ItemType>* newNode;
	TreeNode<ItemType>* nodePtr;
	TreeNode<ItemType>* parentPtr;

	newNode = new TreeNode<ItemType>;
	newNode->info = item;
	newNode->left = NULL;
	newNode->right = NULL;

	findNode(root, item, nodePtr, parentPtr);
	if (parentPtr == NULL)
		root = newNode;
	else if (item < parentPtr->info)
		parentPtr->left = newNode;
	else
		parentPtr->right = newNode;
}
*/

template<class ItemType>
void TreeType<ItemType>::deleteItem(ItemType item)
{
	Delete(root, item);
}

/*template<class ItemType>
void TreeType<ItemType>::deleteItemIter(ItemType item)
{
	TreeNode<ItemType>* nodePtr;
	TreeNode<ItemType>* parentPtr;
	findNode(root, item, nodePtr, parentPtr);
	if (nodePtr == root)
		deleteNode(root);
	else
	{
		if (parentPtr->left == nodePtr)
			deleteNode(parentPtr->left);
		else
			deleteNode(parentPtr->right);
	}

}
*/
template<class ItemType>
void TreeType<ItemType>::resetTree(OrderType order)
{
	switch (order)
	{
	case PRE_ORDER: preOrder(root, preQue);
		break;
	case IN_ORDER: inOrder(root, inQue);
		break;
	case POST_ORDER: postOrder(root, postQue);
		break;
	}
}

template<class ItemType>
void TreeType<ItemType>::printTree()
{
	printNode(root);
	cout << endl;
}

template<class ItemType>
ItemType TreeType<ItemType>::getNextItem(OrderType order, bool& finished)
{
	ItemType item;
	finished = false;
	switch (order)
	{
	case PRE_ORDER: preQue.remove(item);
		if (preQue.isEmpty())
			finished = true;
		break;
	case IN_ORDER: inQue.remove(item);
		if (inQue.isEmpty())
			finished = true;
		break;
	case POST_ORDER: postQue.remove(item);
		if (postQue.isEmpty())
			finished = true;
		break;
	}
	return item;
}

template <class ItemType>
void TreeType<ItemType>::copyTree(TreeNode<ItemType>*& copy, const TreeNode<ItemType>* origTree)
{
	if (origTree == NULL)
		copy = NULL;
	else
	{
		copy = new TreeNode<ItemType>;
		copy->info = origTree->info;

		copyTree(copy->left, origTree->left);
		copyTree(copy->right, origTree->right);
	}
}

template<class ItemType>
void TreeType<ItemType>::deleteNode(TreeNode<ItemType>*& tree)
{
	ItemType data;
	TreeNode<ItemType>* tempPtr;
	tempPtr = tree;
	if (tree->left == NULL)
	{
		tree = tree->right;
		delete tempPtr;
	}
	else if (tree->right == NULL)
	{
		tree = tree->left;
		delete tempPtr;
	}
	else
	{
		getPredecessor(tree->left, data);
		tree->info = data;
		Delete(tree->left, data);//Delete predecessor node
	}
}

template<class ItemType>
void TreeType<ItemType>::printNode(TreeNode<ItemType>*& tree)
{
	if (tree == root)
		cout << "roots info " << tree->info << endl;
	if (tree != NULL)
	{
		printNode(tree->left);
		cout << tree->info << " ";
		printNode(tree->right);
	}
}

template<class ItemType>
void TreeType<ItemType>::Delete(TreeNode<ItemType>*& tree, ItemType item)
{
	if (item < tree->info)
		Delete(tree->left, item);
	else if (item > tree->info)
		Delete(tree->right, item);
	else
		deleteNode(tree);
}

template<class ItemType>
int TreeType<ItemType>::countNodes(TreeNode<ItemType>*& tree)
{
	if (tree == NULL)
		return 0;
	else
		return (countNodes(tree->left) + countNodes(tree->right)) + 1;
}

template<class ItemType>
void TreeType<ItemType>::getPredecessor(TreeNode<ItemType>*& tree, ItemType& item)
{
	while (tree->right != NULL)
		tree = tree->right;
	item = tree->info;
}

template<class ItemType>
void TreeType<ItemType>::retrieve(TreeNode<ItemType>*& tree, ItemType& item, bool& found)
{
	if (tree == NULL)
		found = false;
	else if (item < tree->info)
		retrieve(tree->left, item, found);
	else if (item > tree->info)
		retrieve(tree->right, item, found);
	else
	{
		item = tree->info;
		found = true;
	}
}


template<class ItemType>
void TreeType<ItemType>::findNode(TreeNode<ItemType>* tree, ItemType item, TreeNode<ItemType>*& nodePtr, TreeNode<ItemType>*& parentPtr)
{
	nodePtr = tree;
	parentPtr = NULL;
	bool found = false;
	while (nodePtr != NULL && !found)
	{
		if (item < nodePtr->info)
		{
			parentPtr = nodePtr;
			nodePtr = nodePtr->left;
		}
		else if (item > nodePtr->info)
		{
			parentPtr = nodePtr;
			nodePtr = nodePtr->right;
		}
		else
			found = true;
	}
}

template<class ItemType>
void TreeType<ItemType>::preOrder(TreeNode<ItemType>* tree, QueArr<ItemType>& preQue)
{
	if (tree != NULL)
	{
		preQue.add(tree->info);
		preOrder(tree->left, preQue);
		preOrder(tree->right, preQue);
	}
}

template<class ItemType>
void TreeType<ItemType>::inOrder(TreeNode<ItemType>* tree, QueArr<ItemType>& inQue)
{
	if (tree != NULL)
	{
		inQue.add('(');
		inOrder(tree->left, inQue);
		inQue.add(tree->info);
		inOrder(tree->right, inQue);
		inQue.add(')');

	}
}

template<class ItemType>
void TreeType<ItemType>::postOrder(TreeNode<ItemType>* tree, QueArr<ItemType>& postQue)
{
	if (tree != NULL)
	{
		postOrder(tree->left, postQue);
		postOrder(tree->right, postQue);
		postQue.add(tree->info);
	}
}

template<class ItemType>
void TreeType<ItemType>::printPre()
{
	preOrder(root, preQue);
	preQue.print();
}

template<class ItemType>
void TreeType<ItemType>::printPost()
{
	postOrder(root, postQue);
	postQue.print();
}

template<class ItemType>
void TreeType<ItemType>::printIn()
{
	inOrder(root, inQue);
	inQue.print();
}
