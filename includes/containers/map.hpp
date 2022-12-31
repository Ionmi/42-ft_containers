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
		// typedef RBtree<ft::pair<const Key, T> > RBnode;

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
	};

} // namespace ft

#endif