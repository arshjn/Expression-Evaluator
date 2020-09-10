// // File:    QueArr.h
// Project: CSIS 3400 Assignment 4
// Author:  Arsh Jain 
// History: Version 2.0 November 09, 2019
#include <iostream>
#include<string>
using namespace std;

template <class ItemType>
class QueArr
{
private:
	int maxSize;
	int front;
	int rear;
	ItemType* items;

public:
	QueArr();
	QueArr(int size);
	~QueArr();

	void makeEmpty();
	bool isEmpty() const;
	bool isFull() const;

	void add(ItemType item);
	void remove(ItemType& item);
	void print() const;


};

template <class ItemType>
QueArr<ItemType>::QueArr()
{
	maxSize = 100;
	front = maxSize - 1;
	rear = maxSize - 1;
	items = new ItemType[maxSize];
}

template <class ItemType>
QueArr<ItemType>::QueArr(int size)
{
	maxSize = size;
	front = maxSize - 1;
	rear = maxSize - 1;
	items = new ItemType[maxSize];
}

template <class ItemType>
QueArr<ItemType>::~QueArr()
{
	delete[] items;
}

template <class ItemType>
void QueArr<ItemType>::makeEmpty()
{
	front = maxSize - 1;
	rear = maxSize - 1;
}

template <class ItemType>
bool QueArr<ItemType>::isEmpty() const
{
	return (rear == front);
}

template <class ItemType>
bool QueArr<ItemType>::isFull() const
{
	return ((rear + 1) % maxSize == front);
}

template <class ItemType>
void QueArr<ItemType>::add(ItemType item)
{
	if (isFull())
		cout << "Queue is Full" << endl;
	else
	{
		rear = (rear + 1) % maxSize;
		items[rear] = item;
	}
}

template <class ItemType>
void QueArr<ItemType>::remove(ItemType& item)
{
	if (isEmpty())
		cout << "Queue is empty" << endl;
	else
	{
		front = (front + 1) % maxSize;
		item = items[front];
	}
}

template <class ItemType>
void QueArr<ItemType>::print() const
{
	if (isEmpty())
		cout << "Que is empty" << endl;
	else
	{
		//cout << front << ", " << length << endl;
		int temp = front;
		while (temp != rear)
		{
			temp = (temp + 1) % maxSize;
			cout << items[temp] << "  ";
		}
		cout << endl;
	}
}


