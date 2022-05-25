#ifndef FT_STACK_HPP
# define FT_STACK_HPP

# include "vector.hpp"

namespace ft {
	template< class T, class Container = ft::vector<T> >
	class stack {
		public:

			typedef T										value_type;
			typedef	Container								container_type;
			typedef	typename Container::size_type			size_type;
			typedef	typename Container::reference			reference;
			typedef	typename Container::const_reference		const_reference;

			explicit	stack(const container_type& ctnr = container_type()) : _c(ctnr){}
			virtual		~stack() {}

			stack& operator=(const stack& other) {
				if (*this == other)
					return (*this);
				_c = other._c;
				return (*this);
			}

			reference		top() { return _c.back(); }
			const_reference	top() const { return _c.back(); }
			bool			empty() const { return _c.empty(); }
			size_type		size() const { return _c.size(); }
			void			push(const_reference val) { _c.push_back(val); }
			void			pop() { _c.pop_back(); }

			template< class U, class Cont>
		    friend bool operator==(const ft::stack<U, Cont> &lhs, const ft::stack<U, Cont> &rhs);
			template< class U, class Cont>
			friend bool operator!=(const ft::stack<U, Cont> &lhs, const ft::stack<U, Cont> &rhs);
			template< class U, class Cont>
			friend bool operator<(const ft::stack<U, Cont> &lhs, const ft::stack<U, Cont> &rhs);
			template< class U, class Cont>
			friend bool operator<=(const ft::stack<U, Cont> &lhs, const ft::stack<U, Cont> &rhs);
			template< class U, class Cont>
			friend bool operator>(const ft::stack<U, Cont> &lhs, const ft::stack<U, Cont> &rhs);
			template< class U, class Cont>
			friend bool operator>=(const ft::stack<U, Cont> &lhs, const ft::stack<U, Cont> &rhs);

		protected:
			container_type _c;
	};

	template< class T, class Container>
	bool operator==(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs) { return (lhs._c == rhs._c); }
	template< class T, class Container>
	bool operator!=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs) { return (lhs._c != rhs._c); }
	template< class T, class Container>
	bool operator<(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs) { return (lhs._c < rhs._c); }
	template< class T, class Container>
	bool operator<=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs) { return (lhs._c <= rhs._c); }
	template< class T, class Container>
	bool operator>(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs) { return (lhs._c > rhs._c); }
	template< class T, class Container>
	bool operator>=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs) { return (lhs._c >= rhs._c); }
}

#endif