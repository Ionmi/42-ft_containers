#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "iterator.hpp"

namespace ft
{
	template <class map>
	class iterator
	{
	public:
		typedef typename map::value_type value_type;
		typedef typename map::difference_type difference_type;
		typedef typename map::pointer pointer;
		typedef typename map::reference reference;
	};
} // namespace ft

#endif