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

		template <class Key, class T>
		struct RBnode
		{
			RBnode *parent;
			RBnode *right;
			RBnode *left;
			int color;
			Key key;
			T data;
			bool isEndType;
			void *parentClass;

			RBnode()
			{
				parent = nullptr;
				right = NIL;
				left = NIL;
				color = BLACK;
			};

			RBnode(RBnode *parent)
			{
				this->parent = parent;
				right = NIL;
				left = NIL;
				color = BLACK;
				isEndType = true;
			};

			RBnode(const Key &key, const T data)
			{
				this->key = key;
				this->data = data;
				parent = nullptr;
				right = NIL;
				left = NIL;
				color = RED;
			};
		}; // struct RBnode

		template <class Key, class T, class Compare = std::less<Key> >
		class RBT
		{
		public:
			typedef RBnode<Key, T> *pointer;
			typedef std::allocator<RBnode<Key, T> > allocator_type;
			typedef typename allocator_type::size_type size_type;

		private:
			pointer root;
			pointer rend;
			pointer end;
			Compare compare;
			allocator_type allocator;
			size_type size;

		public:
			RBT();
			RBT(const RBT &rbt);
			~RBT();

			RBT<Key, Compare> &operator=(const RBT &rbt);

			void printTree();
			pointer insert(const Key, const T);
			pointer insertReplace(const Key, const T);
			T &find(Key);
			void remove(const Key);

			// GETTERS
			const pointer getNode(const Key key) const { return findNode(root, key); };
			const pointer getRoot() const { return root; };

			pointer findBegin() const;
			pointer findEnd() const;
			pointer findRbegin() const;
			pointer findRend() const;
			pointer findNext(pointer);
			pointer findPrevious(pointer);

		private:
			pointer insertNode(pointer, pointer &, const Key &, const T &);
			pointer findPredecessor(pointer);
			pointer findSuccessor(pointer);
			pointer findNode(pointer, Key) const;
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
		template <class Key, class T, class Compare>
		RBT<Key, T, Compare>::RBT() : root(NIL), compare(Compare()), size(0)
		{
			end = allocator.allocate(1);
			allocator.construct(end, RBnode<Key, T>(nullptr));
			rend = allocator.allocate(1);
			allocator.construct(rend, RBnode<Key, T>(nullptr));
		}

		template <class Key, class T, class Compare>
		RBT<Key, T, Compare>::RBT(const RBT &rbt) : compare(Compare())
		{
			copyRBT(rbt.root);
		}

		template <class Key, class T, class Compare>
		RBT<Key, T, Compare>::~RBT()
		{
			deleteTree(root);
			deallocateNode(end);
			deallocateNode(rend);
		}

		template <class Key, class T, class Compare>
		RBT<Key, Compare> &RBT<Key, T, Compare>::operator=(const RBT &rbt)
		{
			compare = rbt.compare;
			copyRBT(rbt.root);
		}

		template <class Key, class T, class Compare>
		void RBT<Key, T, Compare>::printTree()
		{
			if (root)
				printHelper(root, 0);
		}

		template <class Key, class T, class Compare>
		RBnode<Key, T> *RBT<Key, T, Compare>::findBegin() const
		{
			pointer tmp = root;
			while (tmp->left != NIL)
				tmp = tmp->left;
			return tmp;
		}

		template <class Key, class T, class Compare>
		RBnode<Key, T> *RBT<Key, T, Compare>::findEnd() const
		{
			pointer tmp = root;
			while (tmp->right != NIL)
				tmp = tmp->right;
			end->parent = tmp;
			return end;
		}

		template <class Key, class T, class Compare>
		RBnode<Key, T> *RBT<Key, T, Compare>::findRbegin() const
		{
			pointer tmp = root;
			while (tmp->right != NIL)
				tmp = tmp->right;
			return tmp;
		}

		template <class Key, class T, class Compare>
		RBnode<Key, T> *RBT<Key, T, Compare>::findRend() const
		{
			pointer tmp = root;
			while (tmp->left != NIL)
				tmp = tmp->left;
			rend->parent = tmp;
			return rend;
		}

		template <class Key, class T, class Compare>
		RBnode<Key, T> *RBT<Key, T, Compare>::findNext(pointer node)
		{
			pointer tmp;
			if (node->right)
			{
				tmp = node->right;
				while (tmp->left != NIL)
					tmp = tmp->left;
				return tmp;
			}
			if (node->parent == nullptr)
			{
				end->parent = node;
				return end;
			}
			if (node->parent->left == node)
				return node->parent;
			tmp = node;
			while (tmp->parent->right == tmp)
			{
				tmp = tmp->parent;
				if (tmp->parent == nullptr)
				{
					end->parent = node;
					return end;
				}
			}
			return tmp->parent;
		}

		template <class Key, class T, class Compare>
		RBnode<Key, T> *RBT<Key, T, Compare>::findPrevious(pointer node)
		{
			pointer tmp;
			if (node->left)
			{
				tmp = node->left;
				while (tmp->right != NIL)
					tmp = tmp->right;
				return tmp;
			}
			if (node->parent == nullptr)
			{
				rend->parent = node;
				return rend;
			}
			if (node->parent->right == node)
				return node->parent;
			tmp = node;
			while (tmp->parent->left == tmp)
			{
				tmp = tmp->parent;
				if (tmp->parent == nullptr)
				{
					rend->parent = node;
					return rend;
				}
			}
			return tmp->parent;
		}

		template <class Key, class T, class Compare>
		RBnode<Key, T> *RBT<Key, T, Compare>::insert(const Key key, const T data)
		{
			if (root == NIL)
			{
				root = allocator.allocate(1);
				allocator.construct(root, RBnode<Key, T>(key, data));
				root->color = BLACK;
				root->parentClass = this;
				size++;
				return root;
			}
			if (++size > allocator.max_size())
				throw std::length_error("red black binary tree");
			return insertNode(nullptr, root, key, data);
		}

		template <class Key, class T, class Compare>
		RBnode<Key, T> *RBT<Key, T, Compare>::insertReplace(const Key key, const T data)
		{
			pointer found = findNode(key);
			if (found == nullptr)
				return insert(key, data);
			found->data = data;
			return found;
		}

		template <class Key, class T, class Compare>
		T &RBT<Key, T, Compare>::find(Key key)
		{
			pointer found = findNode(root, key);
			return found != nullptr ? found->data : 0;
		}

		template <class Key, class T, class Compare>
		void RBT<Key, T, Compare>::remove(const Key key)
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
		template <class Key, class T, class Compare>
		RBnode<Key, T> *RBT<Key, T, Compare>::insertNode(pointer parent, pointer &node, const Key &key, const T &data)
		{
			if (node == NIL)
			{
				node = allocator.allocate(1);
				allocator.construct(node, RBnode<Key, T>(key, data));
				node->parent = parent;
				node->parentClass = this;
				insertFix(node);
				return node;
			}
			if (compare(key, node->key))
				return insertNode(node, node->left, key, data);
			return insertNode(node, node->right, key, data);
		}

		template <class Key, class T, class Compare>
		RBnode<Key, T> *RBT<Key, T, Compare>::findNode(pointer node, const Key key) const
		{
			if (node == NIL)
				return node;

			if (node->key == key)
				return node;

			if (key < node->key)
				return findNode(node->left, key);

			return findNode(node->right, key);
		}

		template <class Key, class T, class Compare>
		RBnode<Key, T> *RBT<Key, T, Compare>::findPredecessor(pointer node)
		{
			node = node->left;
			while (node->right != NIL)
				node = node->right;
			return node;
		}

		template <class Key, class T, class Compare>
		RBnode<Key, T> *RBT<Key, T, Compare>::findSuccessor(pointer node)
		{
			node = node->right;
			while (node->left != NIL)
				node = node->left;
			return node;
		}

		template <class Key, class T, class Compare>
		void RBT<Key, T, Compare>::printHelper(pointer &root, int space)
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

		template <class Key, class T, class Compare>
		void RBT<Key, T, Compare>::leftRotate(pointer x)
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

		template <class Key, class T, class Compare>
		void RBT<Key, T, Compare>::rightRotate(pointer x)
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

		template <class Key, class T, class Compare>
		void RBT<Key, T, Compare>::insertFix(pointer current)
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

		template <class Key, class T, class Compare>
		void RBT<Key, T, Compare>::removeRecolor(pointer current)
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

		template <class Key, class T, class Compare>
		void RBT<Key, T, Compare>::fixDoubleBlack(pointer current)
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

		template <class Key, class T, class Compare>
		void RBT<Key, T, Compare>::transplant(pointer u, pointer v) // U to be removed for -> V
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

		template <class Key, class T, class Compare>
		void RBT<Key, T, Compare>::deleteTree(pointer node)
		{
			if (node == NIL)
				return;

			deleteTree(node->left);
			deleteTree(node->right);

			deallocateNode(node);
		}

		template <class Key, class T, class Compare>
		void RBT<Key, T, Compare>::deallocateNode(pointer node)
		{
			allocator.destroy(node);
			allocator.deallocate(node, 1);
		}

		template <class Key, class T, class Compare>
		void RBT<Key, T, Compare>::copyRBT(pointer node)
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
