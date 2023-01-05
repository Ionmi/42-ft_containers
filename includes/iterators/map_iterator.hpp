#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "iterator.hpp"
#include "../RedBlackTree.hpp"
#include "../pairs.hpp"

namespace ft
{
	template <class map>
	class map_iterator //: public Iterator<typename std::iterator_traits<map *>::bidirectional_iterator_tag, typename map::value_type>
	{
		typedef typename rbt::RBnode<typename map::key_type, typename map::value_type> RBStruct;
		typedef typename map::key_type key_type;
		typedef RBStruct *nodePtr;
		typedef rbt::RBT<key_type, typename map::value_type, typename map::key_compare> RBtree;

	public:
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef typename map::value_type value_type;
		typedef typename map::difference_type difference_type;
		typedef std::allocator<RBStruct> allocator_type;
		typedef value_type &reference;
		typedef value_type *pointer;

	private:
		nodePtr node;
		// nodePtr end;
		// nodePtr rend;
		allocator_type allocator;
		RBtree *parentClass;

	public:
		map_iterator() : node(nullptr){};
		map_iterator(nodePtr node) : node(node)
		{
			parentClass = static_cast<RBtree *>(node->parentClass);
		};
		map_iterator(const map_iterator &ref) : node(ref.node), parentClass(ref.parentClass){};
		map_iterator &operator=(const map_iterator &ref)
		{
			node = ref.node;
			parentClass = ref.parentClass;
			return *this;
		};
		~map_iterator(){};

		bool operator==(const map_iterator &rhs) const
		{
			return node == rhs.node;
		}
		bool operator!=(const map_iterator &rhs) const
		{
			return node != rhs.node;
		}

		map_iterator &operator++()
		{
			node = parentClass->findNext(node);
			return *this;
		}
		map_iterator operator++(int)
		{
			map_iterator it = *this;
			node = parentClass->findNext(node);
			return it;
		}
		map_iterator &operator--()
		{
			node = parentClass->findPrevious(node);
			return *this;
		}
		map_iterator operator--(int)
		{
			map_iterator it = *this;
			node = parentClass->findPrevious(node);
			return it;
		}
		reference operator*() const { return node->data; }
		pointer operator->() const
		{
			return &node->data;
		}
	};
} // namespace ft

#endif