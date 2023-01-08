#ifndef COMPARES_HPP
#define COMPARES_HPP

namespace ft
{
	template <bool B, class T = void>
	struct enable_if
	{
	};

	template <class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	template <class T>
	struct is_integral : public std::integral_constant<bool, false>
	{
	};
	template <>
	struct is_integral<char> : public std::integral_constant<bool, true>
	{
	};
	template <>
	struct is_integral<char16_t> : public std::integral_constant<bool, true>
	{
	};
	template <>
	struct is_integral<char32_t> : public std::integral_constant<bool, true>
	{
	};
	template <>
	struct is_integral<wchar_t> : public std::integral_constant<bool, true>
	{
	};
	template <>
	struct is_integral<signed char> : public std::integral_constant<bool, true>
	{
	};
	template <>
	struct is_integral<short int> : public std::integral_constant<bool, true>
	{
	};
	template <>
	struct is_integral<int> : public std::integral_constant<bool, true>
	{
	};
	template <>
	struct is_integral<long int> : public std::integral_constant<bool, true>
	{
	};
	template <>
	struct is_integral<long long int> : public std::integral_constant<bool, true>
	{
	};
	template <>
	struct is_integral<unsigned char> : public std::integral_constant<bool, true>
	{
	};
	template <>
	struct is_integral<unsigned short int> : public std::integral_constant<bool, true>
	{
	};
	template <>
	struct is_integral<unsigned int> : public std::integral_constant<bool, true>
	{
	};
	template <>
	struct is_integral<unsigned long int> : public std::integral_constant<bool, true>
	{
	};
	template <>
	struct is_integral<unsigned long long int> : public std::integral_constant<bool, true>
	{
	};

	template <class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	};

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1 != last1)
		{
			if (!pred(*first1, *static_cast<InputIterator1>(first2)))
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								 InputIterator2 first2, InputIterator2 last2)
	{
    for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
    {
        if (*first1 < *first2)
            return true;
        if (*first2 < *first1)
            return false;
    }
 
    return (first1 == last1) && (first2 != last2);
}

	template <class InputIt1, class InputIt2, class Compare>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
								 InputIt2 first2, InputIt2 last2, Compare comp)
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, (void)++first2)
		{
			if (comp(*first1, *first2))
				return true;
			if (comp(*first2, *first1))
				return false;
		}

		return (first1 == last1) && (first2 != last2);
	};
};

#endif