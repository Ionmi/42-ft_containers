#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
	protected:
		Container c;

	public:
		typedef Container container_type;
		typedef typename Container::value_type value_type;
		typedef typename Container::size_type size_type;
		typedef typename Container::reference reference;
		typedef typename Container::const_reference const_reference;

		stack(const container_type &ctnr = container_type()) : c(ctnr){};
		stack(const stack &other) : c(other.c){};
		stack &operator=(const stack &other) { c = other.c; };
		~stack(){};

		// ELEMENT ACCESS
		reference top() { return c.back(); };
		const_reference top() const { return c.back(); };

		// CAPACITY
		bool empty() const { return c.empty(); };
		size_type size() const { return c.size(); };

		// MODIFIERS
		void push(const value_type &value) { c.push_back(value); };
		void pop() { c.pop_back(); };

		template <class U, class Container2>
		friend bool operator==(const stack<U, Container2> &lhs, const stack<U, Container2> &rhs);

		template <class U, class Container2>
		friend bool operator!=(const stack<U, Container2> &lhs, const stack<U, Container2> &rhs);

		template <class U, class Container2>
		friend bool operator<(const stack<U, Container2> &lhs, const stack<U, Container2> &rhs);

		template <class U, class Container2>
		friend bool operator<=(const stack<U, Container2> &lhs, const stack<U, Container2> &rhs);

		template <class U, class Container2>
		friend bool operator>(const stack<U, Container2> &lhs, const stack<U, Container2> &rhs);

		template <class U, class Container2>
		friend bool operator>=(const stack<U, Container2> &lhs, const stack<U, Container2> &rhs);
	};
	// NON-MEMBER FUNCTION OVERLOADS

	// RELATIONAL OPERATORS
	template <class U, class Container2>
	bool operator==(const stack<U, Container2> &lhs, const stack<U, Container2> &rhs)
	{
		return lhs.c == rhs.c;
	}
	template <class U, class Container2>
	bool operator!=(const stack<U, Container2> &lhs, const stack<U, Container2> &rhs)
	{
		return lhs.c != rhs.c;
	}
	template <class U, class Container2>
	bool operator<(const stack<U, Container2> &lhs, const stack<U, Container2> &rhs)
	{
		return lhs.c < rhs.c;
	}
	template <class U, class Container2>
	bool operator<=(const stack<U, Container2> &lhs, const stack<U, Container2> &rhs)
	{
		return lhs.c <= rhs.c;
	}
	template <class U, class Container2>
	bool operator>(const stack<U, Container2> &lhs, const stack<U, Container2> &rhs)
	{
		return lhs.c > rhs.c;
	}
	template <class U, class Container>
	bool operator>=(const stack<U, Container> &lhs, const stack<U, Container> &rhs)
	{
		return lhs.c >= rhs.c;
	}

} // namespace ft

#endif