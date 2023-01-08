#include <iostream>
#include <vector>

using std::cout;
using std::vector;

template <class T>
void printAttributes(vector<T> myvector)
{
	for (typename vector<T>::iterator it = myvector.begin(); it != myvector.end(); it++)
		cout << *it << "\n";
	cout << "****************************\n";
	cout << "size: " << myvector.size() << "\n";
	cout << "campacity: " << myvector.capacity() << "\n";
	cout << "max size: " << myvector.max_size() << "\n";
	cout << "empty: " << (myvector.empty() == 1 ? "true" : "false") << "\n";
	cout << "****************************\n";
}

int main()
{
	cout << "*****VECTOR TESTS*****\n";
	typedef vector<int> intVector;
	typedef vector<int>::iterator vectorIt;
	typedef vector<int>::reverse_iterator rVectorIt;

	cout << "CONSTRUCTORS AND ITERATORS:\n";

	intVector myvector;
	cout << "operator= with fill constructor\n";
	cout << "forward iterator\n";
	myvector = vector<int>(5, 1);
	printAttributes(myvector);
	for (vectorIt it = myvector.begin(); it != myvector.end(); it++)
		cout << *it << "\n";
	{
		cout << "copy constructor\n";
		intVector vector2(myvector);
		for (vectorIt it = vector2.begin(); it != vector2.end(); it++)
			cout << *it << "\n";
		printAttributes(vector2);
	}
	{
		cout << "iterator constructor\n";
		intVector vector2(myvector.begin(), myvector.end());
		for (vectorIt it = vector2.begin(); it != vector2.end(); it++)
			cout << *it << "\n";
		printAttributes(vector2);
	}
	cout << "reverse iterator\n";
	for (rVectorIt it = myvector.rbegin(); it != myvector.rend(); it++)
		cout << *it << "\n";

	cout << "\nMODIFIRS:\n";
	cout << "assign inside uses myvector.clear()\n";
	myvector.assign(5, 5);
	printAttributes(myvector);

	// array for testing iterator insert | clear
	int myarray[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	cout << "iterator assign inside uses myvector.clear()\n";
	myvector.assign(myarray, myarray + 5);
	printAttributes(myvector);

	cout << "myvector.push_back() 10 times\n";
	for (int i = 0; i < 10; i++)
		myvector.push_back(i);
	printAttributes(myvector);

	cout << "myvector.pop_back() 15 times\n";
	for (int i = 0; i < 10; i++)
		myvector.pop_back();
	printAttributes(myvector);

	cout << "myvector.insert(myvector.begin(), 5)\n";
	myvector.insert(myvector.begin(), 5);
	cout << "myvector.insert(myvector.begin() + 1, 6)\n";
	myvector.insert(myvector.begin() + 1, 6);
	cout << "myvector.insert(myvector.end(), 7)\n";
	myvector.insert(myvector.end(), 7);
	printAttributes(myvector);

	cout << "myvector.insert(myvector.begin(), 3, 5)\n";
	myvector.insert(myvector.begin(), 3, 5);
	cout << "myvector.insert(myvector.begin() + 1, 3, 6)\n";
	myvector.insert(myvector.begin() + 1, 3, 6);
	cout << "myvector.insert(myvector.end(), 3, 7)\n";
	myvector.insert(myvector.end(), 3, 7);
	printAttributes(myvector);

	cout << "myvector.insert(myvector.begin(), myarray, myarray + 5)\n";
	myvector.insert(myvector.begin(), myarray, myarray + 5);
	cout << "myvector.insert(myvector.begin() + 1, myarray, myarray + 5)\n";
	myvector.insert(myvector.begin() + 1, myarray, myarray + 5);
	cout << "myvector.insert(myvector.end(), myarray, myarray + 5)\n";
	myvector.insert(myvector.end(), myarray, myarray + 5);
	printAttributes(myvector);

	cout << "rezise(5)\n";
	myvector.resize(5);
	printAttributes(myvector);

	cout << "swap(other)\n";
	intVector other(8, 8);
	myvector.swap(other);
	printAttributes(myvector);
	printAttributes(other);

	cout << "\nELEMENT ACCES:\n";
	cout << "ft_myvector.at(3) -> " << myvector.at(3) << "\n";
	cout << "ft_myvector.at(out of renge exception in try catch) -> \n";
	try
	{
		myvector.at(myvector.size());
	}
	catch (const std::exception &e)
	{
		cout << e.what() << '\n';
	}
	cout << "ft_vector[3] -> " << myvector[3] << "\n";
	cout << "ft_vector.front() -> " << myvector.front() << "\n";
	cout << "ft_vector.back() -> " << myvector.back() << "\n";
	cout << "ft_vector.data() -> " << myvector.data() << "\n";

	cout << "\nNON-MEMBER FUNCTIONS:\n";
	cout << "myvector == other -> " << (myvector == other) << "\n";
	cout << "myvector == myvector -> " << (myvector == myvector) << "\n";
	cout << "myvector != other -> " << (myvector != other) << "\n";
	cout << "myvector != myvector -> " << (myvector != myvector) << "\n";
	cout << "myvector < other -> " << (myvector < other) << "\n";
	cout << "myvector < myvector -> " << (myvector < myvector) << "\n";
	cout << "myvector <= other -> " << (myvector <= other) << "\n";
	cout << "myvector <= myvector -> " << (myvector <= myvector) << "\n";
	cout << "myvector > other -> " << (myvector > other) << "\n";
	cout << "myvector > myvector -> " << (myvector > myvector) << "\n";
	cout << "myvector >= other -> " << (myvector >= other) << "\n";
	cout << "myvector >= myvector -> " << (myvector >= myvector) << "\n";

	cout << "swap(myvector, other)\n";
	std::swap(myvector, other);
	printAttributes(myvector);
	printAttributes(other);

	cout << "\nPERFORMANCE:\n";
	for(int i = 0; i < 15000; i++)
		myvector.push_back(i);
	printAttributes(myvector);

	return 0;
}