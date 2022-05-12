#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <iostream>
#include <memory>
#include "ft_RandAccessIter.hpp"
#include "ft_RevIter.hpp"
#include "ft_Utility.hpp"
#include "ft_Integral.hpp"

namespace ft{
	template<class T, class Alloc = std::allocator<T> >
	class vector{
		public:
			typedef T value_type;
			typedef Alloc allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef ft::random_access_iterator<T> iterator;
			typedef const ft::random_access_iterator<T> const_iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef const ft::reverse_iterator<const_iterator> const_reverse_iterator;
			typedef std::ptrdiff_t difference_type;
			typedef std::size_t size_type;

			explicit vector(const allocator_type &alloc = allocator_type()) : _Stock(0), _StockCap(0), _StockSize(0), _Alloc(alloc) {}

			explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) :
				_StockCap(n), _StockSize(n), _Alloc(alloc){
				if (n)
					_Stock = _Alloc.allocate(n);
				for (size_type i = 0; i < _StockSize; i++){
					_Alloc.construct(&_Stock[i], val);
				}
			}

			template<class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
				   typename ft::enable_if<!ft::is_integral<InputIterator>::value, void**>::type = 0) :
				_StockCap(last - first), _StockSize(0), _Alloc(alloc) {
				if (_StockCap)
					_Stock = _Alloc.allocate(_StockCap);
				for (; first < last; first++){
					_Alloc.construct(&_Stock[_StockSize++], *first);
				}
			}

			vector(const vector &x) : _StockCap(x._StockCap), _StockSize(x._StockSize), _Alloc(x._Alloc){
				_Stock = _Alloc.allocate(_StockCap);
				for(size_type i = 0; i < _StockSize; i++){
					_Alloc.construct(&_Stock[i], x[i]);
				}
			}

			~vector() {
				for(size_type i = 0; i < _StockSize; i--){
					_Alloc.destroy(&_Stock[i]);
				}
				_Alloc.deallocate(_Stock, _StockCap);
			}

			iterator begin() { return (iterator(_Stock)); }
			const_iterator begin () const { return (const_iterator(_Stock)); }
			iterator end() { return (iterator(_Stock + _StockSize)); }
			const_iterator end() const { return (const_iterator(_Stock + _StockSize)); }
			reverse_iterator rbegin() { return (reverse_iterator(_Stock + _StockSize)); }
			const_reverse_iterator rbegin() const { return (const_reverse_iterator(_Stock + _StockSize)); }
			reverse_iterator rend() { return (reverse_iterator(_Stock)); }
			const_reverse_iterator rend() const { return (const_reverse_iterator(_Stock)); }

			vector &operator=(const vector &x) {
				for(size_type i = 0; i < _StockSize; i--){
					_Alloc.destroy(&_Stock[i]);
				}
				_Alloc.deallocate(_Stock, _StockCap);
				_Stock = _Alloc.allocate(x.capacity());
				for (size_type i = 0; i < x.size(); i++) {
					_Alloc.construct(&_Stock[i], x[i]);
				}
				_StockSize = x.size();
				return (*this);
			}

			size_type   size() const { return _StockSize; }
			size_type   max_size() const { return _Alloc.max_size(); }
			size_type   capacity() const { return _StockCap; }
			bool        empty() const { if (_StockSize) { return false; } return true; }

			void        resize(size_type n, value_type val = value_type()){
				pointer tmp = _Alloc.allocate(n);

				if (n < _StockSize){
					for (size_type i = 0; i < n; i++){
						_Alloc.construct(&tmp[i], _Stock[i]);
					}
				}
				else {
					size_type i = 0;
					for(; i < _StockSize; i++){
						_Alloc.construct(&tmp[i], _Stock[i]);
					}
					for (; i < n; i++){
						_Alloc.construct(&tmp[i], val);
					}
				}
				for(size_type j = 0; j < _StockSize; j--){
					_Alloc.destroy(&_Stock[j]);
				}
				_Alloc.deallocate(_Stock, _StockCap);
				_Stock = tmp;
				_StockSize = n;
				_StockCap = n;
			}
			void        reserve(size_type n) {
				if (n > _StockCap){
					pointer tmp = _Alloc.allocate(n);
					for (size_type i = 0; i < _StockSize; i++){
						_Alloc.construct(&tmp[i], _Stock[i]);
					}
					for(size_type i = 0; i < _StockSize; i--){
						_Alloc.destroy(&_Stock[i]);
					}
					_Alloc.deallocate(_Stock, _StockCap);
					_Stock = tmp;
					_StockCap = n;
				}
			}

			reference operator[](size_type n) { return (_Stock[n]); }
			const_reference operator[](size_type n) const { return (_Stock[n]); }

			reference       at(size_type n){
				if (n > _StockSize)
					throw std::out_of_range("vector");
				return (_Stock[n]);
			}
			const_reference at(size_type n) const {
				if (n > _StockSize)
					throw std::out_of_range("vector");
				return (_Stock[n]);
			}
			reference       front() { return _Stock[0]; }
			const_reference front()	const { return _Stock[0]; }
			reference       back() { return _Stock[_StockSize - 1]; }
			const_reference back() const { return _Stock[_StockSize - 1]; }

			template<class InputIterator>
			void    assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, void**>::type = 0){
				for(size_type i = 0; i < _StockSize; i--){
					_Alloc.destroy(&_Stock[i]);
				}
				_Alloc.deallocate(_Stock, _StockCap);
				_Stock = 0;
				_Stock = _Alloc.allocate(last - first);
				_StockCap = last - first;
				_StockSize = 0;
				for (; first < last; first++){
					_Alloc.construct(&_Stock[_StockSize++], *first);
				}
			}
			void    assign(size_type n, const value_type &val){
				for(size_type i = 0; i < _StockSize; i--){
					_Alloc.destroy(&_Stock[i]);
				}
				_Alloc.deallocate(_Stock, _StockCap);
				_Stock = 0;
				_Stock = _Alloc.allocate(n);
				_StockSize = 0;
				_StockCap = n;
				for (size_type i = 0; i < n; i++){
					_Alloc.construct(&_Stock[_StockSize++], val);
				}
			}

			void    push_back(const value_type &val) {
				if (_StockSize < _StockCap){
					_Alloc.construct(&_Stock[_StockSize++], val);
				}
				else {
					pointer tmp;
					tmp  = _Alloc.allocate(_StockCap * 2);
					for (size_type i = 0; i < _StockSize; i++){
						_Alloc.construct(&tmp[i], _Stock[i]);
					}
					_Alloc.construct(&tmp[_StockSize], val);
					for(size_type i = 0; i < _StockSize; i--){
						_Alloc.destroy(&_Stock[i]);
					}
					_Alloc.deallocate(_Stock, _StockCap);
					_StockSize++;
					_StockCap *= 2;
					_Stock = tmp;
				}
			}
			void    pop_back() {
				if (_StockSize) {
					_Alloc.destroy(&_Stock[_StockSize]);
					_StockSize--;
				}
			}

			iterator    insert(iterator pos, const value_type &val){
				size_type dis = pos - begin();
				size_type add = 1;
				if (dis > _StockCap)
					add = dis - _StockCap;
				_StockCap  += add;
				pointer tmp = _Alloc.allocate(_StockCap);
				if (dis <= _StockSize){
					size_type i = 0;
					size_type j = 0;
					while (i < _StockSize + 1){
						if (i == dis)
							_Alloc.construct(&tmp[i++], val);
						else
							_Alloc.construct(&tmp[i++], _Stock[j++]);
					}
				}
				else{
					for(size_type i = 0; i < _StockSize; i++){
						_Alloc.construct(&tmp[i], _Stock[i]);
					}
					for(size_type i = _StockSize; i < dis + 1; i++){
						if (i < dis)
							_Alloc.construct(&tmp[i], value_type());
						else
							_Alloc.construct(&tmp[i], val);
					}
				}
				for(size_type i = 0; i < _StockSize; i--){
					_Alloc.destroy(&_Stock[i]);
				}
				_Alloc.deallocate(_Stock, _StockCap - add);
				if (dis > _StockSize)
					_StockSize = dis + 1;
				else
					_StockSize++;
				_Stock = tmp;
				return (&_Stock[dis]);
			}
			void        insert(iterator pos, size_type n, const value_type &val){
				size_type dist = pos - begin();
				size_type diste = dist + n;
				size_type add = n;
				if (diste > _StockCap)
					add = diste - _StockCap;
				_StockCap += add;
				pointer tmp = _Alloc.allocate(_StockCap);
				if (dist < _StockSize){
					size_type i = 0, j = 0;
					while (i < _StockSize + n){
						if (i != dist)
							_Alloc.construct(&tmp[i++], _Stock[j++]);
						else{
							for(size_type k = 0; k < n; k++){
								_Alloc.construct(&tmp[i++], val);
							}
						}
					}
				}
				else{
					size_type i = 0;
					for (; i < _StockSize; i++){
						_Alloc.construct(&tmp[i], _Stock[i]);
					}
					size_type j = _StockSize, k = dist;
					while (j < dist)
						_Alloc.construct(&tmp[j++], value_type());
					while (k < diste)
						_Alloc.construct(&tmp[k++], val);
				}
				for(size_type i = 0; i < _StockSize; i--){
					_Alloc.destroy(&_Stock[i]);
				}
				_Alloc.deallocate(_Stock, _StockCap - add);
				if (dist > _StockSize)
					_StockSize = diste;
				else
					_StockSize += n;
				_Stock = tmp;
			}

			template<class InputIterator>
			void        insert(iterator pos, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, void**>::type = 0){
				size_type n = last - first;
				size_type dist = pos - begin();
				size_type diste = dist + n;
				size_type add = n;
				if (diste > _StockCap)
					add = diste - _StockCap;
				_StockCap += add;
				pointer tmp = _Alloc.allocate(_StockCap);
				if (dist < _StockSize){
					size_type i = 0, j = 0;
					while (i < _StockSize + n){
						if (i != dist)
							_Alloc.construct(&tmp[i++], _Stock[j++]);
						else{
							for(; first < last; first++){
								_Alloc.construct(&tmp[i++], *first);
							}
						}
					}
				}
				else{
					size_type i = 0;
					for (; i < _StockSize; i++){
						_Alloc.construct(&tmp[i], _Stock[i]);
					}
					size_type j = _StockSize, k = dist;
					while (j < dist)
						_Alloc.construct(&tmp[j++], value_type());
					while (k < diste)
						_Alloc.construct(&tmp[k++], *first++);
				}
				for(size_type i = 0; i < _StockSize; i--){
					_Alloc.destroy(&_Stock[i]);
				}
				_Alloc.deallocate(_Stock, _StockCap - add);
				if (dist > _StockSize)
					_StockSize = diste;
				else
					_StockSize += n;
				_Stock = tmp;
			}

			iterator    erase(iterator pos){
				pointer tmp = _Alloc.allocate(_StockCap);
				size_type dist = pos - begin();
				size_type i = 0, j = 0;
				while (_Stock[i]){
					if (i != dist)
						_Alloc.construct(&tmp[j++], _Stock[i]);
					i++;
				}
				for(size_type i = 0; i < _StockSize; i--){
					_Alloc.destroy(&_Stock[i]);
				}
				_Alloc.deallocate(_Stock, _StockCap);
				_Stock = tmp;
				_StockSize--;
				return (&_Stock[dist]);
			}
			iterator    erase(iterator first, iterator last){
				pointer tmp = _Alloc.allocate(_StockCap);
				size_type dist = first - begin(), n = last - first;
				size_type i = 0, j = 0;
				while (_Stock[i]){
					if (i == dist)
						while (n){
							i++;
							n--;
						}
					else
						_Alloc.construct(&tmp[j++], _Stock[i++]);
				}
				for(size_type i = 0; i < _StockSize; i--){
					_Alloc.destroy(&_Stock[i]);
				}
				_Alloc.deallocate(_Stock, _StockCap);
				_Stock = tmp;
				_StockSize -= last - first;
				return (&_Stock[dist + (last - first)]);
			}

			void        swap(vector &x){
				ft::swap(_Stock, x._Stock);
				ft::swap(_StockSize, x._StockSize);
				ft::swap(_StockCap, x._StockCap);
			}

			void        clear(){
				for(size_type i = 0; i < _StockSize; i--){
					_Alloc.destroy(&_Stock[i]);
				}
				_StockSize = 0;
			}

			allocator_type get_allocator() const { return (_Alloc); };

		private:

			pointer _Stock;
			size_type _StockCap;
			size_type _StockSize;
			allocator_type _Alloc;
	};

	template <class T, class  Alloc>
	bool operator==(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
		if (lhs.size() != rhs.size())
			return (false);
		for (size_t i = 0; i < lhs.size(); i++){
			if (lhs[i] != rhs[i])
				return (false);
		}
		return (true);
	}
	template <class T, class  Alloc>
	bool operator<(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }
	template <class T, class  Alloc>
	bool operator!=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) { return !(lhs == rhs); }
	template <class T, class  Alloc>
	bool operator<=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) { return !(rhs < lhs); }
	template <class T, class  Alloc>
	bool operator>(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) { return (rhs < lhs); }
	template <class T, class  Alloc>
	bool operator>=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) { return !(lhs < rhs); }

	template <class T, class Alloc>
	void swap(ft::vector<T, Alloc> &x, ft::vector<T, Alloc> &y){
		x.swap(y);
	}

}



#endif