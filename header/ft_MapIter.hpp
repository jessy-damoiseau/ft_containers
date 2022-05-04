#ifndef FT_MAPITER_HPP
#define FT_MAPITER_HPP

#include "ft_TreeStruct.hpp"
#include "ft_Iter.hpp"

namespace ft {

	template <class T>
	class map_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T> {
		public:
			typedef T*                                                                          ptr;
			typedef typename T::value_type                                                      value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category iterator_category;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type   difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer           pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference         reference;

			map_iterator() : _Ptr(0){}
			map_iterator(ptr Ptr) : _Ptr(Ptr) {}
			map_iterator(const map_iterator &inst) : _Ptr(inst._Ptr){}
			virtual ~map_iterator() {}

			map_iterator    &operator=(const map_iterator &inst){
				_Ptr = inst._Ptr;
				return (*this);
			}

			reference   operator*() const  { return (_Ptr->Stock); }
			pointer     operator->() const { return (&(operator*())); }
			ptr         base() const { return (_Ptr); }

			map_iterator &operator++(){
				if (!_Ptr)
					return (*this);
				if (_Ptr->right){
					_Ptr = _Ptr->right;
					while (_Ptr->left)
						_Ptr = _Ptr->left;
				}
				else{
					while (_Ptr->prev && _Ptr->prev->right == _Ptr)
						_Ptr = _Ptr->prev;
					_Ptr = _Ptr->prev;
				}
				return (*this);
			}
			map_iterator &operator--(){
				if (!_Ptr)
					return (*this);
				if (_Ptr->left){
					_Ptr = _Ptr->left;
					while (_Ptr->right)
						_Ptr = _Ptr->right;
				}
				else{
					while (_Ptr->prev && _Ptr->prev->left == _Ptr)
						_Ptr = _Ptr->prev;
					_Ptr = _Ptr->prev;
				}
				return (*this);
			}
			map_iterator &operator++(int) {
				map_iterator tmp = *this;
				operator++();
				return (tmp);
			}
			map_iterator &operator--(int) {
				map_iterator tmp = *this;
				operator--();
				return (tmp);
			}

			bool operator==(const map_iterator &lhs) { return (_Ptr == lhs.base()); }
			bool operator!=(const map_iterator &lhs) { return (_Ptr != lhs.base()); }

		private:
			ptr _Ptr;
	};

	template <class T>
	class map_const_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T> {
		public:
			typedef T*                                                                          ptr;
			typedef typename T::value_type const                                                value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category iterator_category;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type   difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer           pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference         reference;

			map_const_iterator() : _Ptr(0){}
			map_const_iterator(ptr Ptr) : _Ptr(Ptr) {}
			map_const_iterator(const map_const_iterator &inst) : _Ptr(inst._Ptr){}
			virtual ~map_const_iterator() {}

			map_const_iterator    &operator=(const map_const_iterator &inst){
				_Ptr = inst._Ptr;
				return (*this);
			}

			reference   operator*() const { return (_Ptr->Stock); }
			pointer     operator->() const { return (&(operator*())); }
			ptr         base() const { return (_Ptr); }

			map_const_iterator &operator++(){
				if (!_Ptr)
					return (*this);
				if (_Ptr->right){
					_Ptr = _Ptr->right;
					while (_Ptr->left)
						_Ptr = _Ptr->left;
				}
				else{
					while (_Ptr->prev && _Ptr->prev->right == _Ptr)
						_Ptr = _Ptr->prev;
					_Ptr = _Ptr->prev;
				}
				return (*this);
			}
			map_const_iterator &operator--(){
				if (!_Ptr)
					return (*this);
				if (_Ptr->left){
					_Ptr = _Ptr->left;
					while (_Ptr->right)
						_Ptr = _Ptr->right;
				}
				else{
					while (_Ptr->prev && _Ptr->prev->left == _Ptr)
						_Ptr = _Ptr->prev;
					_Ptr = _Ptr->prev;
				}
				return (*this);
			}
			map_const_iterator &operator++(int) {
				map_const_iterator tmp = *this;
				operator++();
				return (tmp);
			}
			map_const_iterator &operator--(int) {
				map_const_iterator tmp = *this;
				operator--();
				return (tmp);
			}

			bool operator==(const map_const_iterator &lhs) const { return (_Ptr == lhs.base()); }
			bool operator!=(const map_const_iterator &lhs) const { return (_Ptr != lhs.base()); }

		private:
			ptr _Ptr;
	};
}

#endif