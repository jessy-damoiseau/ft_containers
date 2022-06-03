#ifndef BST_AVL_HPP
#define BST_AVL_HPP

#include <memory>
#include "ft_Utility.hpp"
#include "ft_RevIter.hpp"
#include "ft_Integral.hpp"
#include "mapIter.hpp"

namespace ft {
	template <class T>
	struct	node {
		typedef T value_type;
		T		data;
		node	*parent;
		node	*left;
		node	*right;
		int		bf;
		bool	last;

		node() : data(0), parent(0), left(0), right(0), bf(0), last(false) {}
		node(const T &x) : data(x), parent(0), left(0), right(0), bf(0), last(false) {}
		node(const node &x) : data(x.data), parent(x.parent), left(x.left), right(x.right), bf(x.bf), last(x.last) {}
		~node() {}

		node &operator=(const node &x) {
			data = x.data;
			parent = x.parent;
			left = x.left;
			right = x.right;
			bf = x.bf;
			last = x.last;
		}
	};

	template<class T, class Compare = ft::less<typename T::first_type>, class Alloc = std::allocator<T> >
	class BST_AVL{
		public:
			typedef T												value_type;
			typedef Compare											key_compare;
			typedef typename T::first_type							key_type;
			typedef typename T::second_type							mapped_type;
			typedef ft::node<value_type> 							node;
			typedef node*											nodePtr;
			typedef node&											nodeRef;
			typedef typename Alloc::template rebind<node>::other	node_alloc;
			typedef typename Alloc::reference						reference;
			typedef typename Alloc::const_reference					const_reference;
			typedef typename Alloc::pointer							pointer;
			typedef typename Alloc::const_pointer					const_pointer;
			typedef ft::map_iterator<node>							iterator;
			typedef ft::map_const_iterator<node>					const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> 			const_reverse_iterator;
			typedef std::size_t 									size_type;

			BST_AVL(const key_compare &comp = Compare()) : _Root(0), _Size(0), _Comp(comp) {
				nodePtr last = create();
				last->last = true;
				_Root = last;
			}
			BST_AVL(const BST_AVL &inst) : _Root(0), _Size(0), _Comp(inst._Comp) { insert(inst.begin(), inst.end()); }
			virtual ~BST_AVL() {
                clear();
                _Alloc.destroy(_Root);
                _Alloc.deallocate(_Root, 1);
                _Root = 0;
            }

			BST_AVL	&operator=(const BST_AVL &inst) {
					clear();
					_Comp = inst._Comp;
					_Size = 0;
                    insert(inst.begin(), inst.end());
				return (*this);
			}

			size_type size() const { return (_Size); }
			size_type max_size() const { return (_Alloc.max_size()); }

			void	clear() {
                nodePtr last = clear_lastNode();
				destroy(_Root);
                insert_lastNode(last);
				_Size = 0;
			}
			void	swap(BST_AVL &x) {
				ft::swap(_Root, x._Root);
				ft::swap(_Size, x._Size);
				ft::swap(_Comp, x._Comp);
				ft::swap(_Alloc, x._Alloc);
			}

			void						erase(iterator position){
                    deleteNode(position, position.base());
                    _Size--;
			}
			
			ft::pair<iterator, bool>    insert(const value_type &val){
				nodePtr last = clear_lastNode();
				ft::pair<iterator, bool> ret = insertNode(val);
				insert_lastNode(last);
				return (ret);
			}

            template<class InputIterator>
            void                        insert(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, void**>::type = 0){
                for(; first != last; first++){
                    insert(*first);
                }
            }

			nodePtr 				nodeSearch(const key_type &k) const {
				nodePtr ret = _Root;
				while (ret && !ret->last){
					if (ret->data.first == k) {
                        return (ret);
                    }
					else if (k < ret->data.first) {
                        ret = ret->left;
                    }
					else {
                        ret = ret->right;
                    }
				}
				return (end().base());
			}

			iterator				begin() { return (iterator(nodeLeft(_Root))); }
			const_iterator			begin() const { return (const_iterator(nodeLeft(_Root))); }
			iterator				end() { return (iterator(nodeRight(_Root))); }
			const_iterator			end() const { return (const_iterator(nodeRight(_Root))); }
			reverse_iterator 		rbegin() { return (reverse_iterator(end()--)); }
			const_reverse_iterator	rbegin() const { return (const_reverse_iterator(end()--)); }
			reverse_iterator		rend() { return (reverse_iterator(begin())); }
			const_reverse_iterator	rend() const { return (const_reverse_iterator(begin())); }

		private:
			nodePtr		_Root;
			size_type	_Size;
			key_compare	_Comp;
			node_alloc	_Alloc;

			nodePtr create(const value_type &value = value_type()){
				nodePtr New = _Alloc.allocate(1);
				_Alloc.construct(New, node(value));
				return New;
			}
			void	destroy(nodePtr &supp){
				if (supp){
					destroy(supp->left);
					destroy(supp->right);
					_Alloc.destroy(supp);
					_Alloc.deallocate(supp, 1);
				}
                supp = 0;
			}

			ft::pair<iterator, bool>	insertNode(const value_type &value) {
                nodePtr node = create(value);
                if (!_Root){
                    _Root = node;
                    _Size++;
                    return (ft::make_pair(iterator(_Root), true));
                }
                nodePtr tmp = _Root;
                nodePtr tmpPrev = 0;
                while (tmp){
                    tmpPrev = tmp;
                    if (_Comp(value.first, tmp->data.first))
                        tmp = tmp->left;
                    else if (_Comp(tmp->data.first, value.first))
                        tmp = tmp->right;
                    else {
                        _Alloc.destroy(node);
                        _Alloc.deallocate(node, 1);
                        return (ft::pair<iterator, bool>(iterator(tmp), false));
                    }
                }
                _Size++;
                if (_Comp(value.first, tmpPrev->data.first))
                    tmpPrev->left = node;
                else
                    tmpPrev->right = node;
                node->parent = tmpPrev;
                return ( ft::pair<iterator, bool>(iterator(node), true));
			}
			void						deleteNode(iterator position, nodePtr del) {
                if (position == end() || !_Size )
                    return ;
                if (!del->last) {
                    if (del && del->left && del->right)
                    {
                        nodePtr tmp = nodeLeft(del->right);
                        del->data = tmp->data;
                        if (tmp->right)
                        {
                            tmp->right->parent = del;
                            del->right = tmp->right;
                        }
                        else if (tmp->left)
                        {
                            tmp->left->parent = del;
                            del->left = tmp->left;
                        }
                        if (!tmp->right && !tmp->left)
                        {
                            if (tmp->parent->right == tmp)
                                tmp->parent->right = NULL;
                            else if (tmp->parent->left == tmp)
                                tmp->parent->left = NULL;
                        }
                        _Alloc.destroy(tmp);
                        _Alloc.deallocate(tmp, 1);
                    }
                    else
                    {
                        nodePtr tmp = (del->left != NULL) ? del->left : del->right;
                        if (tmp)
                        {
                            tmp->parent = del->parent;
                            if (!tmp->parent)
                            {
                                _Alloc.destroy(del);
                                _Alloc.deallocate(del, 1);
                                del = tmp;
                                _Root = tmp;
                                return ;
                            }
                        }
                        else if (del->parent)
                        {
                            if (del->parent->right == del)
                                del->parent->right = NULL;
                            if (del->parent->left == del)
                                del->parent->left = NULL;
                        }
                        if (del->left)
                        {
                            if (del->parent->left == del)
                                del->parent->left = tmp;
                            else
                                del->parent->right = tmp;
                        }
                        else if (del->right)
                        {
                            if (del->parent->right == del)
                                del->parent->right = tmp;
                            else
                                del->parent->left = tmp;
                        }
                        if (del == _Root && !del->right && !del->left)
                        {
                            _Alloc.destroy(del);
                            _Alloc.deallocate(del, 1);
                            del = _Root = NULL;
                            return ;
                        }
                        _Alloc.destroy(del);
                        _Alloc.deallocate(del, 1);
                        del = NULL;
                    }
                }
			}

			nodePtr nodeLeft(nodePtr node) const {
				nodePtr ret = node;
				if (ret) {
					while (ret->left)
						ret = ret->left;
				}
				return (ret);
			}
			nodePtr	nodeRight(nodePtr node) const {
				nodePtr ret = node;
				if (ret) {
					while (ret->right)
						ret = ret->right;
				}
				return (ret);
			}

			void 	leftRotate(nodePtr x) {
				nodePtr y = x->right;
				x->right = y->left;
				if (y->left != 0)
					y->left->parent = x;
				y->parent = x->parent;
				if (x->parent == 0)
					this->_Root = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->left = x;
				x->parent = y;
				x->bf = x->bf - 1 - ft::max(0, y->bf);
				y->bf = y->bf - 1 + ft::min(0, x->bf);
			}
			void 	rightRotate(nodePtr x) {
				nodePtr y = x->left;
				x->left = y->right;
				if (y->right != 0)
					y->right->parent = x;
				y->parent = x->parent;
				if (x->parent == 0)
					this->_Root = y;
				else if (x == x->parent->right)
					x->parent->right = y;
				else
					x->parent->left = y;
				y->right = x;
				x->parent = y;
				x->bf = x->bf + 1 - ft::min(0, y->bf);
				y->bf = y->bf + 1 + ft::max(0, x->bf);
			}
			void 	rebalance(nodePtr node) {
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
			void 	updateBalance(nodePtr node) {
                if (node) {
                    if (node->bf < -1 || node->bf > 1) {
                        rebalance(node);
                        return;
                    }
                    if (node->parent != 0) {
                        if (node == node->parent->left)
                            node->parent->bf -= 1;
                        if (node == node->parent->right)
                            node->parent->bf += 1;
                        if (node->parent->bf != 0)
                            updateBalance(node->parent);
                    }
                }
			}
			void 	insert_lastNode(nodePtr last){
				if (_Root) {
					iterator it = nodeRight(_Root);
					nodePtr prevlast = it.base();
					prevlast->right = last;
					last->parent = prevlast;
				}
				else
					_Root = last;
			}
			nodePtr clear_lastNode() {
				nodePtr last;
				if (_Root->last){
					last = _Root;
					_Root = 0;
				}
				else {
					iterator it = nodeRight(_Root);
					last = it.base();
					last->parent->right = 0;
					last->parent = 0;
				}
				return (last);
			}
	};
}

#endif