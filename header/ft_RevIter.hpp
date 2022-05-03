#ifndef FT_REVITER_HPP
#define FT_REVITER_HPP

#include "ft_Iter.hpp"
#include "ft_RandAccessIter.hpp"

namespace ft{
	template<class Iterator>
	class reverse_iterator {
		public:
			typedef Iterator iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
			typedef typename iterator_traits<Iterator>::value_type value_type;
			typedef typename iterator_traits<Iterator>::difference_type difference_type;
			typedef typename iterator_traits<Iterator>::pointer pointer;
			typedef typename iterator_traits<Iterator>::reference reference;

			reverse_iterator(): _ptr(0) {}
			explicit reverse_iterator(Iterator it) : _ptr(it) {}
			template<class Iter> reverse_iterator (const reverse_iterator<Iter>& rev_it): _ptr(rev_it.base()) {}
			~reverse_iterator() {}

			Iterator base() const { return (_ptr); }

			reference   operator*() const { Iterator t = _ptr; return (*--t); }
			pointer     operator->() const { return &(operator*()); }
			reference   operator[](const difference_type n) const { return *(_ptr - n - 1); }

			template<class T>
			reverse_iterator    &operator=(const reverse_iterator<T> &inst) { _ptr = inst.base(); return (*this); }
			reverse_iterator    operator+(difference_type n) const { return (reverse_iterator((-n) + _ptr)); }
			reverse_iterator    &operator++() { --_ptr ; return *this; }
			reverse_iterator    operator++(int) { reverse_iterator t = *this ; ++(*this) ; return (t); }
			reverse_iterator    &operator+=(difference_type n) { _ptr -= n; return (*this); }

			reverse_iterator    operator-(difference_type n) const { return (reverse_iterator(n - _ptr)); }
			reverse_iterator    &operator--() { ++_ptr ; return *this; }
			reverse_iterator    operator--(int) { reverse_iterator t = *this ; --(*this) ; return (t); }
			reverse_iterator    &operator-=(difference_type n) { _ptr += n; return (*this); }

		protected:
			Iterator _ptr;
	};

	template <class Iterator>
	ft::reverse_iterator<Iterator> operator+(
			const typename ft::reverse_iterator<Iterator>::difference_type n, const ft::reverse_iterator<Iterator> &lhs) { return (lhs + n); }

	template <class Iterator>
	typename ft::reverse_iterator<Iterator>::difference_type operator-(
			const ft::reverse_iterator<Iterator> &lhs, const ft::reverse_iterator<Iterator> &rhs) { return (rhs.base() - lhs.base()); }

	template <class Iterator>
	bool operator==(const ft::reverse_iterator<Iterator> &lhs, const ft::reverse_iterator<Iterator> &rhs) { return (lhs.base() == rhs.base());}

	template <class Iterator>
	bool operator!=(const ft::reverse_iterator<Iterator> &lhs, const ft::reverse_iterator<Iterator> &rhs) { return (lhs.base() != rhs.base());}

	template <class Iterator>
	bool operator<(const ft::reverse_iterator<Iterator> &lhs, const ft::reverse_iterator<Iterator> &rhs) { return (lhs.base() < rhs.base());}

	template <class Iterator>
	bool operator>(const ft::reverse_iterator<Iterator> &lhs, const ft::reverse_iterator<Iterator> &rhs) { return (lhs.base() > rhs.base());}

	template <class Iterator>
	bool operator<=(const ft::reverse_iterator<Iterator> &lhs, const ft::reverse_iterator<Iterator> &rhs) { return lhs.base() <= rhs.base();}

	template <class Iterator>
	bool operator>=(const ft::reverse_iterator<Iterator> &lhs, const ft::reverse_iterator<Iterator> &rhs) { return lhs.base() >= rhs.base();}
}

#endif