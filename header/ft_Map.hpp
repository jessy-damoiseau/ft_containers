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
				class Alloc = std::allocator<ft::pair<const Key, T>> > class map{
				public:
					typedef Key                                                 key_type;
					typedef T                                                   mapped_type;
					typedef pair<const Key, T>                                  value_type;
					typedef Compare                                             key_compare;
					typedef Alloc                                               allocator_type;
					typedef allocator_type::reference                           reference;
					typedef allocator_type::const_reference                     const_reference;
					typedef allocator_type::pointer                             pointer;
					typedef allocator_type::const_pointer                       const_pointer;
					typedef ft::map_iterator<ft::tree_struct<value_type>>       iterator;
					typedef ft::map_iterator<const ft::tree_struct<value_type>> const_iterator;
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
						_Stock(0), _Size(0), _Cap(0), _Comp(comp), _Alloc(alloc) {}

					template<class InputIterator>
					map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type(),
					    typename ft::enable_if<!ft::is_integral<InputIterator>::value, void**>::type = nullptr)	:
						_Stock(0), _Size(0), _Cap(0), _Alloc(alloc), _Comp(comp) {

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
					reverse_iterator        rbegin() { return (reverse_iterator(this->end() + 1)); }
					const_reverse_iterator  rbegin() const { return (reverse_iterator(this->end() + 1)); }
					reverse_iterator        rend() { return (reverse_iterator(this->begin() - 1)); }
					const_reverse_iterator  rend() const { return (reverse_iterator(this->begin() - 1)); }


					bool            empty() const { return _Size == 0; }
					size_type       size() const { return _Size; }
					size_type       max_size() const { return _Alloc.max_size(); }
					allocator_type  get_allocator() const { return _Alloc; }


				private:
					ft::tree_struct<value_type> _Stock;
					size_type                   _Size;
					size_type                   _Cap;
					allocator_type              _Alloc;
					key_compare                 _Comp;



	};
}

#endif