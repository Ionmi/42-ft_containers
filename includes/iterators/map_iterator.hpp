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
		// class FindNext = rbt::findNext<typename map::key_type>;
		// class FindPrevious = rbt::findPrevious<typename map::key_type>;
		typedef rbt::RBnode<typename map::key_type> *nodePtr;

	public:
		typedef typename map::value_type value_type;
		typedef typename map::difference_type difference_type;
		typedef typename map::pointer pointer;
		typedef typename map::reference reference;

	private:
		nodePtr node;

	public:
		map_iterator() : node(nullptr){};
		map_iterator(nodePtr node) : node(node){};
		map_iterator(const map_iterator &ref) : node(ref.node){};
		map_iterator &operator=(const map_iterator &ref)
		{
			node = ref.node;
			return *this;
		};

		bool operator==(const map_iterator &rhs) const { return node == rhs.node; }
		bool operator!=(const map_iterator &rhs) const { return node != rhs.node; }

		map_iterator &operator++()
		{
			node = rbt::findNext(node);
			return *this;
		}
		map_iterator operator++(int)
		{
			map_iterator it = *this;
			node = rbt::findNext(node);
			cout << " address fuera:" << node << "$\n";
			cout << "++ ->" << reinterpret_cast<value_type *>(&node->data)->first << "$\n";
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
		reference operator*() const { return *node; }
		pointer operator->() const
		{
			return reinterpret_cast<value_type *>(&node->data);
		}
		// pointer operator->() const { return reinterpret_cast<value_type>(this->data); }

		void hola()
		{
			nodePtr hola = rbt::findPrevious(node);
			while (hola != nullptr)
			{
				cout << "key: " << hola->key << "\n";
				hola = rbt::findNext(hola);
			}
		}
	};
} // namespace ft

#endif