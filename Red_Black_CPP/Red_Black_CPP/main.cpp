#include "Tree.h"
#include <random>
#include <ctime>

int getRandomNum(int min, int max)
{
	return (rand() % (max - min)) + min;
}

int main()
{
	Tree<int> tree = Tree<int>();

	srand(time(NULL));


	

	for (int i = 0; i < 23; i++)
	{
		tree.Add(getRandomNum(0, 100));
	}

	return 0;
}