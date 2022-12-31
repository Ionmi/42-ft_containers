#ifndef REDBLACKTREE_HPP
#define REDBLACKTREE_HPP

#include <iostream>
#include "pairs.hpp"

#define NIL nullptr // null pointer  or  pointer to sentinel node
// #define LEFT 0
// #define RIGHT 1
#define RED 0
#define BLACK 1
// #define left child[LEFT]
// #define right child[RIGHT]

namespace ft
{
	namespace rbt
	{
		template <class Key>
		struct RBnode
		{
			RBnode *parent;
			RBnode *right;
			RBnode *left;
			int color;
			Key key;
			uintptr_t data;

			RBnode()
			{
				parent = nullptr;
				right = NIL;
				left = NIL;
				color = BLACK;
			};

			RBnode(const Key &key, const uintptr_t data)
			{
				this->key = key;
				this->data = data;
				parent = nullptr;
				right = NIL;
				left = NIL;
				color = RED;
			};
		}; // struct RBnode

		// template <class Key, class Compare>
		template <class Key, class Compare = std::less<Key> >
		class RBT
		{
		public:
			typedef RBnode<Key> *pointer;
			typedef std::allocator<RBnode<Key> > allocator_type;
			// typedef Compare key_compare;
			// typedef Key key_type;

		private:
			pointer root;
			Compare compare;
			allocator_type allocator;

		public:
			RBT();
			~RBT();

			void printTree();
			void insert(const Key, uintptr_t data = 0);
			uintptr_t find(Key);
			void remove(const Key);

		private:
			void insertNode(pointer, pointer &, const Key, uintptr_t);
			pointer findNode(pointer, Key);
			void printHelper(pointer &, int);
			void leftRotate(pointer);
			void rightRotate(pointer);
			void insertFix(pointer);
			void deleteTree(pointer);
			void dealocateNode(pointer);
		}; // class RBT

		// PUBLIC
		template <class Key, class Compare>
		RBT<Key, Compare>::RBT() : root(NIL), compare(Compare()) {}

		template <class Key, class Compare>
		RBT<Key, Compare>::~RBT() { deleteTree(root); }

		template <class Key, class Compare>
		void RBT<Key, Compare>::printTree()
		{
			if (root)
			{
				printHelper(root, 0);
			}
		}

		template <class Key, class Compare>
		void RBT<Key, Compare>::insert(const Key key, uintptr_t data)
		{
			if (root == NIL)
			{
				root = new RBnode<Key>(key, data);
				root->color = BLACK;
				return;
			}
			insertNode(nullptr, root, key, data);
		}

		template <class Key, class Compare>
		uintptr_t RBT<Key, Compare>::find(Key key)
		{
			pointer found = findNode(root, key);
			return found != nullptr ? found->data : 0;
		}

		template <class Key, class Compare>
		void RBT<Key, Compare>::remove(const Key key)
		{
			pointer found = findNode(root, key);
			if (found == nullptr)
				return;
			if (found->color == RED && found->left == NIL && found->right == NIL)
			{
				found->parent->left == found
					? found->parent->left = NIL
					: found->parent->right = NIL;
				dealocateNode(found);
				return;
			}
			if (found == root && root->left == NIL && root->right == NIL)
			{
				dealocateNode(found);
				root = nullptr;
				return;
			}
		}

		// PRIVATE
		template <class Key, class Compare>
		void RBT<Key, Compare>::insertNode(pointer parent, pointer &node, const Key key, uintptr_t data)
		{
			if (node == NIL)
			{
				node = allocator.allocate(1);
				allocator.construct(node, RBnode<Key>(key, data));
				node->parent = parent;
				insertFix(node);
				return;
			}
			compare(key, node->key)
				? insertNode(node, node->left, key, data)
				: insertNode(node, node->right, key, data);
		}

		template <class Key, class Compare>
		RBnode<Key> *RBT<Key, Compare>::findNode(pointer node, Key key)
		{
			if (node == NIL)
				return node;

			if (node->key == key)
				return node;

			if (key < node->key)
				return findNode(node->left, key);

			return findNode(node->right, key);
		}

		template <class Key, class Compare>
		void RBT<Key, Compare>::printHelper(pointer &root, int space)
		{
			// Base case
			if (root == NULL)
				return;

			// Increase distance between levels
			space += 10;

			// Process right child first
			printHelper(root->right, space);

			// Print current node after space
			// count
			cout << "\n";
			for (int i = 10; i < space; i++)
				cout << " ";
			cout << root->key << (root->color == RED ? " (RED)" : " (BLACK)") << "\n";

			// Process left child
			printHelper(root->left, space);
		}

		template <class Key, class Compare>
		void RBT<Key, Compare>::leftRotate(pointer x)
		{
			pointer y = x->right;

			if (y->left)
				y->left->parent = x;
			x->right = y->left;
			y->left = x;
			y->parent = x->parent;
			x->parent = y;

			if (y->parent == nullptr)
			{
				root = y;
				return;
			}
			y->parent->right = y;
		}

		template <class Key, class Compare>
		void RBT<Key, Compare>::rightRotate(pointer x)
		{
			pointer y = x->left;

			if (y->right)
				y->right->parent = x;
			x->left = y->right;
			y->right = x;
			y->parent = x->parent;
			x->parent = y;

			if (y->parent == nullptr)
			{
				root = y;
				return;
			}
			y->parent->left = y;
		}

		template <class Key, class Compare>
		void RBT<Key, Compare>::insertFix(pointer current)
		{
			pointer uncle;
			pointer parent;
			pointer gParent;

			if (current->parent->color == BLACK)
				return;
			while ((parent = current->parent) != nullptr)
			{
				if (parent->color == BLACK)
					return;
				gParent = parent->parent;
				uncle = gParent->right == parent ? gParent->left : gParent->right;

				if (uncle != NIL && uncle->color == RED)
				{
					parent->color = BLACK;
					uncle->color = BLACK;
					gParent->color = RED;
					current = gParent;
					continue;
				}

				if (gParent->right == parent)
				{
					if (parent->left == current)
					{
						current = parent;
						rightRotate(current);
					}
					parent->color = BLACK;
					gParent->color = RED;
					leftRotate(gParent);
					continue;
				}
				if (parent->right == current)
				{
					current = parent;
					leftRotate(current);
				}
				parent->color = BLACK;
				gParent->color = RED;
				rightRotate(gParent);
			}
			root = current;
			root->color = BLACK;
		}

		template <class Key, class Compare>
		void RBT<Key, Compare>::deleteTree(pointer node)
		{
			if (node == NIL)
				return;

			deleteTree(node->left);
			deleteTree(node->right);

			dealocateNode(node);
		}

		template <class Key, class Compare>
		void RBT<Key, Compare>::dealocateNode(pointer node)
		{
			allocator.destroy(node);
			allocator.deallocate(node, 1);
		}
	} // namespace rbt
} // namespace ft

#endif
