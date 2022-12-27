#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{
	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T *, class Reference = T &>
	struct Iterator
	{
		typedef Category iterator_category;
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
	};
	template <class vector>
	class iterator // : public Iterator<typename ft::iterator_traits<vector *>::random_access_iterator_tag, typename vector::value_type>
	{
	public:
		typedef typename vector::value_type value_type;
		typedef typename vector::difference_type difference_type;
		typedef typename vector::pointer pointer;
		typedef typename vector::reference reference;

	private:
		pointer ptr;

	public:
		iterator() : ptr(nullptr){};
		iterator(pointer _ptr) : ptr(_ptr){};
		iterator(const iterator &ref) : ptr(ref.ptr){};

		iterator &operator=(const iterator &ref)
		{
			ptr = ref.ptr;
			return *this;
		};
		virtual ~iterator(){};
		// OPERATORS
		bool operator==(const iterator &rhs) const { return ptr == rhs.ptr; }
		bool operator!=(const iterator &rhs) const { return ptr != rhs.ptr; }
		iterator &operator++()
		{
			++ptr;
			return *this;
		}
		iterator operator++(int)
		{
			iterator it = *this;
			++ptr;
			return it;
		}
		iterator &operator--()
		{
			--ptr;
			return *this;
		}
		iterator operator--(int)
		{
			iterator it = *this;
			--ptr;
			return it;
		}
		reference operator*() const { return *ptr; }
		pointer operator->() const { return ptr; }
		iterator operator+(const difference_type n) const
		{
			iterator tmp = *this;
			return tmp.ptr += n;
		}
		iterator operator-(const difference_type n) const
		{
			iterator tmp = *this;
			return tmp.ptr -= n;
		}
		difference_type operator+(const iterator &it) { return ptr + it.ptr; }
		difference_type operator-(const iterator &it) { return ptr - it.ptr; }
		iterator operator+=(const difference_type n)
		{
			ptr += n;
			return *this;
		}
		iterator operator-=(const difference_type n)
		{
			ptr -= n;
			return *this;
		}
		reference operator[](int i) const { return *(ptr + i); }

		bool operator>(const iterator &rhs) const { return ptr > rhs.ptr; }
		bool operator>=(const iterator &rhs) const { return ptr >= rhs.ptr; }
		bool operator<(const iterator &rhs) const { return ptr < rhs.ptr; }
		bool operator<=(const iterator &rhs) const { return ptr <= rhs.ptr; }
	};
	
	template <class vector>
	class reverse_iterator // : public Iterator<typename ft::iterator_traits<vector *>::random_access_iterator_tag, typename vector::value_type>
	{
	public:
		typedef typename vector::value_type value_type;
		typedef typename vector::difference_type difference_type;
		typedef typename vector::pointer pointer;
		typedef typename vector::reference reference;

	private:
		pointer ptr;

	public:
		reverse_iterator() : ptr(nullptr){};
		reverse_iterator(pointer _ptr) : ptr(_ptr){};
		reverse_iterator(const reverse_iterator &ref) : ptr(ref.ptr){};

		reverse_iterator &operator=(const reverse_iterator &ref)
		{
			ptr = ref.ptr;
			return *this;
		};
		virtual ~reverse_iterator(){};
		// OPERATORS
		bool operator==(const reverse_iterator &rhs) const { return ptr == rhs.ptr; }
		bool operator!=(const reverse_iterator &rhs) const { return ptr != rhs.ptr; }
		reverse_iterator &operator++()
		{
			--ptr;
			return *this;
		}
		reverse_iterator operator++(int)
		{
			reverse_iterator it = *this;
			--ptr;
			return it;
		}
		reverse_iterator &operator--()
		{
			++ptr;
			return *this;
		}
		reverse_iterator operator--(int)
		{
			reverse_iterator it = *this;
			++ptr;
			return it;
		}
		reference operator*() const { return *ptr; }
		pointer operator->() const { return ptr; }
		reverse_iterator operator+(const difference_type n) const
		{
			reverse_iterator tmp = *this;
			return tmp.ptr -= n;
		}
		reverse_iterator operator-(const difference_type n) const
		{
			reverse_iterator tmp = *this;
			return tmp.ptr += n;
		}
		difference_type operator+(const reverse_iterator &it) { return ptr - it.ptr; }
		difference_type operator-(const reverse_iterator &it) { return ptr + it.ptr; }
		reverse_iterator operator+=(const difference_type n)
		{
			ptr -= n;
			return *this;
		}
		reverse_iterator operator-=(const difference_type n)
		{
			ptr += n;
			return *this;
		}
		reference operator[](int i) const { return *(ptr + i); }

		bool operator>(const reverse_iterator &rhs) const { return ptr > rhs.ptr; }
		bool operator>=(const reverse_iterator &rhs) const { return ptr >= rhs.ptr; }
		bool operator<(const reverse_iterator &rhs) const { return ptr < rhs.ptr; }
		bool operator<=(const reverse_iterator &rhs) const { return ptr <= rhs.ptr; }
	};

}

#endif