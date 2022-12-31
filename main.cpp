#include "includes/containers/vector.hpp"
#include "includes/containers/stack.hpp"
#include "includes/containers/map.hpp"
#include "includes/RedBlackTree.hpp"

#include <iostream>
#include <vector>
#include <map>
// #include <memory>
using namespace ft::rbt;
using namespace std;

// reinterpret_cast<uintptr_t>(ptr);
// reinterpret_cast<Data *>(raw);

int main()
{
	RBT<int, std::less<int> > tree;

	typedef pair<int, string> mypair;
	mypair mipair(1, "holaaa");
	
	tree.insertNode(0);
	tree.insertNode(1, reinterpret_cast<uintptr_t>(&mipair));
	tree.insertNode(2);
	tree.insertNode(3);
	tree.insertNode(4);
	tree.insertNode(5);
	tree.insertNode(6);
	tree.insertNode(7);
	tree.insertNode(8);
	// tree.printTree();
	// cout << "-------------------------------------\n";
	tree.insertNode(5);
	tree.printTree();
	uintptr_t hey = tree.findNode(1);
	if(hey == 0)
		return 0;
	mypair hola = *reinterpret_cast<mypair *>(hey);
	cout << "first:" << hola.first << " second:" << hola.second << "\n";
		
	return 0;
}
// operaotrs
//  {
//  	std::vector<int> myvector(1, 1);
//  	std::vector<int> myvector2(5, 5);
//  	cout << "==: " << (myvector == myvector2) << '\n';
//  }
//  {
//  	ft::vector<int> myvector(1, 1);
//  	ft::vector<int> myvector2(5, 5);
//  	cout << "==: " << (myvector == myvector2) << '\n';
//  }

/*#include <iostream>
#include <string>
#include <deque>
#if 1 // CREATE A REAL STL EXAMPLE
#include <map>
#include <stack>
#include <vector>
namespace ft = std;
#else
#include <map.hpp>
#include <stack.hpp>
#include <vector.hpp>
#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};

#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template <typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T> &src) { *this = src; }
	MutantStack<T> &operator=(const MutantStack<T> &rhs)
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	ft::stack<Buffer, std::deque<int>> stack_deq_buffer;
	ft::map<int, int> map_int;

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	ft::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" << std::endl;
		}
	}
	catch (const std::exception &e)
	{
		// NORMAL ! :P
	}

	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
	}

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	{
		ft::map<int, int> copy = map_int;
	}
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;
	return (0);
}
*/