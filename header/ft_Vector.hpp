#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

# include <iostream>
# include <memory>
# include "ft_RandAccessIter.hpp"
# include "ft_RevIter.hpp"
# include "ft_Utility.hpp"
# include "ft_Integral.hpp"

namespace ft {
	template<class T, class Alloc = std::allocator<T> >
	class vector {
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

			explicit vector(const allocator_type& alloc = allocator_type()) : _Stock(NULL), _StockCap(0), _StockSize(0), _Alloc(alloc) {}

			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) :
				_Stock(NULL), _StockCap(n), _StockSize(n), _Alloc(alloc) {
				if (n)
					_Stock = _Alloc.allocate(n);
				for (size_type i = 0; i < _StockSize; i++)
					_Alloc.construct(&_Stock[i], val);
			}

			template<class InputIterator>
			vector(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last, const allocator_type& alloc = allocator_type()) :
				_Stock(NULL), _StockCap(last - first), _StockSize(0), _Alloc(alloc) {
				if (_StockCap)
					_Stock = _Alloc.allocate(_StockCap);
				for (; first < last; first++)
					_Alloc.construct(&_Stock[_StockSize++], *first);
			}

			vector(const vector& x) : _Stock(NULL), _StockCap(x._StockCap), _StockSize(x._StockSize), _Alloc(x._Alloc) {
				_Stock = _Alloc.allocate(_StockCap);
				for(size_type i = 0; i < _StockSize; i++)
					_Alloc.construct(&_Stock[i], x[i]);
			}

			~vector() {
				for(size_type i = 0; i < _StockSize; i++)
					_Alloc.destroy(&_Stock[i]);
				_Alloc.deallocate(_Stock, _StockCap);
			}

			vector &operator=(const vector& x) {
				if (this != &x)
				{
					for(size_type i = 0; i < _StockSize; i++)
						_Alloc.destroy(&_Stock[i]);
					if (_StockSize < x._StockSize)
					{
						reserve(x._StockSize);
						resize(x._StockSize);
					}
					_StockSize = x.size();
					for (size_type i = 0; i < _StockSize; i++)
						_Alloc.construct(&_Stock[i], x._Stock[i]);
				}
				return (*this);
			}

			iterator				begin() { return (iterator(_Stock)); }
			const_iterator			begin () const { return (const_iterator(_Stock)); }
			iterator				end() { return (iterator(_Stock + _StockSize)); }
			const_iterator			end() const { return (const_iterator(_Stock + _StockSize)); }
			reverse_iterator		rbegin() { return (reverse_iterator(end())); }
			const_reverse_iterator	rbegin() const { return (const_reverse_iterator(end())); }
			reverse_iterator		rend() { return (reverse_iterator(begin())); }
			const_reverse_iterator	rend() const { return (const_reverse_iterator(begin())); }

			size_type   size() const { return _StockSize; }
			size_type   max_size() const { return _Alloc.max_size(); }
			size_type   capacity() const { return _StockCap; }
			bool        empty() const { if (_StockSize) return false; return true; }

			void        resize(size_type n, value_type val = value_type()) {
				if (n > _StockCap)
				{
					if (n < _StockCap * 2)
						reserve(_StockCap * 2);
					else
						reserve(n);
				}
				for(size_type i = _StockSize; i < n; i++)
					_Alloc.construct(&_Stock[i], val);
				for(size_type i = n; i < _StockSize; i++)
					_Alloc.destroy(&_Stock[i]);
				_StockSize = n;
			}

			void        reserve(size_type n) {
				if (n > _StockCap)
				{
					pointer tmp = _Alloc.allocate(n);
					for (size_type i = 0; i < _StockSize; i++)
					{
						_Alloc.construct(&tmp[i], _Stock[i]);
						_Alloc.destroy(&_Stock[i]);
					}
					_Alloc.deallocate(_Stock, _StockCap);
					_Stock = tmp;
					_StockCap = n;
				}
			}

			reference		operator[](size_type n) { return (reference(_Stock[n])); }
			const_reference	operator[](size_type n) const { return (const_reference(_Stock[n])); }

			reference		at(size_type n) {
				if (n >= _StockSize)
					throw std::out_of_range("out of range");
				return (reference(_Stock[n]));
			}

			const_reference	at(size_type n) const {
				if (n >= _StockSize)
					throw std::out_of_range("out of range");
				return (const_reference(_Stock[n]));
			}

			reference		front() { return (reference(*_Stock)); }
			const_reference	front()	const { return (const_reference(*_Stock)); }
			reference		back() { return (reference(_Stock[_StockSize - 1])); }
			const_reference	back() const { return (const_reference(_Stock[_StockSize - 1])); }

			template<class InputIterator>
			void	assign(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last) {
				size_type n = last - first;
				reserve(n);
				for(size_type i = 0; i < _StockSize; i++)
					_Alloc.destroy(&_Stock[i]);
				resize(n);
				n = 0;
				for (InputIterator it = first; it != last; it++)
					_Alloc.construct(&_Stock[n++], *it);
			}

			void	assign(size_type n, const value_type& val) {
				reserve(n);
				for(size_type i = 0; i < _StockSize; i++)
					_Alloc.destroy(&_Stock[i]);
				resize(n);
				for (size_type i = 0; i < n; i++)
					_Alloc.construct(&_Stock[i++], val);
			}

			void	push_back(const value_type& val) {
				if (!_StockCap)
					this->reserve(1);
				else if (_StockSize == _StockCap)
					this->reserve(_StockCap * 2);
				_Alloc.construct(&_Stock[_StockSize++], val);
			}

			void	pop_back() { if (_StockSize) _Alloc.destroy(&_Stock[--_StockSize]); }

			iterator    insert(iterator position, const value_type& val) {
				difference_type pos = position.base() - _Stock;
				insert(position, 1, val);
				return (iterator(begin() + pos));
			}

			void		insert(iterator position, size_type n, const value_type& val) {
				size_type b = position - begin();
				size_type e = end() - position;
				if (_StockSize + n > _StockCap)
				{
					if (_StockSize + n < _StockCap * 2)
						reserve(_StockCap * 2);
					else
						reserve(_StockSize + n);
				}
				_StockSize += n;
				for(size_type i = 0; i < e; i++)
				{
					_Alloc.construct(&_Stock[_StockSize - i - 1], _Stock[_StockSize - n - i - 1]);
					_Alloc.destroy(&_Stock[_StockSize - n - i - 1]);
				}
				for(size_type i = 0; i < n; i++)
					_Alloc.construct(&_Stock[b + i], val);
			}

			template<class InputIterator>
			void        insert(iterator position, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last) {
				size_type n = last - first;
				size_type b = position - begin();
				size_type e = end() - position;
				if (_StockSize + n > _StockCap) {
					if (_StockSize + n < _StockCap * 2)
						reserve(_StockCap * 2);
					else
						reserve(_StockSize + n);
				}
				_StockSize += n;
				for(size_type i = 0; i < e; i++) {
					_Alloc.construct(&_Stock[_StockSize - i - 1], _Stock[_StockSize - n - i - 1]);
					_Alloc.destroy(&_Stock[_StockSize - n - i - 1]);
				}
				for(size_type i = 0; i < n; i++)
					_Alloc.construct(&_Stock[b + i], *first++);
			}

			iterator    erase(iterator position) { return (erase(position, position + 1)); }

			iterator    erase(iterator first, iterator last) {
				if (first == this->end() || first == last)
					return (first);
				size_type b = first - begin();
				size_type e = end() - last;
				size_type diff = last - first;
				for(size_type i = 0; i < e; i++) {
					_Alloc.destroy(&_Stock[b + i]);
					_Alloc.construct(&_Stock[b + i], _Stock[b + i + diff]);
				}
				for(size_type i = e; i < diff; i++)
					_Alloc.destroy(&_Stock[b + i]);
				_StockSize -= diff;
				return (first);
			}

			void        swap(vector& x) {
				if (*this == x)
					return ;
				ft::swap(_Stock, x._Stock);
				ft::swap(_StockSize, x._StockSize);
				ft::swap(_StockCap, x._StockCap);
				ft::swap(_Alloc, x._Alloc);
			}

			void        clear() {
				while (--_StockSize > 0)
					_Alloc.destroy(&_Stock[_StockSize]);
				_Alloc.destroy(&_Stock[_StockSize]);
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
		for (size_t i = 0; i < lhs.size(); i++)
			if (lhs[i] != rhs[i])
				return (false);
		return (true);
	}
	template <class T, class  Alloc>
	bool operator!=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) { return !(lhs == rhs); }
	template <class T, class  Alloc>
	bool operator<(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }
	template <class T, class  Alloc>
	bool operator<=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) { return !(rhs < lhs); }
	template <class T, class  Alloc>
	bool operator>(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) { return (rhs < lhs); }
	template <class T, class  Alloc>
	bool operator>=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) { return !(lhs < rhs); }

	template <class T, class Alloc>
	void swap(ft::vector<T, Alloc> &x, ft::vector<T, Alloc> &y) { x.swap(y); }
}

#endif