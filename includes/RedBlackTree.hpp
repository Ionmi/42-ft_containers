#ifndef REDBLACKTREE_HPP
#define REDBLACKTREE_HPP

#include <iostream>
#include "pairs.hpp"

#define NIL nullptr
#define RED 0
#define BLACK 1

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

		template <class Key>
		RBnode<Key> *findNext(const RBnode<Key> *node)
		{
			RBnode<Key> *tmp;
			if (node->right)
			{
				tmp = node->right;
				while (tmp->left != NIL)
					tmp = tmp->left;
				cout << "address dentro:" << tmp << "$\n";
				cout << reinterpret_cast<std::pair<int, int> *>(&tmp->data)->first << "$\n";
				return tmp;
			}
			if (node->parent == nullptr)
				return nullptr;
			tmp = node->parent;
			while (tmp->right == tmp)
			{
				if (tmp->parent == nullptr)
					return nullptr;
				tmp = tmp->parent;
			}
			if (tmp->right == node)
				return nullptr;
			return tmp;
		}

		template <class Key>
		RBnode<Key> *findPrevious(const RBnode<Key> *node)
		{
			RBnode<Key> *tmp;
			if (node->left)
			{
				tmp = node->left;
				while (tmp->right != NIL)
					tmp = tmp->right;
				return tmp;
			}
			if (node->parent == nullptr)
				return nullptr;
			tmp = node->parent;
			while (tmp->left == tmp)
			{
				if (tmp->parent == nullptr)
					return nullptr;
				tmp = tmp->parent;
			}
			if (tmp->left == node)
				return nullptr;
			return tmp;
		}

		template <class Key, class Compare = std::less<Key> >
		class RBT
		{
		public:
			typedef RBnode<Key> *pointer;
			typedef std::allocator<RBnode<Key> > allocator_type;
			typedef typename allocator_type::size_type size_type;

		private:
			pointer root;
			Compare compare;
			allocator_type allocator;
			size_type size;

		public:
			RBT();
			RBT(const RBT &rbt);
			~RBT();

			RBT<Key, Compare> &operator=(const RBT &rbt);

			void printTree();
			void insert(const Key, uintptr_t data = 0);
			void insertReplace(const Key, uintptr_t data = 0);
			uintptr_t find(Key);
			void remove(const Key);

			// GETTERS
			const pointer &getRoot() const { return root; }

		private:
			void insertNode(pointer, pointer &, const Key, uintptr_t);
			pointer findNode(pointer, Key);
			pointer findPredecessor(pointer);
			pointer findSuccessor(pointer);
			void printHelper(pointer &, int);
			void leftRotate(pointer);
			void rightRotate(pointer);
			void insertFix(pointer);
			void removeRecolor(pointer);
			void fixDoubleBlack(pointer);
			void transplant(pointer, pointer);
			void deleteTree(pointer);
			void deallocateNode(pointer);
			void copyRBT(pointer);
		}; // class RBT

		// PUBLIC
		template <class Key, class Compare>
		RBT<Key, Compare>::RBT() : root(NIL), compare(Compare()), size(0) {}

		template <class Key, class Compare>
		RBT<Key, Compare>::RBT(const RBT &rbt) : compare(Compare())
		{
			copyRBT(rbt.root);
		}

		template <class Key, class Compare>
		RBT<Key, Compare>::~RBT() { deleteTree(root); }

		template <class Key, class Compare>
		RBT<Key, Compare> &RBT<Key, Compare>::operator=(const RBT &rbt)
		{
			compare = rbt.compare;
			copyRBT(rbt.root);
		}

		template <class Key, class Compare>
		void RBT<Key, Compare>::printTree()
		{
			if (root)
				printHelper(root, 0);
		}

		template <class Key, class Compare>
		void RBT<Key, Compare>::insert(const Key key, uintptr_t data)
		{
			if (root == NIL)
			{
				root = allocator.allocate(1);
				allocator.construct(root, RBnode<Key>(key, data));
				root->color = BLACK;
				size++;
				return;
			}
			if (++size > allocator.max_size())
				throw std::length_error("red black binary tree");
			insertNode(nullptr, root, key, data);
		}

		template <class Key, class Compare>
		void RBT<Key, Compare>::insertReplace(const Key key, uintptr_t data)
		{
			pointer found = find(key);
			if (found == NULL)
			{
				insert(key, data);
				return;
			}
			found->data = data;
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
		remove:
			pointer found = findNode(root, key);

			if (found == nullptr)
				return;
			if (found->left && found->right)
			{
				pointer successor = findSuccessor(found);
				std::swap(found->key, successor->key);
				std::swap(found->data, successor->data);
				found = successor;
			}
			pointer x = found->left == NIL ? found->right : found->left;
			if (found->parent == nullptr)
			{
				deallocateNode(found);
				root = x;
				size--;
				goto remove;
			}
			if (x == NIL)
			{
				if (found->color == BLACK)
					fixDoubleBlack(found);
				else
				{
					pointer sibling = found->parent->left == NIL
										  ? found->parent->right
										  : found->parent->left;
					if (sibling != NIL)
						sibling->color = RED;
				}
				transplant(found, x);
			}
			else
			{
				transplant(found, x);
				found->color == BLACK && x->color == BLACK
					? fixDoubleBlack(x)
					: (void)(x->color = BLACK);
			}
			deallocateNode(found);
			size--;
			goto remove;
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
		RBnode<Key> *RBT<Key, Compare>::findPredecessor(pointer node)
		{
			node = node->left;
			while (node->right != NIL)
				node = node->right;
			return node;
		}

		template <class Key, class Compare>
		RBnode<Key> *RBT<Key, Compare>::findSuccessor(pointer node)
		{
			node = node->right;
			while (node->left != NIL)
				node = node->left;
			return node;
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
		void RBT<Key, Compare>::removeRecolor(pointer current)
		{
			while (current != root && current->color != RED)
			{
				pointer sibling = current == current->parent->left
									  ? current->parent->right
									  : current->parent->left;
				sibling->color = RED;
				current = current->parent;
			}
		}

		template <class Key, class Compare>
		void RBT<Key, Compare>::fixDoubleBlack(pointer current)
		{
			if (current->parent == nullptr)
				return;

			pointer parent = current->parent;
			pointer sibling = current->parent->left == current
								  ? current->parent->right
								  : current->parent->left;
			if (sibling == NIL)
			{
				fixDoubleBlack(parent);
				return;
			}
			if (sibling->color == RED)
			{
				parent->color = RED;
				sibling->color = BLACK;
				sibling->parent->left == sibling
					? rightRotate(parent)
					: leftRotate(parent);
				fixDoubleBlack(current);
				return;
			}
			// 2 black children
			if ((sibling->left == NIL || sibling->left->color == BLACK) &&
				(sibling->right == NIL || sibling->right->color == BLACK))
			{
				sibling->color = RED;
				parent->color == BLACK
					? fixDoubleBlack(parent)
					: (void)(parent->color = BLACK);
				return;
			}
			// at least 1 red children
			bool isSiblingLeft = sibling->parent->left == sibling ? true : false;
			// left sibling is red
			if (sibling->left != NIL && sibling->left->color == RED)
			{
				if (isSiblingLeft)
				{
					// left left
					sibling->left->color = sibling->color;
					sibling->color = parent->color;
					rightRotate(parent);
				}
				else
				{
					// right left
					sibling->left->color = parent->color;
					rightRotate(sibling);
					leftRotate(parent);
				}
				parent->color = BLACK;
				return;
			}
			if (isSiblingLeft)
			{
				// left right
				sibling->right->color = parent->color;
				leftRotate(sibling);
				rightRotate(parent);
			}
			else
			{
				// right right
				sibling->right->color = sibling->color;
				sibling->color = parent->color;
				leftRotate(parent);
			}
			parent->color = BLACK;
		}

		template <class Key, class Compare>
		void RBT<Key, Compare>::transplant(pointer u, pointer v) // U to be removed for -> V
		{
			if (v != NIL)
				v->parent = u->parent;

			if (u->parent == nullptr)
			{
				root = v;
				return;
			}

			u == u->parent->left
				? u->parent->left = v
				: u->parent->right = v;
		}

		template <class Key, class Compare>
		void RBT<Key, Compare>::deleteTree(pointer node)
		{
			if (node == NIL)
				return;

			deleteTree(node->left);
			deleteTree(node->right);

			deallocateNode(node);
		}

		template <class Key, class Compare>
		void RBT<Key, Compare>::deallocateNode(pointer node)
		{
			allocator.destroy(node);
			allocator.deallocate(node, 1);
		}

		template <class Key, class Compare>
		void RBT<Key, Compare>::copyRBT(pointer node)
		{
			if (!node)
				return;
			inorder(node->left);
			insert(node->key, node->data);
			inorder(node->right);
		}
	} // namespace rbt
} // namespace ft

#endif
