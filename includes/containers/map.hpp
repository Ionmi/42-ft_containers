#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include "../pairs.hpp"
#include "../RedBlackTree.hpp"

// reinterpret_cast<uintptr_t>(ptr);
// reinterpret_cast<Data *>(raw);

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		typedef rbt::RBT<Key, Compare> RBtree;
		// typedef rbt::RBnode<Key> *pointer;

	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const Key, T> value_type;
		typedef Compare key_compare;
		typedef Allocator allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::size_type size_type;
		typedef typename allocator_type::difference_type difference_type;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		// typedef ft::iterator<ft::map_iterator> iterator;
		// typedef ft::iterator<ft::map_const_iterator> const_iterator;
		// typedef typename ft::reverse_iterator<ft::map_iterator> reverse_iterator;
		// typedef typename ft::reverse_iterator<ft::map_const_iterator> const_reverse_iterator;

	private:
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
		mapped_type& at (const key_type& k);

		const mapped_type& at (const key_type& k) const;

		mapped_type &operator[](const key_type &k);
		// MODIFIERS
		// single element (1)
		// pair<iterator, bool> insert(const value_type &val)
		// {
		// 	if (rbTree.find(val.key))
		// 		return ft::make_pair(val.second, false);

		// 	rbTree.insert(val.first, reinterpret_cast<uintptr_t>(val));
		// 	size++;
		// 	return ft::make_pair(val.second, true);
		// }
		// with hint (2)
		// iterator insert(iterator position, const value_type &val);
		// range (3)
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last);
	};

} // namespace ft

#endif