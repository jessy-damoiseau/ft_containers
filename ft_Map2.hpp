#ifndef FT_MAP2_HPP
#define FT_MAP2_HPP

#include "ft_TreeStruct.hpp"
#include "ft_MapIter.hpp"
#include "ft_Utility.hpp"
#include "ft_Integral.hpp"
#include "ft_Pair.hpp"
#include "ft_RevIter.hpp"
#include <memory>

namespace ft {

	template<class T, class Compare = std::less<typename T::first_type>, class Allocator = std::allocator<T> >
	class SubMap {
		public:
			typedef T                                       value_type;
			typedef Compare                                 key_compare;
			typedef typename T::first_type                  key_type;
			typedef typename T::second_type                 mapped_type;
			typedef ft::tree_struct<value_type>             tree;
			typedef tree*                                   tree_pointer;
			typedef tree&                                   tree_reference;
			typedef typename std::allocator<tree>           tree_alloc;
			typedef typename Allocator::reference           reference;
			typedef typename Allocator::const_reference     const_reference;
			typedef typename Allocator::pointer             pointer;
			typedef typename Allocator::const_pointer       const_pointer;
			typedef ft::map_iterator<tree>            iterator;
			typedef ft::map_const_iterator<tree>      const_iterator;
			typedef ft::reverse_iterator<iterator>          reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;
			typedef std::size_t                             size_type;
			typedef ptrdiff_t                               difference_type;

			SubMap(const key_compare &compare = key_compare()){ _Stock = 0; _Comp = compare; _Size = 0; }
			SubMap(const SubMap &inst) : _Stock(0), _Size(inst._Size), _Comp(inst._Comp){ insert(inst.begin(), inst.end()); }
			virtual ~SubMap() { clear(); }

			SubMap  &operator=(const SubMap &inst) { _Stock = inst._Stock; _Size = inst._Size; _Comp = inst._Comp; _Alloc = inst._Alloc; return (*this); }

			size_type       size() const { return _Size; }
			size_type       max_size() const { return _Alloc.max_size(); }

			void            clear() {
				destroy_branch(_Stock);
				_Size = 0;
			}

			void            erase(iterator position) {
				if (position == end() || !_Size )
					return ;
				tree_pointer del = searchFind(position->first);
				if (del) {
					if (del && del->left && del->right)
					{
						tree_pointer tmp = FullLeft(del->right);
						del->Stock = tmp->Stock;
						if (tmp->right)
						{
							tmp->right->prev = del;
							del->right = tmp->right;
						}
						else if (tmp->left)
						{
							tmp->left->prev = del;
							del->left = tmp->left;
						}
						if (!tmp->right && !tmp->left)
						{
							if (tmp->prev->right == tmp)
								tmp->prev->right = NULL;
							else if (tmp->prev->left == tmp)
								tmp->prev->left = NULL;
						}
						_Alloc.destroy(tmp);
						_Alloc.deallocate(tmp, 1);
						_Size--;
					}
					else
					{
						tree_pointer tmp = (del->left != NULL) ? del->left : del->right;
						if (tmp)
						{
							tmp->prev = del->prev;
							if (!tmp->prev)
							{
								_Alloc.destroy(del);
								_Alloc.deallocate(del, 1);
								del = tmp;
								_Stock = tmp;
								_Size--;
								return ;
							}
						}
						else if (del->prev)
						{
							if (del->prev->right == del)
								del->prev->right = NULL;
							if (del->prev->left == del)
								del->prev->left = NULL;
						}
						if (del->left)
						{
							if (del->prev->left == del)
								del->prev->left = tmp;
							else
								del->prev->right = tmp;
						}
						else if (del->right)
						{
							if (del->prev->right == del)
								del->prev->right = tmp;
							else
								del->prev->left = tmp;
						}
						if (del == _Stock && !del->right && !del->left)
						{
							_Alloc.destroy(del);
							_Alloc.deallocate(del, 1);
							del = _Stock = NULL;
							_Size--;
							return ;
						}
						_Alloc.destroy(del);
						_Alloc.deallocate(del, 1);
						del = NULL;
						_Size--;
					}
				}
			}
			size_type       erase(const key_type &k){
				iterator it = find(k);
				if (it != end()){
					erase(it);
					return (1);
				}
				return (0);
			}
			void            erase(iterator first, iterator last){
				for(; first != last;) {
					iterator tmp = first;
					first++;
					erase(tmp);
				}
			}

			iterator        find(const key_type &k) {
				return (searchFind(k));
			}
			const_iterator  find(const key_type &k) const {
				return (searchFind(k));
			}

			template<class InputIterator>
			void                        insert(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, void**>::type = 0){
				for(; first != last; first++){
					func_insert(_Stock, *first);
				}
			}
			ft::pair<iterator, bool>    insert(const value_type &val){
				return (func_insert(_Stock, val));
			}
			iterator                    insert(iterator position, const value_type &val){
				(void)position;
				return (func_insert(_Stock, val).first);
			}


			void                    swap(SubMap &x){
				ft::swap(_Stock, x._Stock);
				ft::swap(_Size, x._Size);
			}

			iterator                begin() { return ( iterator(FullLeft(_Stock))); }
			const_iterator          begin() const { return ( const_iterator(FullLeft(_Stock))); }
			iterator                end() { return ( iterator(0, FullRight(_Stock))); }
			const_iterator          end() const { return ( const_iterator(0, FullRight(_Stock))); }
			reverse_iterator        rbegin() { return (reverse_iterator(end())); }
			const_reverse_iterator  rbegin() const { return (const_reverse_iterator(end())); }
			reverse_iterator        rend() { return (reverse_iterator(begin())); }
			const_reverse_iterator  rend() const { return (const_reverse_iterator(begin())); }

		private:
			tree_pointer    _Stock;
			size_type       _Size;
			tree_alloc      _Alloc;
			key_compare     _Comp;

			void leftRotate(tree_pointer x) {
				tree_pointer y = x->right;
				x->right = y->left;
				if (y->left != 0)
					y->left->prev = x;
				y->prev = x->prev;
				if (x->prev == 0)
					this->_Stock = y;
				else if (x == x->prev->left)
					x->prev->left = y;
				else 
					x->prev->right = y;
				y->left = x;
				x->prev = y;
				x->bf = x->bf - 1 - ft::max(0, y->bf);
				y->bf = y->bf - 1 + ft::min(0, x->bf);
			}
			void rightRotate(tree_pointer x) {
				tree_pointer y = x->left;
				x->left = y->right;
				if (y->right != 0) 
					y->right->prev = x;
				y->prev = x->prev;
				if (x->prev == 0)
					this->_Stock = y;
				else if (x == x->prev->right)
					x->prev->right = y;
				else
					x->prev->left = y;
				y->right = x;
				x->prev = y;
				x->bf = x->bf + 1 - ft::min(0, y->bf);
				y->bf = y->bf + 1 + ft::max(0, x->bf);
			}
			void rebalance(tree_pointer node) {
				if (node->bf > 0) {
					if (node->right->bf < 0) {
						rightRotate(node->right);
						leftRotate(node);
					} else
						leftRotate(node);
				} else if (node->bf < 0) {
					if (node->left->bf > 0) {
						leftRotate(node->left);
						rightRotate(node);
					} else
						rightRotate(node);
				}
			}
			void updateBalance(tree_pointer node) {
				if (node->bf < -1 || node->bf > 1) {
					rebalance(node);
					return;
				}
				if (node->prev != 0) {
					if (node == node->prev->left)
						node->prev->bf -= 1;
					if (node == node->prev->right)
						node->prev->bf += 1;
					if (node->prev->bf != 0)
						updateBalance(node->prev);
				}
			}


		protected:
			void                        destroy_branch(tree_pointer &supp){
				if (supp){
					destroy_branch(supp->left);
					destroy_branch(supp->right);
					_Alloc.destroy(supp);
					_Alloc.deallocate(supp, 1);
					supp = 0;
				}
			}

			ft::pair<iterator, bool>    func_insert(tree_pointer stock, const value_type &value) {
				if (!_Stock){
					_Stock = _Alloc.allocate(1);
					_Alloc.construct(_Stock, tree(value));
					_Stock->bf = 0;
					_Size++;
					return (ft::make_pair(iterator(_Stock), true));
				}
				tree_pointer tmp = stock;
				tree_pointer tmpPrev = 0;
				while (tmp){
					tmpPrev = tmp;
					if (_Comp(value.first, tmp->Stock.first))
						tmp = tmp->left;
					else if (_Comp(tmp->Stock.first, value.first))
						tmp = tmp->right;
					else
						return ( ft::pair<iterator, bool>(iterator(tmp), false));
				}
				tmp = _Alloc.allocate(1);
				_Alloc.construct(tmp, tree(value));
				tmp->bf = 0;
				_Size++;
				if (_Comp(value.first, tmpPrev->Stock.first))
					tmpPrev->left = tmp;
				else
					tmpPrev->right = tmp;
				tmp->prev = tmpPrev;
				//updateBalance(tmp);
				return ( ft::pair<iterator, bool>(iterator(tmp), true));
			}
			tree_pointer                FullLeft(tree_pointer x) const{
				tree_pointer ret = x;
				if (ret){
					while (ret->left)
						ret = ret->left;
				}
				return ret;
			}
			tree_pointer                FullRight(tree_pointer x) const{
				tree_pointer ret = x;
				if (ret){
					while (ret->right)
						ret = ret->right;
				}
				return ret;
			}

			tree_pointer       			searchFind(const key_type &k) const {
				tree_pointer tmp = _Stock;
				while (tmp){
					if (tmp->Stock.first == k)
						return (tmp);
					else if (k < tmp->Stock.first)
						tmp = tmp->left;
					else
						tmp = tmp->right;
				}
				return (0);
			}
	};
}

#endif