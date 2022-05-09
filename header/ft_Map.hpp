#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include <memory>
#include "ft_Pair.hpp"
#include "ft_Utility.hpp"
#include "ft_MapIter.hpp"
#include "ft_RevIter.hpp"
#include "ft_TreeStruct.hpp"
#include "ft_Map2.hpp"

namespace ft
{
	template <  class Key, class T, class Compare = ft::less<Key>,
				class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
			typedef Key														key_type;
			typedef T														mapped_type;
			typedef ft::pair<const key_type, mapped_type>					value_type;
			typedef Compare													key_compare;
			typedef Alloc													allocator_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef typename ft::SubMap<value_type, key_compare>::iterator 			iterator;
			typedef typename ft::SubMap<value_type, key_compare>::const_iterator	const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
			typedef ptrdiff_t												difference_type;
			typedef size_t													size_type;

		class value_compare : public ft::binary_function<value_type, value_type, bool>
		{
			friend class map;
			protected:
				Compare comp;
				value_compare(Compare c) : comp(c) {}
			public:
				typedef bool result_type;
				typedef value_type first_argument_type;
				typedef value_type second_argument_type;
				bool operator() (const value_type &x, const value_type &y) const { return comp(x.first, y.first); }
		};

					explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) :
						_Stock(comp), _Alloc(alloc), _Comp(comp) {}

					template<class InputIterator>
					map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type(),
					    typename ft::enable_if<!ft::is_integral<InputIterator>::value, void**>::type = 0) :
						_Stock(comp), _Alloc(alloc), _Comp(comp) {
						_Stock.insert(first, last);
					}

					map(const map &x) : _Stock(x._Stock), _Alloc(x._Alloc), _Comp(x._Comp){}
					~map(){}

					iterator                begin() { return (_Stock.begin()); }
					const_iterator          begin() const { return (_Stock.begin()); }
					iterator                end() { return (_Stock.end()); }
					const_iterator          end() const { return (_Stock.end()); }
					reverse_iterator        rbegin() { return (_Stock.rbegin()); }
					const_reverse_iterator  rbegin() const { return (_Stock.rbegin()); }
					reverse_iterator        rend() { return (_Stock.rend()); }
					const_reverse_iterator  rend() const { return (_Stock.rend()); }


					bool            empty() const { return size() == 0; }
					size_type       size() const { return (_Stock.size()); }
					size_type       max_size() const { return (_Stock.max_size()); }
					allocator_type  get_allocator() const { return _Alloc; }

					map             &operator=(const map &x){
							_Alloc = x._Alloc;
							clear();
							_Stock.insert(x.begin(), x.end());
							return (*this);
					}

					mapped_type     &operator[](const key_type &k){
						iterator it = _Stock.find(k);
						if (it == end())
							it = insert(ft::make_pair(k, mapped_type())).first;
						return (it->second);
					}


					iterator        find(const key_type &k) {
						return (iterator(_Stock.find(k)));
					}
					const_iterator  find(const key_type &k) const {
						return (const_iterator(_Stock.find(k)));
					}
					size_type       count(const key_type &k) const {
						const_iterator check = find(k);
						if (check != end())
							return 1;
						return 0;
					}

					iterator        lower_bound(const key_type &k) {
						iterator it = begin();
						iterator ite = end();
						while (it != ite){
							if (!_Comp(it->Stock.first, k))
								break;
							it++;
						}
						return (it);
					}
					const_iterator  lower_bound(const key_type &k) const {
						iterator it = begin();
						iterator ite = end();
						while (it != ite) {
							if (!_Comp(it->Stock.first, k))
								break;
							it++;
						}
						return (it);
					}
					iterator        upper_bound(const key_type &k) {
						iterator it = begin();
						iterator ite = end();
						while (it != ite) {
							if (!_Comp(it->Stock.first, k))
								break;
							it++;
						}
						if (it != ite)
							it++;
						return (it);
					}
					const_iterator  upper_bound(const key_type &k) const {
						iterator it = begin();
						iterator ite = end();
						while (it != ite) {
							if (!_Comp(it->Stock.first, k))
								break;
							it++;
						}
						if (it != ite)
							it++;
						return (it);
					}

					ft::pair<const_iterator, const_iterator>    equal_range(const key_type &k) const {
						return (ft::make_pair(lower_bound(k), upper_bound(k)));
					}
					ft::pair<iterator, iterator>                equal_range(const key_type &k) {
						return (ft::make_pair(lower_bound(k), upper_bound(k)));
					}

					key_compare     key_comp() const { return (_Comp); }
					value_compare   value_comp() const { return (_Comp); }

					ft::pair<iterator, bool> insert(const value_type &val){
						return (_Stock.insert(val));
					}
					iterator                 insert(iterator position, const value_type &val){
						(void)position;
						return (_Stock.insert(val).first);
					}

					template<class InputIterator>
					void    insert(InputIterator first, InputIterator last,
								typename ft::enable_if<!ft::is_integral<InputIterator>::value, void**>::type = 0){
						for(; first != last; first++){
							insert(*first);
						}
					}

					void swap(map &x){
						_Stock.swap(x._Stock);
						ft::swap(_Comp, x._Comp);
						ft::swap(_Alloc, x._Alloc);
					}

					void clear() {
						_Stock.clear();
					}

					void erase(iterator position){
						_Stock.erase(position);
					}

					size_type erase(const key_type &k){
						return (_Stock.erase(k));
					}

					void erase(iterator first, iterator last){
						_Stock.erase(first, last);
					}

				private:
					ft::SubMap<value_type, key_compare> _Stock;
					allocator_type                      _Alloc;
					key_compare                         _Comp;


	};
}

#endif