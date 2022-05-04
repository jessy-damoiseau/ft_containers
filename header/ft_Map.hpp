#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include <memory>
#include "ft_Pair.hpp"
#include "ft_Utility.hpp"
#include "ft_MapIter.hpp"
#include "ft_RevIter.hpp"
#include "ft_TreeStruct.hpp"

namespace ft {
	template <  class Key, class T, class Compare = ft::less<Key>,
				class Alloc = std::allocator<ft::pair<const Key, T> > > class map{
				public:
					typedef Key                                                 key_type;
					typedef T                                                   mapped_type;
					typedef pair<const Key, T>                                  value_type;
					typedef Compare                                             key_compare;
					typedef Alloc                                               allocator_type;
					typedef typename allocator_type::reference                           reference;
					typedef typename allocator_type::const_reference                     const_reference;
					typedef typename allocator_type::pointer                             pointer;
					typedef typename allocator_type::const_pointer                       const_pointer;
					typedef ft::map_iterator<ft::tree_struct<value_type> >       iterator;
					typedef ft::map_const_iterator<ft::tree_struct<value_type> > const_iterator;
					typedef ft::reverse_iterator<iterator>                      reverse_iterator;
					typedef ft::reverse_iterator<const_iterator>                const_reverse_iterator;
					typedef ptrdiff_t                                           difference_type;
					typedef size_t                                              size_type;
					class value_compare : public ft::binary_function<value_type, value_type, bool> {
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
						_Stock(0), _Size(0), _Alloc(alloc), _Comp(comp) {}

					template<class InputIterator>
					map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type(),
					    typename ft::enable_if<!ft::is_integral<InputIterator>::value, void**>::type = 0)	:
						_Stock(0), _Size(0), _Alloc(alloc), _Comp(comp) {
						insert(first, last);
					}

					map(const map &x) { *this = x; }

					~map(){}

					iterator                begin() {
						ft::tree_struct<value_type> *tmp = _Stock;
						while (tmp->left)
							tmp = tmp->left;
						return tmp;
					}
					const_iterator          begin() const {
						ft::tree_struct<value_type> *tmp = _Stock;
						while (tmp->left)
							tmp = tmp->left;
						return tmp;
					}
					iterator                end() {
						ft::tree_struct<value_type> *tmp = _Stock;
						while (tmp->right)
							tmp = tmp->right;
						return tmp;
					}
					const_iterator          end() const {
						ft::tree_struct<value_type> *tmp = _Stock;
						while (tmp->right)
							tmp = tmp->right;
						return tmp;
					}
					reverse_iterator        rbegin() { return (reverse_iterator(end() + 1)); }
					const_reverse_iterator  rbegin() const { return (reverse_iterator(end() + 1)); }
					reverse_iterator        rend() { return (reverse_iterator(this->begin() - 1)); }
					const_reverse_iterator  rend() const { return (reverse_iterator(this->begin() - 1)); }


					bool            empty() const { return _Size == 0; }
					size_type       size() const { return _Size; }
					size_type       max_size() const { return _Alloc.max_size(); }
					allocator_type  get_allocator() const { return _Alloc; }

					map             &operator=(const map &x){
							_Alloc = x._Alloc;
							clear();
							insert(x.begin(), x.end());
							return (*this);
					}

					mapped_type     &operator[](const key_type &k){
						iterator it = find(k);
						if (it == end())
							it = insert(ft::make_pair(k, mapped_type())).first;
						return (it->Stock.second);
					}


					iterator        find(const key_type &k) {
						ft::tree_struct<value_type> *tmp = _Stock;
						while (tmp){
							if (tmp->Stock.first == k)
								return tmp;
							else if (k < tmp->Stock.first)
								tmp = tmp->left;
							else
								tmp = tmp->right;
						}
						return (0);
					}
					const_iterator  find(const key_type &k) const {
						ft::tree_struct<value_type> *tmp = _Stock;
						while (tmp){
							if (tmp->Stock.first == k)
								return tmp;
							else if (k < tmp->Stock.first)
								tmp = tmp->left;
							else
								tmp = tmp->right;
						}
						return (0);
					}
					size_type       count(const key_type &k) const {
						iterator check = this->find(k);
						if (check)
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
						return (func_insert(_Stock, val));
					}
					iterator                 insert(iterator position, const value_type &val){
						(void)position;
						return (func_insert(_Stock, val).first);
					}

					template<class InputIterator>
					void    insert(InputIterator first, InputIterator last,
								typename ft::enable_if<!ft::is_integral<InputIterator>::value, void**>::type = 0){
						for(; first != last; first++){
							func_insert(_Stock, *first);
						}
					}

					void swap(map &x){
						ft::swap(_Stock, x._Stock);
						ft::swap(_Comp, x._Comp);
						ft::swap(_Alloc, x._Alloc);
						ft::swap(_Size, x._Size);
					}

					void clear() {
						destroy_branch(_Stock);
						_Size = 0;
					}

					void erase(iterator position){
						if (position == end() || !_Size)
							return ;
						iterator itsupp = find(position->Stock.first);
						if (itsupp == 0)
							return ;
						typedef ft::tree_struct<value_type> tree;
						tree supp = itsupp->Stock;
						if (_Comp(supp.first, supp->prev->Stock.first))
							supp->prev->left = 0;
						else
							supp->prev->right = 0;
						supp->prev = 0;
						iterator itins = itsupp;
						while (itins->left)
							itins = itins->left;
						insert(itins, itsupp);
						itins = itsupp;
						while (itins->right)
							itins = itins->right;
						insert(itsupp->right, itins + 1);
						destroy_branch(itsupp->Stock);
						_Size--;
					}

					size_type erase(const key_type &k){
						iterator it = find(k);
						if (it){
							erase(it);
							return (1);
						}
						return (0);
					}

					void erase(iterator first, iterator last){
						for (; first != last; first++)
							erase(first);
					}

				private:
					ft::tree_struct<value_type> *_Stock;
					size_type                   _Size;
					allocator_type              _Alloc;
					key_compare                 _Comp;

					ft::pair<iterator, bool> func_insert(ft::tree_struct<value_type> *stock, const value_type &value) {
						typedef ft::tree_struct<value_type> tree;
						typedef std::allocator<tree> alloc_tree;
						alloc_tree tmp_alloc;
						if (!_Stock){
							_Stock = tmp_alloc.allocate(1);
							tmp_alloc.construct(_Stock, tree(value));
							_Size++;
							return (ft::pair<iterator, bool>(iterator(_Stock), true));
						}
						tree *tmp = stock;
						tree *tmpPrev = 0;
						while (tmp){
							tmpPrev = tmp;
							if (_Comp(value.first, tmp->Stock.first))
								tmp = tmp->left;
							else if (_Comp(tmp->Stock.first, value.first))
								tmp = tmp->right;
							else
								return ( ft::pair<iterator, bool>(iterator(tmp), false));
						}
						tmp = tmp_alloc.allocate(1);
						tmp_alloc.construct(tmp, tree(value));
						_Size++;
						if (_Comp(value.first, tmpPrev->Stock.first))
							tmpPrev->left = tmp;
						else
							tmpPrev->right = tmp;
						tmp->prev = tmpPrev;
						return ( ft::pair<iterator, bool>(iterator(tmp), true));
					}
					void destroy_branch(ft::tree_struct<value_type> *supp){
						if (supp){
							destroy_branch(supp->left);
							destroy_branch(supp->right);
							_Alloc.destroy(supp);
							_Alloc.deallocate(supp, 1);
							supp = 0;
						}
					}

	};
}

#endif