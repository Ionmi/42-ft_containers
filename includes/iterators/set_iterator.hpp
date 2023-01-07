#ifndef SET_ITERATOR_HPP
#define SET_ITERATOR_HPP

#include "iterator.hpp"
#include "../RedBlackTree.hpp"
#include "../pairs.hpp"

namespace ft
{
	template <class set>
	class set_iterator //: public Iterator<typename std::iterator_traits<set *>::bidirectional_iterator_tag, typename set::value_type>
	{
		typedef typename rbt::RBnode<typename set::key_type, typename set::value_type> RBStruct;
		typedef typename set::key_type key_type;
		typedef RBStruct *nodePtr;
		typedef rbt::RBT<key_type, typename set::value_type, typename set::key_compare> RBtree;

	public:
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef typename set::value_type value_type;
		typedef typename set::difference_type difference_type;
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
		set_iterator() : node(nullptr){};
		set_iterator(nodePtr node) : node(node)
		{
			parentClass = static_cast<RBtree *>(node->parentClass);
		};
		set_iterator(const set_iterator &ref) : node(ref.node), parentClass(ref.parentClass){};
		set_iterator &operator=(const set_iterator &ref)
		{
			node = ref.node;
			parentClass = ref.parentClass;
			return *this;
		};
		~set_iterator(){};

		bool operator==(const set_iterator &rhs) const
		{
			return node == rhs.node;
		}
		bool operator!=(const set_iterator &rhs) const
		{
			return node != rhs.node;
		}

		set_iterator &operator++()
		{
			node = parentClass->findNext(node);
			return *this;
		}
		set_iterator operator++(int)
		{
			set_iterator it = *this;
			node = parentClass->findNext(node);
			return it;
		}
		set_iterator &operator--()
		{
			node = parentClass->findPrevious(node);
			return *this;
		}
		set_iterator operator--(int)
		{
			set_iterator it = *this;
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