#ifndef FT_STACK_HPP
#define FT_STACK_HPP

#include "ft_Vector.hpp"

namespace ft{
	template< class T, class Container = ft::vector<T> >
	class stack{
		public:

			typedef typename Container::value_type  value_type;
			typedef          Container              container_type;
			typedef typename Container::size_type   size_type;

			explicit    stack(const Container &ctnr = Container()) : c(ctnr){}

			bool        empty() const { return c.empty(); }
			size_type   size() const { return c.size(); }
			void        push(const value_type &val) { c.push_back(val); }
			void        pop() { c.pop_back(); }

			value_type          &top() { return c.back(); }
			const value_type    &top() const { return c.back(); }


		    friend bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return (lhs.c == rhs.c); }
			friend bool operator!=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs) { return (lhs.c != rhs.c); }
			friend bool operator<(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs) { return (lhs.c < rhs.c); }
			friend bool operator<=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs) { return (lhs.c <= rhs.c); }
			friend bool operator>(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs) { return (lhs.c > rhs.c); }
			friend bool operator>=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs) { return (lhs.c >= rhs.c); }

		protected:
			Container c;
	};
}

#endif