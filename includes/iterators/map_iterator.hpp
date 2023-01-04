#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "iterator.hpp"
#include "../RedBlackTree.hpp"
#include "../pairs.hpp"

namespace ft
{
	template <class map>
	class map_iterator
	{
		typedef typename rbt::RBnode<typename map::key_type, typename map::value_type> RBStruct;
		typedef typename map::key_type key_type;
		typedef RBStruct *nodePtr;

	public:
		typedef typename map::value_type value_type;
		typedef typename map::difference_type difference_type;
		typedef std::allocator<RBStruct> allocator_type;
		typedef value_type &reference;
		typedef value_type *pointer;

	private:
		nodePtr node;
		nodePtr end;
		nodePtr rend;
		allocator_type allocator;

	public:
		map_iterator() : node(nullptr)
		{
			end = allocator.allocate(1);
			allocator.construct(end, RBStruct(nullptr));
			rend = allocator.allocate(1);
			allocator.construct(rend, RBStruct(nullptr));
		};
		map_iterator(nodePtr node) : node(node)
		{
			end = allocator.allocate(1);
			allocator.construct(end, RBStruct(nullptr));
			rend = allocator.allocate(1);
			allocator.construct(rend, RBStruct(nullptr));
			if (node->isEndType)
				this->node = end;
		};
		map_iterator(const map_iterator &ref) : node(ref.node)
		{
			end = allocator.allocate(1);
			allocator.construct(end, RBStruct(ref.end));
			rend = allocator.allocate(1);
			allocator.construct(rend, RBStruct(ref.rend));
		};
		map_iterator &operator=(const map_iterator &ref)
		{
			node = ref.node;
			end->parent = ref.end->parent;
			rend = ref.rend->parent;

			return *this;
		};
		~map_iterator()
		{
			allocator.destroy(end);
			allocator.deallocate(end, 1);
			allocator.destroy(rend);
			allocator.deallocate(rend, 1);
		};

		bool operator==(const map_iterator &rhs) const
		{
			if (node != rhs.node && node == end && rhs.node == rhs.end)
				return true;
			return node == rhs.node;
		}
		bool operator!=(const map_iterator &rhs) const
		{
			cout << "------------------------\n";
			if (node == end && rhs.node == rhs.end)
				return true;
			return node != rhs.node;
			return !(node == rhs.node);
		}

		map_iterator &operator++()
		{
			node = rbt::findNext(node);
			cout << "next encontado\n";
				cout << "next == end"<< node->key << "\n";
			if (node->right == nullptr)
			{
				cout << "next == end\n";
				end->parent = node;
				node = end;
			}
			cout << "next devuelto\n";
			return *this;
		}
		map_iterator operator++(int)
		{
			map_iterator it = *this;
			node = rbt::findNext(node);
			return it;
		}
		map_iterator &operator--()
		{
			node = rbt::findPrevious(node);
			return *this;
		}
		map_iterator operator--(int)
		{
			map_iterator it = *this;
			node = rbt::findPrevious(node);
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