#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>

template<class T>
struct sgListNode
{
	sgListNode() {};
	sgListNode(T argData) : data(argData) {};

	T data;
	sgListNode<T>* nextNode = nullptr;
};

template<class T>
class sgList
{
private:
	unsigned int size{ 0 };
	sgListNode<T>* front{ nullptr };

public:
	sgListNode<T>* operator[] (unsigned const int);

	// adds a node to the end of the list
	void PushBack(T* argData)
	{
		sgListNode<T>* newBack = new sgListNode<T>(*argData);

		if (front != nullptr)
		{
			sgListNode<T>* tempNode = front;

			while (tempNode->nextNode != nullptr)
			{
				tempNode = tempNode->nextNode;
			}

			tempNode->nextNode = newBack;
		}
		else
		{
			front = newBack;
		}


		size++;
	}

	// adds a node to the front of the list
	void PushFront(T* argData)
	{
		sgListNode<T>* newFront = new sgListNode<T>(*argData);

		if (front != nullptr)
		{
			newFront->nextNode = front;
		}

		front = newFront;

		size++;
	}

	// Removes a node from the end of the list, and also deleting it freeing the memory
	void PopBack()
	{
		sgListNode<T>* tempNode = front;
		sgListNode<T>* previousNode = nullptr;

		if (tempNode != nullptr)
		{
			while (tempNode->nextNode != nullptr)
			{
				previousNode = tempNode;
				tempNode = tempNode->nextNode;
			}

			delete tempNode;

			if (previousNode != nullptr)
				previousNode->nextNode = nullptr;

			size--;
		}
	}

	// Removes a node from the front of the list, and also deleting it freeing the memory
	void PopFront()
	{
		if (front != nullptr)
		{
			sgListNode<T>* tempFront = front->nextNode;

			delete front;

			front = tempFront;
			size--;
		}
	}

	unsigned int Size() const
	{
		return size;
	}
};

// Allows for the square bracket operator to be used to search for a node at a specific point
template<class T>
inline sgListNode<T>* sgList<T>::operator[](unsigned const int argElementID)
{
	unsigned int counter{ 0 };
	sgListNode<T>* node{ front };

	if (node != nullptr)
	{
		while (counter < argElementID && node->nextNode != nullptr)
		{
			node = node->nextNode;
			counter++;
		}
	}

	return node;
}

