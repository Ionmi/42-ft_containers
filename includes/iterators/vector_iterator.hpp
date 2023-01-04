#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "iterator.hpp"

namespace ft
{
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

} // namespace ft

#endif