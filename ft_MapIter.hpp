#ifndef FT_MAPITER_HPP
# define FT_MAPITER_HPP

# include "ft_TreeStruct.hpp"
# include "ft_Iter.hpp"

namespace ft {
	template<typename T>
	class map_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
	{
	public:
		typedef T*																						ptr;
		typedef typename T::value_type																	value_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type		difference_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer				pointer;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference			reference;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;


		map_iterator() : _Ptr(0) {}
		map_iterator(ptr Ptr) : _Ptr(Ptr) {}
		map_iterator(ptr Ptr, ptr parent) : _Ptr(Ptr), _parent(parent) {}


		map_iterator(const map_iterator &src) : _Ptr(src._Ptr), _parent(src._parent) {}


		map_iterator	&operator=(const map_iterator &rhs)
		{
			if (*this != rhs)
				_Ptr = rhs._Ptr;
			_parent = rhs._parent;
			return ( *this );
		}

		virtual ~map_iterator() {}

		reference	operator*( void ) const { return ( _Ptr->Stock ); }
		pointer	operator->( void ) const { return ( &( operator*() ) );}
		ptr	base() const { return ( _Ptr ); }
		ptr	pbase() const { return (_parent); }

		map_iterator	&operator++()
		{
			if (_Ptr != NULL) {
				if (_Ptr->right) {
					_Ptr = _Ptr->right;
					while (_Ptr->left)
						_Ptr = _Ptr->left;
				} else {
					while (_Ptr->prev && _Ptr->prev->right == _Ptr)
						_Ptr = _Ptr->prev;
					_Ptr = _Ptr->prev;
				}
			}
			return ( *this );
		}

		map_iterator	operator++(int)
		{
			map_iterator tmp = *this;
			operator++();
			return ( tmp );
		}

		map_iterator	&operator--()
		{
			if (_Ptr != NULL)
			{
				_parent = _Ptr;
				if (_Ptr->left)
				{
					_Ptr = _Ptr->left;
					while (_Ptr->right)
						_Ptr = _Ptr->right;
				}
				else
				{
					while (_Ptr->prev && _Ptr->prev->left == _Ptr)
						_Ptr = _Ptr->prev;
					_Ptr = _Ptr->prev;
				}
			}
			else
				_Ptr = _parent;

			return ( *this );
		}

		map_iterator	operator--(int)
		{
			map_iterator tmp = *this;
			operator--();
			return ( tmp );
		}

		bool operator==(const map_iterator &rhs) const { return ( _Ptr == rhs._Ptr ); }
		bool operator!=(const map_iterator &rhs) const { return ( _Ptr != rhs._Ptr ); }

	private:
		ptr	_Ptr;
		ptr	_parent;
	};


	template<typename T>
	class map_const_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
	{
	public:
		typedef T*																						ptr;
		typedef typename T::value_type const															value_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type		difference_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer				pointer;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference			reference;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;


		map_const_iterator() : _Ptr(0) {}
		map_const_iterator(ptr Ptr) : _Ptr(Ptr) {}
		map_const_iterator(ptr Ptr, ptr parent) : _Ptr(Ptr), _parent(parent) {}

		template<class U>
		map_const_iterator(const U &src) : _Ptr(src.base()), _parent(src.pbase()) {}
		map_const_iterator(const map_const_iterator &src) : _Ptr(src._Ptr), _parent(src._parent) {}


		map_const_iterator	&operator=(const map_const_iterator &rhs)
		{
			if (*this != rhs)
				_Ptr = rhs._Ptr;
			_parent = rhs._parent;
			return ( *this );
		}

		virtual ~map_const_iterator() {}

		reference	operator*( void ) const { return ( _Ptr->Stock ); }
		pointer	operator->( void ) const { return ( &( operator*() ) );}
		ptr	base() const { return ( _Ptr ); }
		ptr	pbase() const { return (_parent); }

		map_const_iterator	&operator++()
		{
			if (_Ptr != NULL)
			{
				if (_Ptr->right)
				{
					_Ptr = _Ptr->right;
					while (_Ptr->left)
						_Ptr = _Ptr->left;
				}
				else
				{
					while (_Ptr->prev && _Ptr->prev->right == _Ptr)
						_Ptr = _Ptr->prev;
					_Ptr = _Ptr->prev;
				}
			}
			return ( *this );
		}

		map_const_iterator	operator++(int)
		{
			map_const_iterator tmp = *this;
			operator++();
			return ( tmp );
		}

		map_const_iterator	&operator--()
		{
			if (_Ptr != NULL)
			{
				_parent = _Ptr;
				if (_Ptr->left)
				{
					_Ptr = _Ptr->left;
					while (_Ptr->right)
						_Ptr = _Ptr->right;
				}
				else
				{
					while (_Ptr->prev && _Ptr->prev->left == _Ptr)
						_Ptr = _Ptr->prev;
					_Ptr = _Ptr->prev;
				}
			}
			else
				_Ptr = _parent;
			return ( *this );
		}

		map_const_iterator	operator--(int)
		{
			map_const_iterator tmp = *this;
			operator--();
			return ( tmp );
		}

		bool operator==(const map_const_iterator &rhs) const { return ( _Ptr == rhs._Ptr ); }
		bool operator!=(const map_const_iterator &rhs) const { return ( _Ptr != rhs._Ptr ); }

	private:
		ptr	_Ptr;
		ptr	_parent;
	};


}

#endif