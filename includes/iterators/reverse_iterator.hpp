#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator.hpp"

namespace ft
{
	template <class Iterator>
	class reverse_iterator
	{
	public:
		typedef Iterator iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
		typedef typename iterator_traits<Iterator>::value_type value_type;
		typedef typename iterator_traits<Iterator>::difference_type difference_type;
		typedef typename iterator_traits<Iterator>::pointer pointer;
		typedef typename iterator_traits<Iterator>::reference reference;

	protected:
		iterator_type current;

	public:
		// default (1)
		reverse_iterator() : current(0) {}
		// initialization (2)
		explicit reverse_iterator(iterator_type it) : current(it){};
		// copy (3)
		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter> &rev_it) : current(rev_it.base()) {}

		template <class U>
		reverse_iterator &operator=(const reverse_iterator<U> &other) { current = other.base(); }

		iterator_type base() const { return current; };

		reference operator*() const
		{
			iterator_type tmp = current;
			return *tmp;
		};

		pointer operator->() const { return &(operator*()); };

		reference operator[](difference_type n) const { return base()[-n - 1]; };

		reverse_iterator &operator++()
		{
			--current;
			return *this;
		};
		reverse_iterator &operator--()
		{
			++current;
			return *this;
		};
		reverse_iterator operator++(int)
		{
			reverse_iterator tmp = *this;
			--current;
			return tmp;
		};
		reverse_iterator operator--(int)
		{
			reverse_iterator tmp = *this;
			++current;
			return tmp;
		};
		reverse_iterator operator+(difference_type n) const { return reverse_iterator(base() - n); };
		reverse_iterator operator-(difference_type n) const { return reverse_iterator(base() + n); };
		reverse_iterator &operator+=(difference_type n)
		{
			current = current - n;
			return *this;
		};
		reverse_iterator &operator-=(difference_type n)
		{
			current = current + n;
			return *this;
		};
	};

	// NON MEMBER FUNCTIONS
	template <class Iterator1, class Iterator2>
	bool operator==(const reverse_iterator<Iterator1> &lhs,
					const reverse_iterator<Iterator2> &rhs)
	{
		return lhs.base() == rhs.base();
	}
	template <class Iterator1, class Iterator2>
	bool operator!=(const reverse_iterator<Iterator1> &lhs,
					const reverse_iterator<Iterator2> &rhs)
	{
		return lhs.base() != rhs.base();
	}
	template <class Iterator1, class Iterator2>
	bool operator<(const reverse_iterator<Iterator1> &lhs,
				   const reverse_iterator<Iterator2> &rhs)
	{
		return lhs.base() < rhs.base();
	}
	template <class Iterator1, class Iterator2>
	bool operator<=(const reverse_iterator<Iterator1> &lhs,
					const reverse_iterator<Iterator2> &rhs)
	{
		return lhs.base() <= rhs.base();
	}
	template <class Iterator1, class Iterator2>
	bool operator>(const reverse_iterator<Iterator1> &lhs,
				   const reverse_iterator<Iterator2> &rhs)
	{
		return lhs.base() > rhs.base();
	}
	template <class Iterator1, class Iterator2>
	bool operator>=(const reverse_iterator<Iterator1> &lhs,
					const reverse_iterator<Iterator2> &rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n,
											 const reverse_iterator<Iterator> &it)
	{
		return reverse_iterator<Iterator>(it.base() - n);
	}

	template <class Iterator1, class Iterator2>
	typename reverse_iterator<Iterator1>::difference_type
	operator-(const reverse_iterator<Iterator1> &lhs,
			  const reverse_iterator<Iterator2> &rhs)
	{
		return rhs.base() - lhs.base();
	}
} // namespace ft

#endif