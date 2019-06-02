#pragma once
#include "Node.h"

template <typename T>
class Tree
{
public:
	int count = 0;
	Node<T>* Root;
	Tree()
	{
		count = 0;
		Root = nullptr;
	}
	void Add(T value);
	bool Remove(T value);
private:
	const int& Count = count;
	bool IsRed(Node<T>* node);
	Node<T>* add(Node<T>* node, T value);
};

template <typename T>
void Tree<T>::Add(T value)
{
	Root = add(Root, value);
	Root->IsBlack = true;
}

template<typename T>
bool Tree<T>::IsRed(Node<T>* node)
{
	if (node = nullptr)
	{
		return false;
	}
	
	return !node->IsBlack;
}

template <typename T>
Node<T>* Tree<T>::add(Node<T> *node, T value)
{
	if (node = nullptr)
	{
		return new Node<T>(value);
	}
	if (IsRed(node->LeftChild.get()) & IsRed(node->RightChild.get()))
	{
		//flip the color of the node
	}
	if (value < node->data)
	{
		add(node->LeftChild.get(), value);
	}
	if (value > node->data)
	{
		add(node->RightChild.get(), value);
	}
	else
	{
		if (IsRed(node->RightChild.get()))
		{
			//rotate the node left
		}
		if (IsRed(node->LeftChild.get()) && IsRed(node->LeftChild.get()->LeftChild.get()))
		{
			//rotate the node right
		}

		return node;
	}


}

template <typename T>
bool Tree<T>::Remove(T value)
{
	int initCount = 0;
	if (Root != nullptr)
	{
		//recursively call private remove
		if (Root != nullptr)
		{
			Root->IsBlack = true;
		}
	}
	
	return initCount != count;
}