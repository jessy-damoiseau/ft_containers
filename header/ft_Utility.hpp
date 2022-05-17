#ifndef FT_UTILITY_HPP
# define FT_UTILITY_HPP

namespace ft {

	template<bool, class T = void> struct enable_if {};
	template<class T> struct enable_if<true, T> { typedef T type; };

	template<class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
		for (; first1 != last1; first1++)
			if (!(*first1 == *first2++))
				return (false);
		return (true);
	}

	template<class InputIterator1, class InputIterator2, typename BinaryPredicate>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred) {
		for (; first1 != last1; first1++, first2++)
			if (!pred(*first1, *first2))
				return (false);
		return (true);
	}

	template<class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2) {
        for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
        {
            if (*first1 < *first2)
                return true;
            if (*first2 < *first1)
                return false;
        }
        return (first1 == last1) && (first2 != last2);
    }

    template <class InputIt1, class InputIt2, class Compare>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp) {
        for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
        {
            if (comp(*first1, *first2))
                return true;
            if (comp(*first2, *first1))
                return false;
        }
        return (first1 == last1) && (first2 != last2);
    }

	template<class T>
	void swap(T &a, T &b) {
		T tmp = b;
		b = a;
		a = tmp;
	}

	template <class Arg1, class Arg2, class Result>
	struct binary_function {
		typedef Arg1 first_argument_type;
		typedef Arg2 second_argument_type;
		typedef Result result_type;
	};

	template <class T> struct less : ft::binary_function<T, T, bool>
	{ bool operator() (const T &x, const T &y) const { return x < y; } };
}

#endif