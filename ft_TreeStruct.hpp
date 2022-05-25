#ifndef FT_TREESTRUCT_HPP
#define FT_TREESTRUCT_HPP

namespace ft {
	template <class T>
	struct tree_struct {
		typedef T value_type;
		T               Stock;
		int             bf;
		tree_struct     *left;
		tree_struct     *right;
		tree_struct     *prev;

		tree_struct() : Stock(), bf(0), left(0), right(0), prev(0) {}
		tree_struct(const T &x) : Stock(x), bf(0), left(0), right(0), prev(0) {}
		tree_struct(const tree_struct &x) : Stock(x.Stock), bf(0), left(x.left), right(x.right), prev(x.prev) {}
		~tree_struct() {}
		tree_struct &operator=(const tree_struct &x) {
			Stock = x.Stock;
			left = x.left;
			right = x.right;
			prev = x.prev;
			bf = x.bf;
			return (*this);
		}
	};
}

#endif