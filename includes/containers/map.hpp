#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include "../pairs.hpp"
#include "../RedBlackTree.hpp"
#include "../iterators/map_iterator.hpp"

// reinterpret_cast<uintptr_t>(ptr);
// reinterpret_cast<Data *>(raw);

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{

	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<Key, T> value_type;
		typedef Compare key_compare;
		typedef Allocator allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::size_type size_type;
		typedef typename allocator_type::difference_type difference_type;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef ft::map_iterator<map> iterator;
		typedef ft::map_iterator<const map> const_iterator;
		typedef typename ft::reverse_iterator<iterator> reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

	private:
		typedef rbt::RBT<Key, value_type, Compare> RBtree;
		typedef rbt::RBnode<key_type, value_type> *nodePtr;
		RBtree rbTree;
		size_type size;
		key_compare compare;
		allocator_type allocator;

	public:
		class value_compare
		{
		protected:
			Compare comp;
			value_compare(Compare c) : comp(c) {} // constructed with map's comparison object
		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator()(const value_type &x, const value_type &y) const
			{
				return comp(x.first, y.first);
			}
		};

		// CONSTRUCTORS

		// empty(1)
		explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
			: size(0), compare(comp), allocator(alloc) {}

		// range (2)
		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type());

		// copy (3)
		map(const map &x)
		{
			*this = x;
		}

		// copy (1)
		map &operator=(const map &x)
		{
			if (this == &x)
				return *this;
			delete rbTree;
			size = x.size;
			rbTree(x.rbTree);
			return *this;
		}

		~map() {}

		// ELEMENT ACCESS
		mapped_type &at(const key_type &k);

		const mapped_type &at(const key_type &k) const;

		mapped_type &operator[](const key_type &k);

		// ITERATORS
		iterator begin() { return iterator(rbTree.findBegin()); };
		const_iterator begin() const { return iterator(rbTree.findBegin()); };
		iterator end() { return iterator(rbTree.findEnd()); };
		const_iterator end() const { return iterator(rbTree.findEnd()); };

		reverse_iterator rbegin() { return reverse_iterator(rbTree.findRbegin()); };
		const_reverse_iterator rbegin() const { return reverse_iterator(rbTree.findRbegin()); };
		reverse_iterator rend() { return reverse_iterator(rbTree.findRend()); };
		const_reverse_iterator rend() const { return reverse_iterator(rbTree.findRend()); };

		// MODIFIERS
		// single element (1)
		pair<iterator, bool> insert(const value_type &val)
		{
			nodePtr node = rbTree.getNode(val.first);
			if (node != nullptr)
				return ft::make_pair(iterator(node), false);

			node = rbTree.insert(val.first, ft::make_pair(val.first, val.second));
			size++;
			return ft::make_pair(iterator(node), true);
		}
		// with hint (2)
		// iterator insert(iterator position, const value_type &val);
		// range (3)
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last);
	};

} // namespace ft
#endif