#ifndef SET_HPP
#define SET_HPP

#include <iostream>
#include "../pairs.hpp"
#include "../compares.hpp"
#include "../RedBlackTree.hpp"
#include "../iterators/set_iterator.hpp"
#include "../iterators/reverse_iterator.hpp"

namespace ft
{
	template <class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
	class set
	{

	public:
		typedef Key key_type;
		typedef Key value_type;
		typedef Compare key_compare;
		typedef Compare value_compare;
		typedef Allocator allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::size_type size_type;
		typedef typename allocator_type::difference_type difference_type;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef ft::set_iterator<set> iterator;
		typedef ft::set_iterator<const set> const_iterator;
		typedef typename ft::reverse_iterator<iterator> reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

	private:
		typedef ft::rbt::RBT<Key, value_type, Compare> RBtree;
		typedef ft::rbt::RBnode<key_type, value_type> *nodePtr;

		RBtree rbTree;
		size_type _size;
		key_compare compare;
		allocator_type allocator;

	public:
		key_compare key_comp() const
		{
			return compare;
		}

		value_compare value_comp() const
		{
			return compare;
		}

		// CONSTRUCTORS

		// empty(1)
		explicit set(const Compare &comp = key_compare(), const Allocator &alloc = Allocator())
			: _size(0), compare(comp), allocator(alloc) {}

		// range (2)
		template <class InputIterator>
		set(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
			: _size(0), compare(comp), allocator(alloc)
		{
			for (; first != last; ++first)
				insert(*first);
		}
		// copy (3)
		set(const set &x)
		{
			*this = x;
		}

		// copy (1)
		set &operator=(const set &x)
		{
			if (this == &x)
				return *this;
			clear();
			for (const_iterator it = x.begin(); it != x.end(); ++it)
				insert(*it);
			return *this;
		}

		~set() {}

		allocator_type get_allocator() const { return allocator; }

		// ITERATORS
		iterator begin() { return iterator(rbTree.findBegin()); };
		const_iterator begin() const { return const_iterator(rbTree.findBegin()); };
		iterator end() { return iterator(rbTree.findEnd()); };
		const_iterator end() const { return const_iterator(rbTree.findEnd()); };

		reverse_iterator rbegin() { return reverse_iterator(rbTree.findRbegin()); };
		const_reverse_iterator rbegin() const { return const_reverse_iterator(rbTree.findRbegin()); };
		reverse_iterator rend() { return reverse_iterator(rbTree.findRend()); };
		const_reverse_iterator rend() const { return const_reverse_iterator(rbTree.findRend()); };

		// CAPACITY
		bool empty() const { return _size == 0; };
		size_type size() const { return _size; };
		size_type max_size() const
		{
			return allocator.max_size() < rbTree.getMaxSize()
					   ? allocator.max_size()
					   : rbTree.getMaxSize();
		};

		// MODIFIERS
		void clear()
		{
			rbTree.clear();
			_size = 0;
		}
		// single element (1)
		pair<iterator, bool> insert(const value_type &val)
		{
			nodePtr node = rbTree.getNode(val);
			if (node != nullptr)
				return ft::make_pair(iterator(node), false);

			node = rbTree.insert(val, val);
			_size++;
			return ft::make_pair(iterator(node), true);
		}
		// with hint (2)
		iterator insert(iterator position, const value_type &val)
		{
			(void)position;
			return insert(val).first;
		}
		// range (3)
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			if (first == last)
				return;
			for (; first != last; ++first)
				insert(*first);
		}

		// erase (1)
		void erase(iterator position) { erase(*position); }
		// erase (2)
		size_type erase(const key_type &key)
		{
			if (rbTree.find(key) == NULL)
				return 0;
			rbTree.remove(key);
			_size--;
			return 1;
		}
		// erase (3)
		void erase(iterator first, iterator last)
		{
			if (first == last)
				return;
			for (; first != last; ++first)
				erase(*first);
		}

		void swap(set &x)
		{
			set tmp(x);

			x.clear();
			for (iterator it = begin(); it != end(); ++it)
				x.insert(*it);
			clear();
			for (iterator it = tmp.begin(); it != tmp.end(); ++it)
				insert(*it);
			std::swap(compare, x.compare);
			std::swap(allocator, x.allocator);
		}

		// LOOKUP
		size_type count(const Key &key) const
		{
			nodePtr node = rbTree.getNode(key);
			if (node == nullptr)
				return 0;
			return 1;
		}
		iterator find(const Key &key)
		{
			nodePtr node = rbTree.getNode(key);
			if (node == nullptr)
				return end();
			return iterator(node);
		}
		const_iterator find(const Key &key) const
		{
			nodePtr node = rbTree.getNode(key);
			if (node == nullptr)
				return end();
			return const_iterator(node);
		}
		iterator lower_bound(const key_type &key)
		{
			iterator it = begin();
			for (; it != end(); it++)
				if (!compare(*it, key))
					return it == begin() ? end() : it;
			return end();
		}
		const_iterator lower_bound(const key_type &key) const
		{
			const_iterator it = begin();
			for (; it != end(); it++)
				if (!compare(*it, key))
					return it == begin() ? end() : it;
			return end();
		}
		iterator upper_bound(const key_type &key)
		{
			iterator it = begin();
			for (; it != end(); it++)
				if (compare(key, *it))
					return it;
			return end();
		}
		const_iterator upper_bound(const key_type &key) const
		{
			const_iterator it = begin();
			for (; it != end(); it++)
				if (compare(key, *it))
					return it;
			return end();
		}
		ft::pair<iterator, iterator> equal_range(const key_type &key)
		{
			return ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
		}
		ft::pair<const_iterator, const_iterator> equal_range(const key_type &key) const
		{
			return ft::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
		}
	};

	// NO-MEMBER FUNCTIONS
	// RELATIONAL OPERATORS
	template <class Key, class Compare, class Alloc>
	bool operator==(const ft::set<Key, Compare, Alloc> &lhs,
					const ft::set<Key, Compare, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}
	template <class Key, class Compare, class Alloc>
	bool operator!=(const ft::set<Key, Compare, Alloc> &lhs,
					const ft::set<Key, Compare, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return true;
		return !ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}
	template <class Key, class Compare, class Alloc>
	bool operator<(const ft::set<Key, Compare, Alloc> &lhs,
				   const ft::set<Key, Compare, Alloc> &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template <class Key, class Compare, class Alloc>
	bool operator<=(const ft::set<Key, Compare, Alloc> &lhs,
					const ft::set<Key, Compare, Alloc> &rhs)
	{
		if (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()))
			return true;
		return lhs == rhs;
	}
	template <class Key, class Compare, class Alloc>
	bool operator>(const ft::set<Key, Compare, Alloc> &lhs,
				   const ft::set<Key, Compare, Alloc> &rhs)
	{
		return !(lhs <= rhs);
	}
	template <class Key, class Compare, class Alloc>
	bool operator>=(const ft::set<Key, Compare, Alloc> &lhs,
					const ft::set<Key, Compare, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}

	// SWAP
	template <class Key, class Compare, class Alloc>
	void swap(ft::set<Key, Compare, Alloc> &lhs,
			  ft::set<Key, Compare, Alloc> &rhs)
	{
		lhs.swap(rhs);
	}
} // namespace ft
#endif