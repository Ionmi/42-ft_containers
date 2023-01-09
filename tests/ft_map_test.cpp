#include "../includes/containers/map.hpp"
#include <iostream>

using ft::map;
using std::cout;

template <class Key, class T>
void printAttributes(map<Key, T> mymap)
{
	for (typename map<Key, T>::iterator it = mymap.begin(); it != mymap.end(); it++)
		cout << "key: " << it->first << ", value: " << it->second << "\n";
	cout << "****************************\n";
	cout << "size: " << mymap.size() << "\n";
	// cout << "max size: " << mymap.max_size() << "\n";
	cout << "empty: " << (mymap.empty() == 1 ? "true" : "false") << "\n";
	cout << "****************************\n";
}

int main()
{
	cout << "*****MAP TESTS*****\n";
	typedef map<int, int> intMap;
	typedef map<int, int>::reverse_iterator rMapIt;

	cout << "CONSTRUCTORS AND ITERATORS:\n";

	intMap mymap;

	cout << "\nMODIFIRS:\n";

	cout << "mymap.insert(make_pair(i, i))\n";
	for (int i = 0; i < 5; i++)
		mymap.insert(ft::make_pair(i, i));
	printAttributes(mymap);

	cout << "mymap.insert(mymap.begin(), make_pair(i, i))\n";
	for (int i = 5; i < 10; i++)
		mymap.insert(mymap.begin(), ft::make_pair(i, i));
	printAttributes(mymap);

	cout << "mymap.insert(mymap.begin(), mymap.end())\n";
	mymap.insert(mymap.begin(), mymap.end());
	printAttributes(mymap);

	{
		cout << "operator=\n";
		intMap other = mymap;
		printAttributes(mymap);
	}
	cout << "copy cunstructor\n";
	intMap other(mymap);
	printAttributes(mymap);
	{
		cout << "iterator constructor\n";
		intMap map2(mymap.begin(), mymap.end());
		printAttributes(map2);
	}
	cout << "reverse iterator\n";
	for (rMapIt it = mymap.rbegin(); it != mymap.rend(); it++)
		cout << "key: " << it->first << ", value: " << it->second << "\n";

	cout << "swap(other)\n";
	mymap.swap(other);
	printAttributes(mymap);
	printAttributes(other);

	cout << "mymap.clear()\n";
	printAttributes(mymap);

	cout << "mymap.insert(make_pair(i, i))\n";
	for (int i = 0; i < 5; i++)
		mymap.insert(ft::make_pair(i, i));
	printAttributes(mymap);
	cout << "mymap.erase(3)\n";
	mymap.erase(3);
	printAttributes(mymap);

	cout << "mymap=other\n";
	mymap = other;
	printAttributes(mymap);

	cout << "\nELEMENT ACCES:\n";
	cout << "mymap.at(3) -> " << mymap.at(3) << "\n";
	cout << "mymap.at(out of renge exception in try catch) -> \n";
	try
	{
		mymap.at(-1);
	}
	catch (const std::exception &e)
	{
		cout << e.what() << '\n';
	}
	cout << "mymap[3] -> " << mymap[3] << "\n";
	cout << "mymap[3] = 8 -> " << (mymap[3] = 8) << "\n";

	cout << "\nLOOKUP:\n";
	cout << "mymap.count(3) -> " << mymap.count(3) << "\n";
	cout << "mymap.count(-1) -> " << mymap.count(-1) << "\n";
	cout << "mymap.find(3)->first -> " << mymap.find(3)->first << "\n";
	cout << "mymap.find(-1)->first -> " << mymap.find(-1)->first << "\n";
	cout << "mymap.equal_range(3).first -> " << mymap.equal_range(3).first->first << "\n";
	cout << "mymap.equal_range(-1).first -> " << mymap.equal_range(-1).first->first << "\n";
	cout << "mymap.upper_bound(3)->first -> " << mymap.upper_bound(3)->first << "\n";
	cout << "mymap.upper_bound(-1)->first -> " << mymap.upper_bound(-1)->first << "\n";
	cout << "mymap.lower_bound(3)->first -> " << mymap.lower_bound(3)->first << "\n";
	cout << "mymap.lower_bound(-1)->first -> " << mymap.lower_bound(-1)->first << "\n";

	cout << "\nNON-MEMBER FUNCTIONS:\n";
	cout << "mymap == other -> " << (mymap == other) << "\n";
	cout << "mymap == mymap -> " << (mymap == mymap) << "\n";
	cout << "mymap != other -> " << (mymap != other) << "\n";
	cout << "mymap != mymap -> " << (mymap != mymap) << "\n";
	cout << "mymap < other -> " << (mymap < other) << "\n";
	cout << "mymap < mymap -> " << (mymap < mymap) << "\n";
	cout << "mymap <= other -> " << (mymap <= other) << "\n";
	cout << "mymap <= mymap -> " << (mymap <= mymap) << "\n";
	cout << "mymap > other -> " << (mymap > other) << "\n";
	cout << "mymap > mymap -> " << (mymap > mymap) << "\n";
	cout << "mymap >= other -> " << (mymap >= other) << "\n";
	cout << "mymap >= mymap -> " << (mymap >= mymap) << "\n";

	cout << "swap(mymap, other)\n";
	ft::swap(mymap, other);
	printAttributes(mymap);
	printAttributes(other);

	cout << "\nPERFORMANCE:\n";
	for (int i = 0; i < 150000; i++)
		mymap.insert(ft::make_pair(i, i));
	printAttributes(mymap);

	return 0;
}