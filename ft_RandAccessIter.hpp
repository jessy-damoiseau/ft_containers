#ifndef FT_RANDACCESSITER_HPP
# define FT_RANDACCESSITER_HPP

# include "ft_Iter.hpp"

namespace ft {
	template<class T>
	class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T> {
		public:
			typedef T																			value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category	iterator_category;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer			pointer;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference			reference;

			random_access_iterator() : _ptr(NULL) {}
			random_access_iterator(pointer src) : _ptr(src) {}
			random_access_iterator(const random_access_iterator &src) : _ptr(src._ptr) {}
			virtual ~random_access_iterator() {}

			pointer base() const { return ( _ptr ); }

			operator	random_access_iterator<const value_type>() const { return ( random_access_iterator<const value_type>(_ptr) ); }

			random_access_iterator	&operator=(const random_access_iterator &src) { _ptr = src.base(); return ( *this ); }
			reference				operator*() const { return ( *_ptr ); }
			pointer					operator->() const { return (&(operator*())); }
			reference				operator[](const difference_type n ) { return ( *(_ptr + n) ); }
			random_access_iterator	&operator++() { ++_ptr; return ( *this ); }
			random_access_iterator	&operator--() { --_ptr; return ( *this ); }
			random_access_iterator	operator++( int ) { random_access_iterator tmp = *this; _ptr++; return (tmp); }
			random_access_iterator	operator--(int){ random_access_iterator tmp = *this; _ptr--; return (tmp); }
			random_access_iterator	operator+(difference_type n ) const { return (_ptr + n); }
			random_access_iterator	operator-(difference_type n ) const { return (_ptr - n); }
			difference_type			operator+(const random_access_iterator& rhs) const { return (_ptr + rhs._ptr); }
			difference_type			operator-(const random_access_iterator& rhs) const { return (_ptr - rhs._ptr); }
			random_access_iterator	&operator+=(difference_type n ) { _ptr += n; return (*this); }
			random_access_iterator	&operator-=(difference_type n ) { _ptr -= n; return (*this); }

			bool	operator==( const random_access_iterator &rhs ) const { return ( _ptr == rhs._ptr ); }
			bool	operator!=( const random_access_iterator &rhs ) const { return ( _ptr != rhs._ptr ); }
			bool	operator<( const random_access_iterator  &rhs ) const { return ( _ptr < rhs._ptr ); }
			bool	operator<=( const random_access_iterator &rhs ) const { return ( _ptr <= rhs._ptr ); }
			bool	operator>( const random_access_iterator &rhs ) const { return ( _ptr > rhs._ptr ); }
			bool	operator>=( const random_access_iterator &rhs ) const { return ( _ptr >= rhs._ptr ); }

		protected:
			pointer _ptr;
	};

	template<typename T>
	ft::random_access_iterator<T>	operator+(typename ft::random_access_iterator<T>::difference_type n, const ft::random_access_iterator<T> &rhs) { return (rhs.base() + n); }
	template<typename T>
	ft::random_access_iterator<T>	operator-(typename ft::random_access_iterator<T>::difference_type n, const ft::random_access_iterator<T> &rhs) { return (rhs.base() - n); }
	template<typename T1, typename T2>
	typename ft::random_access_iterator<T1>::difference_type	operator+(const ft::random_access_iterator<T1> &lhs, const ft::random_access_iterator<T2> &rhs) { return ( lhs.base() + rhs.base() ); }
	template<typename T1, typename T2>
	typename ft::random_access_iterator<T1>::difference_type	operator-(const ft::random_access_iterator<T1> &lhs, const ft::random_access_iterator<T2> &rhs) { return ( lhs.base() - rhs.base() ); }
	template<typename T1, typename T2>
	bool	operator==( const ft::random_access_iterator<T1> &lhs, const ft::random_access_iterator<T2> &rhs ) { return ( lhs.base() == rhs.base() ); }
	template<typename T1, typename T2>
	bool	operator!=( const ft::random_access_iterator<T1> &lhs, const ft::random_access_iterator<T2> &rhs ) { return ( lhs.base() != rhs.base() ); }
	template<typename T1, typename T2>
	bool	operator<( const ft::random_access_iterator<T1> &lhs, const ft::random_access_iterator<T2> &rhs ) { return ( lhs.base() < rhs.base() ); }
	template<typename T1, typename T2>
	bool	operator<=( const ft::random_access_iterator<T1> &lhs, const ft::random_access_iterator<T2> &rhs ) { return ( lhs.base() <= rhs.base() ); }
	template<typename T1, typename T2>
	bool	operator>( const ft::random_access_iterator<T1> &lhs, const ft::random_access_iterator<T2> &rhs ) { return ( lhs.base() > rhs.base() ); }
	template<typename T1, typename T2>
	bool	operator>=( const ft::random_access_iterator<T1> &lhs, const ft::random_access_iterator<T2> &rhs ) { return ( lhs.base() >= rhs.base() ); }
}
#endif