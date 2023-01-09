#include <iostream>
#include <set>

using std::cout;
using std::set;

template <class Key>
void printAttributes(set<Key> myset)
{
	for (typename set<Key>::iterator it = myset.begin(); it != myset.end(); it++)
		cout << "key value: " << *it << "\n";
	cout << "****************************\n";
	cout << "size: " << myset.size() << "\n";
	cout << "max size: " << myset.max_size() << "\n";
	cout << "empty: " << (myset.empty() == 1 ? "true" : "false") << "\n";
	cout << "****************************\n";
}

int main()
{
	cout << "*****SET TESTS*****\n";
	typedef set<int> intSet;
	typedef set<int>::reverse_iterator rSetIt;

	cout << "CONSTRUCTORS AND ITERATORS:\n";

	intSet myset;

	cout << "\nMODIFIRS:\n";

	cout << "myset.insert(i)\n";
	for (int i = 0; i < 5; i++)
		myset.insert(i);
	printAttributes(myset);

	cout << "myset.insert(myset.begin(), i)\n";
	for (int i = 5; i < 10; i++)
		myset.insert(myset.begin(), i);
	printAttributes(myset);

	cout << "myset.insert(myset.begin(), myset.end())\n";
	myset.insert(myset.begin(), myset.end());
	printAttributes(myset);

	{
		cout << "operator=\n";
		intSet other = myset;
		printAttributes(myset);
	}
	cout << "copy cunstructor\n";
	intSet other(myset);
	printAttributes(myset);
	{
		cout << "iterator constructor\n";
		intSet set2(myset.begin(), myset.end());
		printAttributes(set2);
	}
	cout << "reverse iterator\n";
	for (rSetIt it = myset.rbegin(); it != myset.rend(); it++)
		cout << "key value: " << *it << "\n";

	cout << "swap(other)\n";
	myset.swap(other);
	printAttributes(myset);
	printAttributes(other);

	cout << "myset.clear()\n";
	printAttributes(myset);

	cout << "myset.insert(i)\n";
	for (int i = 0; i < 5; i++)
		myset.insert(i);
	printAttributes(myset);
	cout << "myset.erase(3)\n";
	myset.erase(3);
	printAttributes(myset);

	cout << "myset=other\n";
	myset = other;
	printAttributes(myset);

	cout << "\nLOOKUP:\n";
	cout << "myset.count(3) -> " << myset.count(3) << "\n";
	cout << "myset.count(-1) -> " << myset.count(-1) << "\n";
	cout << "*myset.find(3) -> " << *myset.find(3) << "\n";
	cout << "*myset.find(-1) -> " << *myset.find(-1) << "\n";
	cout << "*myset.equal_range(3).first -> " << *myset.equal_range(3).first << "\n";
	cout << "*myset.equal_range(3).second -> " << *myset.equal_range(3).second << "\n";
	cout << "*myset.equal_range(-1).first -> " << *myset.equal_range(-1).first << "\n";
	cout << "*myset.equal_range(-1).second -> " << *myset.equal_range(-1).second << "\n";
	cout << "*myset.upper_bound(3) -> " << *myset.upper_bound(3) << "\n";
	cout << "*myset.upper_bound(-1) -> " << *myset.upper_bound(-1) << "\n";
	cout << "*myset.lower_bound(3) -> " << *myset.lower_bound(3) << "\n";
	cout << "*myset.lower_bound(-1) -> " << *myset.lower_bound(-1) << "\n";

	cout << "\nNON-MEMBER FUNCTIONS:\n";
	cout << "myset == other -> " << (myset == other) << "\n";
	cout << "myset == myset -> " << (myset == myset) << "\n";
	cout << "myset != other -> " << (myset != other) << "\n";
	cout << "myset != myset -> " << (myset != myset) << "\n";
	cout << "myset < other -> " << (myset < other) << "\n";
	cout << "myset < myset -> " << (myset < myset) << "\n";
	cout << "myset <= other -> " << (myset <= other) << "\n";
	cout << "myset <= myset -> " << (myset <= myset) << "\n";
	cout << "myset > other -> " << (myset > other) << "\n";
	cout << "myset > myset -> " << (myset > myset) << "\n";
	cout << "myset >= other -> " << (myset >= other) << "\n";
	cout << "myset >= myset -> " << (myset >= myset) << "\n";

	cout << "swap(myset, other)\n";
	std::swap(myset, other);
	printAttributes(myset);
	printAttributes(other);

	cout << "\nPERFORMANCE:\n";
	for (int i = 0; i < 150000; i++)
		myset.insert(i);
	printAttributes(myset);

	return 0;
}