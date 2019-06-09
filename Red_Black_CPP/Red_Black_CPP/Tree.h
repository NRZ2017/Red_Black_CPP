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
	Node<T>* remove(Node<T>* node, T value);
	void FlipColor(Node<T>* node);
	Node<T>* RotateLeft(Node<T>* node);
	Node<T>* RotateRight(Node<T>* node);
	Node<T>* MoveRedLeft(Node<T>* node);
	Node<T>* MoveRedRight(Node<T>* node);
	Node<T>* GetMinimum(Node<T>* node);
	Node<T>* Fixup(Node<T>* node);
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
	if (node == nullptr)
	{
		return false;
	}
	
	return !node->IsBlack;
}

template <typename T>
Node<T>* Tree<T>::add(Node<T> *node, T value)
{
	if (node == nullptr)
	{
		return new Node<T>(value);
	}
	if (IsRed(node->LeftChild.get()) && IsRed(node->RightChild.get()))
	{
		FlipColor(node);
	}
	if (value < node->data)
	{
		node->LeftChild = std::move(add(node->LeftChild.get(), value));
	}
	if (value > node->data)
	{
		add(node->RightChild.get(), value);
	}

		if (IsRed(node->RightChild.get()))
		{
			RotateLeft(node);
		}
		if (IsRed(node->LeftChild.get()) && IsRed(node->LeftChild.get()->LeftChild.get()))
		{
			RotateRight(node);
		}

		return node;



}

template <typename T>
bool Tree<T>::Remove(T value)
{
	int initCount = 0;
	if (Root != nullptr)
	{
		Root = remove(Root, value);
		if (Root != nullptr)
		{
			Root->IsBlack = true;
		}
	}
	
	return initCount != count;
}

template <typename T>
Node<T>* Tree<T>::remove(Node<T>* node, T value)
{
	if (value < node->data)
	{
		if (node->LeftChild != nullptr)
		{
			if (!IsRed(node->LeftChild.get()) && !IsRed(node->LeftChild.get()->LeftChild.get()))
			{
				node = MoveRedLeft(node);
			}

			node->LeftChild = std::make_unique<Node<T>>(remove(node->LeftChild.get(), value));
		}
	}
	else
	{
		if (IsRed(node->LeftChild.get()))
		{
			node = RotateRight(node);
		}
		if (value == node->data && node->RightChild == nullptr)
		{
			count--;
			return nullptr;
		}
		if (node->RightChild != nullptr)
		{
			if (!IsRed(node->RightChild.get()) && !IsRed(node->RightChild.get()->LeftChild.get()))
			{
				node = MoveRedRight(node);
			}
			if (value == node->data)
			{
				Node<T>* min = GetMinimum(node->RightChild.get());
				node->data = min->data;
				node->RightChild = std::make_unique<Node<T>>(remove(node->RightChild.get(), min->data));
			}
			else
			{
				node->RightChild = std::make_unique<Node<T>>(remove(node->RightChild.get(), value));
			}
		}
	}

	return Fixup(node);
}

template<typename T>
void Tree<T>::FlipColor(Node<T>* node)
{
	node->IsBlack = !node->IsBlack;
	node->LeftChild->IsBlack = !node->LeftChild->IsBlack;
	node->RightChild->IsBlack = !node->RightChild->IsBlack;
}

template<typename T>
Node<T>* Tree<T>::RotateLeft(Node<T>* node)
{
	Node<T>* temp = node->RightChild.get();
	node->RightChild = std::move(temp->LeftChild);
	temp->LeftChild = std::make_unique<Node<T>>(node);

	temp->IsBlack = node->IsBlack;
	node->IsBlack = false;
	return temp;
}

template <typename T>
Node<T>* Tree<T>::RotateRight(Node<T>* node)
{
	Node<T>* temp = node->LeftChild.get();
	node->LeftChild = std::move(temp->RightChild);
	temp->RightChild = std::make_unique<Node<T>>(node);

	temp->IsBlack = node->IsBlack;
	node->IsBlack = false;
	return temp;
}

template <typename T>
Node<T>* Tree<T>::MoveRedLeft(Node<T>* node)
{
	FlipColor(node);
	if(IsRed(node->RightChild.get()->LeftChild.get()))
	{
		node->RightChild = std::make_unique<Node<T>>(RotateRight(node->RightChild.get()));
		node = RotateLeft(node);

		FlipColor(node);

		if (IsRed(node->RightChild.get()->RightChild.get()))
		{
			node->RightChild = std::make_unique<Node<T>>(RotateLeft(node->RightChild.get()));
		}
	}

	return node;
}

template <typename T>
Node<T>* Tree<T>::MoveRedRight(Node<T>* node)
{
	FlipColor(node);
	if (IsRed(node->LeftChild.get()->LeftChild.get()))
	{
		node = RotateRight(node);
		FlipColor(node);
	}

	return node;
}

template <typename T>
Node<T>* Tree<T>::GetMinimum(Node<T>* node)
{
	Node<T>* temp = node;
	while (temp->LeftChild != nullptr)
	{
		temp = temp->LeftChild.get();
	}

	return temp;
}

template <typename T>
Node<T>* Tree<T>::Fixup(Node<T>* node)
{
	/*if (IsRed(node->RightChild.get()))
	{
		node = RotateLeft(node);
	}
	if (IsRed(node->LeftChild.get()) && IsRed(node->LeftChild.get()->LeftChild.get()))
	{
		node = RotateRight(node);
	}
	if (IsRed(node->LeftChild.get()) && IsRed(node->RightChild.get()))
	{
		FlipColor(node);
	}
	if (node->LeftChild != nullptr && IsRed(node->LeftChild.get()->RightChild.get()) && IsRed(node->LeftChild.get()->LeftChild.get()))
	{
		node->LeftChild = std::make_unique<Node<T>>(RotateLeft(node->LeftChild.get()));
		if (IsRed(node->LeftChild.get()))
		{
			node = RotateRight(node);
		}
	}

	return node;*/
}