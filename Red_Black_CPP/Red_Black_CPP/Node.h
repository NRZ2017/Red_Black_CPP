#pragma once
#include <memory>

template <typename T>
class Node
{
public:
	T data;
	std::unique_ptr<Node<T>> LeftChild;
	std::unique_ptr<Node<T>> RightChild;
	bool IsBlack;

	Node(T Data)
	{
		this->data = Data;
		IsBlack = false;
		LeftChild = nullptr;
		RightChild = nullptr;
	}
private:

};