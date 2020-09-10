//StackArr.h
// Project: CSIS 3400 Assignment 7
//Author: Dr. Ajoy Kumar, Arsh Jain

#include <iostream>

using namespace std;

template <class ItemType>
class StackArr
{
public:
	StackArr();			//Empty constructor
	StackArr(int max);  //Constructor which takes a size

	bool IsEmpty() const;
	bool IsFull() const;

	void Push(ItemType item);
	ItemType Pop();

	ItemType Top() const;
	void PrintStack();

private:
	int top;
	int maxStack;
	ItemType* items;
	int length;

};

template <class ItemType>
StackArr<ItemType>::StackArr()
{
	maxStack = 100;
	top = -1;
	items = new ItemType[maxStack];
	length = 0;
}

template <class ItemType>
StackArr<ItemType>::StackArr( int max)
{
	maxStack = max;
	top = -1;
	items = new ItemType[maxStack];
	length = 0;
}

template <class ItemType>
bool StackArr<ItemType>::IsEmpty() const
{
	return (top == -1);
}

template <class ItemType>
bool StackArr<ItemType>::IsFull() const
{
	return (top == maxStack - 1);
}

template <class ItemType>
void StackArr<ItemType>::Push(ItemType item)
{
	if (IsFull())
	{
		cout << "The stack is full and item cannot be pushed";
	}
	else
	{
		top++;
		items[top] = item;
		length++;
	}
}

template <class ItemType>
ItemType StackArr<ItemType>::Pop()
{
	if(IsEmpty())
	{
		cout << "The stack is empty and item cannot be popped";
		return 0;
	}
	else
	{
		top--;
		length--;
		return items[top + 1];
	}
}

template <class ItemType>
ItemType StackArr<ItemType>::Top() const
{
	if (IsEmpty())
	{
		cout << "The stack is empty and no item on top";
	}
	else
		return items[top];

}

template <class ItemType>
void StackArr<ItemType>::PrintStack()
{
	if (length == 0)
		cout << "Stack is empty" << endl;
	else
	{
		for (int i = 0; i < length; i++)
			cout << items[i]->info << ", ";
		cout << endl;
	}

}
 


