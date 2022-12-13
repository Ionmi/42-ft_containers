#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <iostream>
#include <vector>

using std::cout;

template <typename vector, >
class RandomAccessIterator
{
public:
	typedef typename vector::value_type value_type;
	typedef typename value_type::difference_type difference_type;
	typedef typename value_type::pointer pointer;
	typedef typename value_type::reference reference;

private:
	pointer ptr;

public:
	RandomAccessIterator(){};
	// RandomAccessIterator(pointer ptr) : ptr(ptr){};
	// RandomAccessIterator(RandomAccessIterator &ref) : ptr(ref.ptr){};
	// RandomAccessIterator &operator=(const RandomAccessIterator &ref)
	// {
	// 	ptr = ref.ptr;
	// 	return *this;
	// };
	// virtual ~RandomAccessIterator(){};

	// // OPERATORS
	// bool operator==(const RandomAccessIterator &rhs) const { return ptr == rhs.ptr; }
	// bool operator!=(const RandomAccessIterator &rhs) const { return ptr != rhs.ptr; }
	// RandomAccessIterator &operator++()
	// {
	// 	++ptr;
	// 	return *this;
	// }
	// RandomAccessIterator &operator++(int)
	// {
	// 	RandomAccessIterator it = *this;
	// 	++ptr;
	// 	return it;
	// }
	// RandomAccessIterator &operator--()
	// {
	// 	--ptr;
	// 	return *this;
	// }
	// RandomAccessIterator &operator--(int)
	// {
	// 	RandomAccessIterator it = *this;
	// 	--ptr;
	// 	return it;
	// }
	// reference operator*() const { return *ptr; }
	// pointer operator->() const { return ptr; }
	// RandomAccessIterator operator+(const difference_type n) const { return ptr + n; }
	// RandomAccessIterator operator-(const difference_type n) const { return ptr - n; }
	// RandomAccessIterator operator+(RandomAccessIterator const &it) const { return ptr + it; }
	// RandomAccessIterator operator-(RandomAccessIterator const &it) const { return ptr - it; }
	// RandomAccessIterator operator+=(const difference_type n) const
	// {
	// 	ptr += n;
	// 	return *this;
	// }
	// RandomAccessIterator operator-=(const difference_type n) const
	// {
	// 	ptr -= n;
	// 	return *this;
	// }
	// reference operator[](int i) const { return *(ptr + i); }
};

namespace ft
{
	template <class T, class Allocator = std::allocator<T>>
	class vector
	{

	public:
		typedef T value_type;
		typedef Allocator allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::size_type size_type;
		typedef typename allocator_type::difference_type difference_type;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef RandomAccessIterator<value_type> iterator;
		typedef RandomAccessIterator<const value_type> const_iterator;
		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	private:
		pointer _first;
		size_type _size, _capacity, _max_size;
		allocator_type allocator;

	public:
		//(1) empty container constructor (default constructor) -> Constructs an empty container, with no elements.
		explicit vector(const allocator_type &alloc = allocator_type()) : _first(NULL), _size(0), _capacity(0), allocator(alloc)
		{
			set_max_size();
		}
		// (2) fill constructor -> Constructs a container with n elements. Each element is a copy of val.
		explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
			: _size(n), _capacity(n), allocator(alloc)
		{
			set_max_size();
			_first = allocate(_capacity);
			for (size_type i = 0; i < _size; i++)
				allocator.construct(_first + i, val);
		}
		// (3) range constructor -> Constructs a container with as many elements as the range [first,last), with each element constructed from its corresponding element in that range, in the same order.
		template <class InputIterator>
		vector(typename InputIterator::type first, typename InputIterator::type last, const allocator_type &alloc = allocator_type()) : allocator(alloc)
		{
			set_max_size();
			if (first > last)
				throw std::length_error("vector");
			_size = last - first;
			_capacity = _size;
			_first = allocate(_capacity);
			for (difference_type i = 0; i < static_cast<difference_type>(_size); i++)
				allocator.construct(_first + i, *(first + i));
		}
		// (4) copy constructor -> Constructs a container with a copy of each of the elements in x, in the same order.
		vector(const vector &x) : _size(0), _capacity(0)
		{
			*this = x;
		}
		// assing operator -> Assigns new contents to the container, replacing its current contents, and modifying its size accordingly.
		vector &operator=(const vector &x)
		{
			if (this == &x)
				return *this;
			if (_capacity < x._size)
			{
				deallocate();
				_capacity = x._size;
				_first = allocate(_capacity);
			}
			else
			{
				for (size_type i = 0; i < _size; i++)
					allocator.destroy(_first + i);
			}
			_size = x._size;
			for (size_type i = 0; i < _size; i++)
				allocator.construct(_first + i, *(x + i));
			return *this;
		}
		// destructor -> This destroys all container elements, and deallocates all the storage capacity allocated by the vector using its allocator.
		~vector() { deallocate(); }

	private:
		void ReAlloc(size_type newCapacity);
		pointer allocate(const size_type &n)
		{
			if (n > _max_size)
				throw std::length_error("vector");
			return allocator.allocate(n);
		}
		void deallocate()
		{
			if (_capacity == 0)
				return;
			for (size_type i = 0; i < _size; i++)
				allocator.destroy(_first + i);
			allocator.deallocate(_first, _capacity);
		}
		void set_capacity(const size_type &n)
		{
			if (n > _max_size)
				throw std::length_error("vector");
			if (n == 0)
				return;
			size_type exp = 1;
			while (exp < n && exp <= _max_size)
				exp = exp << 1;
			if (exp > _max_size)
				throw std::length_error("vector");
			_capacity = exp;
		}
		void set_max_size() { _max_size = allocator.max_size(); };

	public:
		// ITERATORS
		iterator begin()
		{
			return iterator(_first);
		}
		const_iterator begin() const
		{
			return const_iterator(_first);
		}
		iterator end()
		{
			return iterator(_first + _size);
		}
		const_iterator end() const
		{
			return const_iterator(_first + _size);
		}

		// CAPACITY
		size_type size() const { return _size; };
		size_type max_size() const { return _max_size; };
		void resize(size_type n, value_type val = value_type())
		{
			if (n == _size)
				return;
			if (n < _size)
			{
				for (size_type i = n; i < _size; i++)
					allocator.destroy(_first + i);
				_size = n;
				return;
			}
			reserve(n);
			for (size_type i = _size; i < n; i++)
				allocator.construct(_first + i, val);
			_size = n;
		};
		size_type capacity() const { return _capacity; };
		bool empty() const { return _size == 0; };
		void reserve(size_type n)
		{
			if (n < _capacity)
				return;
			pointer tmp = allocate(n);
			for (size_type i = 0; i < _size; i++)
				allocator.construct(tmp + i, *(_first + i));
			deallocate();
			_capacity = n;
			_first = tmp;
		};

		// ELEMENT ACCESS
		reference operator[](size_type n) { return *(_first + n); }
		const_reference operator[](size_type n) const { return *(_first + n); }
		reference at(size_type n)
		{
			if (n >= _capacity)
				throw std::out_of_range("vector");
			return *(_first + n);
		}
		const_reference at(size_type n) const
		{
			if (n >= _capacity)
				throw std::out_of_range("vector");
			return *(_first + n);
		}
		reference front() { return *_first; }
		const_reference front() const { return *_first; }
		reference back() { return *(_first + _size - 1); }
		const_reference back() const { return *(_first + _size - 1); }
		value_type *data() { return _first; }
		const value_type *data() const { return _first; }

		// MODIFIERS
		// range (1)
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			if (first > last)
				throw std::length_error("vector");
			clear();
			_size = last - first;
			if (_size > _capacity)
			{
				deallocate();
				_capacity = _size;
				_first = allocate(_size);
			}
			for (difference_type i = 0; i < static_cast<difference_type>(_size); i++)
				allocator.construct(_first + i, *(first + i));
		}
		// fill (2)
		void assign(size_type n, const value_type &val)
		{
			clear();
			_size = n;
			if (n > _capacity)
			{
				deallocate();
				_capacity = n;
				_first = allocate(n);
			}
			for (size_type i = 0; i < n; i++)
				allocator.construct(_first + i, val);
		}
		void push_back(const value_type &val)
		{
			if (_capacity > _size)
			{
				allocator.construct(_first + _size, val);
				_size++;
				return;
			}
			set_capacity(_capacity + 1);
			pointer tmp = allocate(_capacity);
			for (size_type i = 0; i < _size; i++)
				allocator.construct(tmp + i, *(_first + i));
			deallocate();
			_first = tmp;
			allocator.construct(_first + _size, val);
			_size++;
		}
		void pop_back()
		{
			_size--;
			allocator.destroy(_first + _size);
		}
		// // single element (1)
		// iterator insert(iterator position, const value_type &val);
		// // fill (2)
		// void insert(iterator position, size_type n, const value_type &val);
		// // range (3)
		// template <class InputIterator>
		// void insert(iterator position, InputIterator first, InputIterator last);
		// iterator erase (iterator position);
		// iterator erase (iterator first, iterator last);
		void swap(vector &x)
		{
			std::swap(_first, x._first);
			std::swap(_size, x._size);
			std::swap(_capacity, x._capacity);
			std::swap(allocator, x.allocator);
		}
		void clear()
		{
			for (size_type i = 0; i < _size; i++)
				allocator.destroy(_first + i);
			_size = 0;
		}

		// ALLOCATOR
		allocator_type get_allocator() const
		{
			return allocator;
		}
	};

	// RELATIONAL OPERATORS
	// template <class T, class Alloc>
	// bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	// {
	// 	if (lhs.size() != rhs.size())
	// 		return false;
	// 	return std::equal(lhs.begin(), lhs.end(), rhs);
	// 	for (size_t i = 0; i < lhs.size(); i++)
	// 	{
	// 		if (lhs[i] != rhs[i])
	// 			return false;
	// 	}
	// 	return true;
	// }
	// template <class T, class Alloc>
	// bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	// {
	// 	if (lhs.size() != rhs.size())
	// 		return true;
	// 	return !std::equal(lhs.begin(), lhs.end(), rhs);
	// }
	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);
	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);
	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);
	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);
}

#endif