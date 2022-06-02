#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include "ft_Pair.hpp"
#include "ft_Utility.hpp"
#include "ft_RevIter.hpp"
#include "BST_AVL.hpp"

namespace ft {
	template <  class Key, class T, class Compare = ft::less<Key>, 
				class Alloc = std::allocator<ft::pair<const Key, T > > >
	class map {
		public:
			typedef Key																key_type;
			typedef T																mapped_type;
			typedef ft::pair<key_type, mapped_type>									value_type;
			typedef Compare															key_compare;
			typedef Alloc															allocator_type;
			typedef typename allocator_type::reference								reference;
			typedef typename allocator_type::const_reference						const_reference;
			typedef typename allocator_type::pointer								pointer;
			typedef typename allocator_type::const_pointer							cons_pointer;
			typedef typename ft::BST_AVL<value_type, key_compare>::iterator			iterator;
			typedef typename ft::BST_AVL<value_type, key_compare>::const_iterator	const_iterator;
			typedef ft::reverse_iterator<iterator>									reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>							const_reverse_iterator;
			typedef ptrdiff_t														difference_type;
			typedef std::size_t														size_type;
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
					_Bst(comp), _Alloc(alloc), _Comp(comp) {}
			template<class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, void**>::type = 0) :
					_Bst(comp), _Alloc(alloc), _Comp(comp) {
				insert(first, last);
			}
			map(const map &x) {
				_Alloc = x.get_allocator();
				insert(x.begin(), x.end());
			}
			~map() {}

			iterator                begin() { return (_Bst.begin()); }
			const_iterator          begin() const { return (_Bst.begin()); }
			iterator                end() { return (_Bst.end()); }
			const_iterator          end() const { return (_Bst.end()); }
			reverse_iterator        rbegin() { return (_Bst.rbegin()); }
			const_reverse_iterator  rbegin() const { return (_Bst.rbegin()); }
			reverse_iterator        rend() { return (_Bst.rend()); }
			const_reverse_iterator  rend() const { return (_Bst.rend()); }

			bool            empty() const { return size() == 0; }
			size_type       size() const { return (_Bst.size()); }
			size_type       max_size() const { return (_Bst.max_size()); }
			allocator_type  get_allocator() const { return _Alloc; }

			map				&operator=(const map &inst) {
				_Alloc = inst._Alloc;
				_Bst = inst._Bst;
				return (*this);
			}
			mapped_type		&operator[](const key_type &key) {
				iterator it = _Bst.nodeSearch(key);
				if (it == end()) {
                    it = insert(ft::make_pair(key, mapped_type())).first;
                }
				return (it->second);
			}

			iterator        find(const key_type &k) { return (iterator(_Bst.nodeSearch(k))); }
			const_iterator  find(const key_type &k) const { return (const_iterator(_Bst.nodeSearch(k))); }
			size_type		count(const key_type &k) const {
				const_iterator check = find(k);
				if (check != end())
					return 1;
				return 0;
			}

			iterator		lower_bound(const key_type &k) {
				iterator it = begin();
				iterator ite = end();
				while (it != ite){
					if (!_Comp(it->first, k))
						break;
					it++;
				}
				return (it);
			}
			const_iterator	lower_bound(const key_type &k) const {
				const_iterator it = begin();
				const_iterator ite = end();
				while (it != ite) {
					if (!_Comp(it->first, k))
						break;
					it++;
				}
				return (it);
			}
			iterator		upper_bound(const key_type &k) {
				iterator it = begin();
				iterator ite = end();
				while (it != ite) {
					if (_Comp(k, it->first))
						break;
					it++;
				}
				return (it);
			}
			const_iterator	upper_bound(const key_type &k) const {
				const_iterator it = begin();
				const_iterator ite = end();
				while (it != ite) {
					if (_Comp(k, it->first))
						break;
					it++;
				}
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

			template<class InputIterator>
			void	insert(InputIterator first, InputIterator last,
						   typename ft::enable_if<!ft::is_integral<InputIterator>::value, void**>::type = 0) {
                for(; first != last; first++)
					insert(*first);
			}

			ft::pair<iterator, bool>	insert(const value_type &val) {
                return (_Bst.insert(val));
            }
			iterator					insert(iterator position, const value_type &val) {
				(void)position;
				return (_Bst.insert(val).first);
			}

			void		erase(iterator position) {
				erase(position->first);
			}
			size_type 	erase(const key_type &k) {
				iterator it = find(k);
				if (it == end())
					return (0);
				_Bst.erase(it);
				return (1);
			}
			void		erase(iterator first, iterator last) {
				for(; first != last;) {
					iterator tmp = first;
					first++;
					erase(tmp);
				}
			}

			void	swap(map &x) {
				_Bst.swap(x._Bst);
				ft::swap(_Alloc, x._Alloc);
				ft::swap(_Comp, x._Comp);
			}
			void	clear() {
				_Bst.clear();
			}

		private:
			BST_AVL<value_type, key_compare>	_Bst;
			allocator_type						_Alloc;
			key_compare 						_Comp;
	};
	template <typename Key, typename T, typename Compare, typename Allocator>
	bool operator==(const map<Key, T, Compare, Allocator> &lhs, const map<Key, T, Compare, Allocator> &rhs) {
		typename ft::map<Key, T, Compare, Allocator>::const_iterator	it = lhs.begin();
		typename ft::map<Key, T, Compare, Allocator>::const_iterator	ite = lhs.end();
		typename ft::map<Key, T, Compare, Allocator>::const_iterator	it2 = rhs.begin();

		while (it != ite && it2 != rhs.end())
		{
			if (it->first != it2->first || it->second != it2->second)
				return (false);
			it++;
			it2++;
		}
		return (it == ite && it2 == rhs.end());
	}
	template <typename Key, typename T, typename Compare, typename Allocator>
	bool operator!=(const map<Key, T, Compare, Allocator> &lhs, const map<Key, T, Compare, Allocator> &rhs) { return (!(lhs == rhs)); }
	template <typename Key, typename T, typename Compare, typename Allocator>
	bool operator<(const map<Key, T, Compare, Allocator> &lhs, const map<Key, T, Compare, Allocator> &rhs) { return ( ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) ); }
	template <typename Key, typename T, typename Compare, typename Allocator>
	bool operator>(const map<Key, T, Compare, Allocator> &lhs, const map<Key, T, Compare, Allocator> &rhs) { return (rhs < lhs); }
	template <typename Key, typename T, typename Compare, typename Allocator>
	bool operator<=(const map<Key, T, Compare, Allocator> &lhs, const map<Key, T, Compare, Allocator> &rhs) { return (!(rhs < lhs)); }
	template <typename Key, typename T, typename Compare, typename Allocator>
	bool operator>=(const map<Key, T, Compare, Allocator> &lhs, const map<Key, T, Compare, Allocator> &rhs) { return (!(lhs < rhs)); }
	template <typename Key, typename T, typename Compare, typename Allocator>
	void swap(map<Key, T, Compare, Allocator> &lhs, map<Key, T, Compare, Allocator> &rhs) { lhs.swap(rhs); }
}
#endif