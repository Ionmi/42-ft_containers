#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <iostream>
// #include <vector>
#include "../iterators/vector_iterator.hpp"
#include "../iterators/reverse_iterator.hpp"
#include "../compares.hpp"

using std::cout;

namespace ft
{

	template <class T, class Allocator = std::allocator<T> >
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
		typedef ft::iterator<vector> iterator;
		typedef ft::iterator<const vector> const_iterator;
		typedef typename ft::reverse_iterator<iterator> reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

	private:
		allocator_type allocator;
		pointer _first;
		size_type _size, _capacity, _max_size;

	public:
		//(1) empty container constructor (default constructor) -> Constructs an empty container, with no elements.
		explicit vector(const allocator_type &alloc = allocator_type())
			: allocator(alloc), _first(NULL), _size(0), _capacity(0), _max_size(allocator.max_size()) {}
		// (2) fill constructor -> Constructs a container with n elements. Each element is a copy of val.
		explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
			: allocator(alloc), _size(n), _capacity(n), _max_size(allocator.max_size())
		{
			_first = allocator.allocate(n);
			for (size_type i = 0; i < _size; i++)
				allocator.construct(_first + i, val);
		}
		// (3) range constructor -> Constructs a container with as many elements as the range [first,last), with each element constructed from its corresponding element in that range, in the same order.
		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
			   typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0)
			: allocator(alloc), _max_size(allocator.max_size())
		{
			if (first > last)
				throw std::length_error("vector");
			_size = last - first;
			_capacity = _size;
			_first = allocator.allocate(_capacity);
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
				_first = allocator.allocate(_capacity);
			}
			else
			{
				for (size_type i = 0; i < _size; i++)
					allocator.destroy(_first + i);
			}
			_size = x._size;
			for (size_type i = 0; i < _size; i++)
				allocator.construct(_first + i, x[i]);
			return *this;
		}
		// destructor -> This destroys all container elements, and deallocates all the storage capacity allocated by the vector using its allocator.
		~vector()
		{
			deallocate();
		};

	private:
		void deallocate()
		{
			if (_capacity == 0)
				return;
			for (size_type i = 0; i < _size; i++)
				allocator.destroy(_first + i);
			allocator.deallocate(_first, _capacity);
		}
		void set_capacity()
		{
			if (_capacity == 0)
			{
				_capacity = 1;
				return;
			}
			if ((_capacity = _capacity << 1) > _max_size)
				throw std::length_error("vector");
		}

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
		reverse_iterator rbegin()
		{
			return reverse_iterator(_first + _size - 1);
		}
		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(_first + _size - 1);
		}
		reverse_iterator rend()
		{
			return reverse_iterator(_first - 1);
		}
		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(_first - 1);
		}
		// CAPACITY
		size_type size() const { return _size; };
		size_type max_size() const { return allocator.max_size(); };
		// size_type max_size() const { return sizeof(value_type) == 1 ? _max_size : _max_size / (sizeof(value_type) / 2); };
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
			if (n <= _capacity)
				return;
			pointer tmp = allocator.allocate(n);
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
			if (n >= _size)
				throw std::out_of_range("vector");
			return *(_first + n);
		}
		const_reference at(size_type n) const
		{
			if (n >= _size)
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
		void assign(InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0)
		{
			if (first > last)
				throw std::length_error("vector");
			clear();
			_size = last - first;
			if (_size > _capacity)
			{
				deallocate();
				_capacity = _size;
				_first = allocator.allocate(_size);
			}
			for (difference_type i = 0; i < static_cast<difference_type>(_size); i++)
				allocator.construct(_first + i, *first++);
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
				_first = allocator.allocate(n);
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
			set_capacity();
			pointer tmp = allocator.allocate(_capacity);
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
		// single element (1)
		iterator insert(iterator position, const value_type &val)
		{
			difference_type pos = position - _first;
			if (_capacity == _size++)
			{
				set_capacity();
				reserve(_size);
			}
			difference_type i = _size - 1;
			while (i > pos)
			{
				allocator.construct(_first + i, _first[i - 1]);
				i--;
			}
			allocator.construct(_first + i, val);
			return position;
		}
		// fill (2)
		void insert(iterator position, size_type n, const value_type &val)
		{
			difference_type pos = position - _first;
			if (_capacity < _size + n)
			{
				size_type capacity = _capacity;
				while (_capacity < _size + n)
					set_capacity();
				std::swap(capacity, _capacity);
				reserve(capacity);
			}
			_size += n;
			difference_type i = _size - 1;
			while (i > pos + (difference_type)n - 1)
			{
				allocator.construct(_first + i, _first[i - n]);
				i--;
			}
			while (i >= pos)
			{
				allocator.construct(_first + i, val);
				i--;
			}
		}

		// range (3)

		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0)
		{
			if (first == last)
				return;
			if (first > last)
				throw std::out_of_range("vector");
			if (position < begin() || position > end())
				throw std::out_of_range("vector");
			difference_type n = last - first;
			difference_type i = position - begin();
			if (_capacity < _size + n)
			{
				size_type capacity = _capacity;
				while (_capacity < _size + n)
					set_capacity();
				std::swap(capacity, _capacity);
				reserve(capacity);
			}
			for (difference_type j = _size; j > i; j--)
			{
				allocator.construct(&_first[j + n - 1], _first[j - 1]);
				allocator.destroy(&_first[j - 1]);
			}
			for (difference_type j = 0; j < n; j++)
				allocator.construct(&_first[j + i], *(first + j));
			_size += n;
		}

		iterator erase(iterator position)
		{
			iterator it = position;
			while (it + 1 != this->end())
			{
				_first[it - _first] = _first[(it + 1) - _first];
				it++;
			}
			pop_back();
			return position;
		}
		iterator erase(iterator first, iterator last)
		{
			vector tmp = *this;
			tmp.clear();
			iterator it = _first;
			while (it != first)
				tmp.push_back(_first[it++ - _first]);
			it = last;
			while (it != this->end())
				tmp.push_back(_first[it++ - _first]);
			*this = tmp;
			return last;
		}

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

	// NON-MEMBER FUNCTION OVERLOADS

	// RELATIONAL OPERATORS
	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}
	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return true;
		return !ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}
	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		if (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()))
			return true;
		return lhs == rhs;
	}
	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(lhs <= rhs);
	}
	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}

	// SWAP
	template <class T, class Alloc>
	void swap(vector<T, Alloc> &lhs, vector<T, Alloc> &rhs)
	{
		lhs.swap(rhs);
	}
}

#endif