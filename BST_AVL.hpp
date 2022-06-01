#ifndef BST_AVL_HPP
#define BST_AVL_HPP

#include <memory>
#include "ft_Utility.hpp"
#include "ft_RevIter.hpp"
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
			virtual ~BST_AVL() { clear(); }

			BST_AVL	&operator=(const BST_AVL &inst) {
				if (*this != inst){
					clear();
					_Comp = inst._Comp;
					_Size = 0;
					insert(inst.begin(), inst.end());
				}
				return (*this);
			}

			size_type size() const { return (_Size); }
			size_type max_size() const { return (_Alloc.max_size()); }

			void	clear() {
				destroy(_Root);
				_Size = 0;
			}
			void	swap(BST_AVL &x) {
				ft::swap(_Root, x._Root);
				ft::swap(_Size, x._Size);
				ft::swap(_Comp, x._Comp);
				ft::swap(_Alloc, x._Alloc);
			}

			void						erase(iterator position){
				nodePtr last = clear_lastNode();
				deleteNode(position.base(), position->first);
				_Size--;
				updateBalance(nodeLeft(_Root));
				updateBalance(nodeRight(_Root));
				insert_lastNode(last);
			}
			ft::pair<iterator, bool>    insert(const value_type &val){
				nodePtr last = clear_lastNode();
				ft::pair<iterator, bool> ret = insertNode(val);
				insert_lastNode(last);
				return (ret);
			}

			nodePtr 				nodeSearch(const key_type &k) const {
				nodePtr ret = _Root;
				while (ret){
					if (ret->data.first == k)
						return (ret);
					else if (k < ret->data.first)
						ret = ret->left;
					else
						ret = ret->right;
				}
				return (0);
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
					supp = 0;
				}
			}

			ft::pair<iterator, bool>	insertNode(const value_type &value) {
				nodePtr node = create(value);
				nodePtr y = 0;
				nodePtr x = _Root;
				while (x != 0) {
					y = x;
					if (_Comp(value.first, x->data.first))
						x = x->left;
					else if (_Comp(x->data.first, value.first))
						x = x->right;
					else
						return ( ft::pair<iterator, bool>(iterator(x), false));
				}
				node->parent = y;
				if (y == 0)
					_Root = node;
				else if (node->data < y->data)
					y->left = node;
				else
					y->right = node;
				updateBalance(node);
				_Size++;
				return ( ft::pair<iterator, bool>(iterator(node), true));
			}
			nodePtr						deleteNode(nodePtr node, key_type key) {
				if (node == 0) return node;
				else if (key < node->data) node->left = deleteNode(node->left, key);
				else if (key > node->data) node->right = deleteNode(node->right, key);
				else {
					if (node->left == 0 && node->right == 0) {
						_Alloc.destroy(node);
						_Alloc.deallocate(node, 1);
						node = 0;
					}
					else if (node->left == 0) {
						nodePtr temp = node;
						node = node->right;
						_Alloc.destroy(temp);
						_Alloc.deallocate(temp, 1);
					}
					else if (node->right == 0) {
						nodePtr temp = node;
						node = node->left;
						_Alloc.destroy(temp);
						_Alloc.deallocate(temp, 1);
					}
					else {
						nodePtr temp = nodeLeft(node->right);
						node->data = temp->data;
						node->right = deleteNode(node->right, temp->data);
					}
				}
				return node;
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