#ifndef FT_REVITER_HPP
# define FT_REVITER_HPP

# include "ft_Iter.hpp"
# include "ft_RandAccessIter.hpp"

namespace ft {
	template<class Iterator>
	class reverse_iterator {
		public:
			typedef Iterator													iterator_type;
			typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;
			typedef typename iterator_traits<iterator_type>::value_type			value_type;
			typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
			typedef typename iterator_traits<iterator_type>::pointer			pointer;
			typedef typename iterator_traits<iterator_type>::reference			reference;

			reverse_iterator() : _ptr(NULL) {}
			explicit reverse_iterator(iterator_type it) : _ptr(it) {}
			template<class Iter> reverse_iterator(const reverse_iterator<Iter>& rev_it) : _ptr(rev_it.base()) {}
			virtual ~reverse_iterator() {}

			iterator_type base() const { return (_ptr); }

			template<class T>
			reverse_iterator	&operator=(const reverse_iterator<T> &inst) { _ptr = inst.base(); return (*this); }
			reference			operator*() const { iterator_type t = _ptr; return (*--t); }
			pointer				operator->() const { return &(operator*()); }
			reference			operator[](const difference_type n) const { return *(_ptr - n - 1); }
			reverse_iterator	&operator++() { --_ptr; return (*this); }
			reverse_iterator	&operator--() { ++_ptr; return (*this); }
			reverse_iterator	operator++(int) { reverse_iterator t = *this; --_ptr ; return (t); }
			reverse_iterator	operator--(int) { reverse_iterator t = *this; ++_ptr ; return (t); }
			reverse_iterator	operator+(difference_type n) const { return (reverse_iterator(_ptr - n)); }
			reverse_iterator	operator-(difference_type n) const { return (reverse_iterator(_ptr + n)); }
			reverse_iterator	&operator+=(difference_type n) { _ptr -= n; return (*this); }
			reverse_iterator	&operator-=(difference_type n) { _ptr += n; return (*this); }

		protected:
			iterator_type _ptr;
	};

	template<typename T>
	ft::reverse_iterator<T> operator+(typename ft::reverse_iterator<T>::difference_type n, const ft::reverse_iterator<T> &rev_it) { return (reverse_iterator<T>(rev_it.base() - n)); }
	template<typename T1, typename T2>
	typename ft::reverse_iterator<T1>::difference_type operator-(const ft::reverse_iterator<T1> &lhs, const ft::reverse_iterator<T2> &rhs) { return (rhs.base() - lhs.base()); }
	template<typename T1, typename T2>
	bool operator==(const ft::reverse_iterator<T1> &lhs, const ft::reverse_iterator<T2> &rhs) { return (lhs.base() == rhs.base());}
	template<typename T1, typename T2>
	bool operator!=(const ft::reverse_iterator<T1> &lhs, const ft::reverse_iterator<T2> &rhs) { return (lhs.base() != rhs.base());}
	template<typename T1, typename T2>
	bool operator<(const ft::reverse_iterator<T1> &lhs, const ft::reverse_iterator<T2> &rhs) { return (lhs.base() > rhs.base());}
	template<typename T1, typename T2>
	bool operator<=(const ft::reverse_iterator<T1> &lhs, const ft::reverse_iterator<T2> &rhs) { return lhs.base() >= rhs.base();}
	template<typename T1, typename T2>
	bool operator>(const ft::reverse_iterator<T1> &lhs, const ft::reverse_iterator<T2> &rhs) { return (lhs.base() < rhs.base());}
	template<typename T1, typename T2>
	bool operator>=(const ft::reverse_iterator<T1> &lhs, const ft::reverse_iterator<T2> &rhs) { return lhs.base() <= rhs.base();}
}

#endif