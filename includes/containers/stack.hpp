#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
	protected:
		Container container;

	public:
		typedef Container container_type;
		typedef typename Container::value_type value_type;
		typedef typename Container::size_type size_type;
		typedef typename Container::reference reference;
		typedef typename Container::const_reference const_reference;

		stack(const container_type &ctnr = container_type()) : container(ctnr){};
		stack(const stack &other) : container(other.container){};
		stack &operator=(const stack &other) { container = other.container; };
		~stack(){};

		// ELEMENT ACCESS
		reference top() { return container.back(); };
		const_reference top() const { return container.back(); };

		// CAPACITY
		bool empty() const { return container.empty(); };
		size_type size() const { return container.size(); };

		// MODIFIERS
		void push(const value_type &value) { container.push_back(value); };
		void pop() { container.pop_back(); };
	};
	// NON-MEMBER FUNCTION OVERLOADS

	// RELATIONAL OPERATORS
	template <class T, class Container>
	bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return lhs.container == rhs.container;
	}
	template <class T, class Container>
	bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return lhs.container != rhs.container;
	}
	template <class T, class Container>
	bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return lhs.container < rhs.container;
	}
	template <class T, class Container>
	bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return lhs.container <= rhs.container;
	}
	template <class T, class Container>
	bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return lhs.container >= rhs.container;
	}
	template <class T, class Container>
	bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return lhs.container > rhs.container;
	}

} // namespace ft

#endif