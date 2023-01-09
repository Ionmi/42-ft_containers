#include "../includes/containers/stack.hpp"
#include <iostream>

using ft::stack;
using std::cout;

template <typename T>
class MutantStack : public stack<T>
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

	typedef typename stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

template <class T>
void printAttributes(MutantStack<T> mystack)
{
	for (typename MutantStack<T>::iterator it = mystack.begin(); it != mystack.end(); it++)
		cout << *it << "\n";
	if (mystack.size() > 0)
		cout << mystack.top() << "\n";
	cout << "****************************\n";
	cout << "size: " << mystack.size() << "\n";
	cout << "empty: " << (mystack.empty() == 1 ? "true" : "false") << "\n";
	cout << "****************************\n";
}

int main()
{
	cout << "*****STACK TESTS*****\n";
	typedef MutantStack<int> intStack;

	cout << "CONSTRUCTORS:\n";

	intStack mystack;
	cout << "mystack.push()\n";
	for (int i = 0; i < 20; i++)
		mystack.push(i);
	printAttributes(mystack);
	{
		cout << "other = mystack\n";
		intStack other = mystack;
		printAttributes(other);
	}
	cout << "other(mystack)\n";
	intStack other(mystack);
	printAttributes(other);
	cout << "if (mystack.size() > 0) mystack.pop()\n";
	for (int i = 0; i < 15; i++)
	{
		if (mystack.size() > 0)
			mystack.pop();
	}
	printAttributes(mystack);

	if (mystack.size() > 0)
	{
		cout << "\nELEMENT ACCES:\n";
		cout << "mystack.top() -> ";
		cout << mystack.top() << "\n";
	}

	cout << "\nNON-MEMBER FUNCTIONS:\n";
	cout << "mystack == other -> " << (mystack == other) << "\n";
	cout << "mystack == mystack -> " << (mystack == mystack) << "\n";
	cout << "mystack != other -> " << (mystack != other) << "\n";
	cout << "mystack != mystack -> " << (mystack != mystack) << "\n";
	cout << "mystack < other -> " << (mystack < other) << "\n";
	cout << "mystack < mystack -> " << (mystack < mystack) << "\n";
	cout << "mystack <= other -> " << (mystack <= other) << "\n";
	cout << "mystack <= mystack -> " << (mystack <= mystack) << "\n";
	cout << "mystack > other -> " << (mystack > other) << "\n";
	cout << "mystack > mystack -> " << (mystack > mystack) << "\n";
	cout << "mystack >= other -> " << (mystack >= other) << "\n";
	cout << "mystack >= mystack -> " << (mystack >= mystack) << "\n";
	
	cout << "\nPERFORMANCE:\n";
	for (int i = 0; i < 150000; i++)
		mystack.push(i);
	printAttributes(mystack);

	return 0;
}