/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 19:56:42 by jalvaro           #+#    #+#             */
/*   Updated: 2020/09/19 12:18:28 by jalvaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP
#include <iostream>
#include "List.hpp"

namespace ft {

	template< class T, class Container = ft::list<T> >
	class stack {

	public:

		typedef Container							container_type;
		typedef typename Container::value_type		value_type;
		typedef	typename Container::size_type		size_type;
		typedef	typename Container::reference		reference;
		typedef	typename Container::const_reference const_reference;

	private:

		container_type _base;

	public:

		/* Coplien */
		explicit stack (const container_type& ctnr = container_type()):
		_base(ctnr) {}

		stack( const stack& other ) { *this = other; }

		stack& operator=( const stack& other ) {

			this->_base = other._base;
			return (*this);

		}

		~stack(void) {}

		/* Member functions */

		bool empty() const { return (this->_base.empty()); }

		size_type size(void) const { return (this->_base.size()); }

		value_type& top(void) { return (this->_base.back()); }

		const value_type& top(void) const { return (this->_base.back()); }

		void push (const value_type& val) { return (this->_base.push_back(val)); }

		void pop (void) { return (this->_base.pop_back()); }

	};
}

template <class T, class Container>
bool operator==(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs) {

	return (lhs._base == rhs._base);

}

template <class T, class Container>
bool operator!=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs) {

	return (lhs._base != rhs._base);

}

template <class T, class Container>
bool operator<(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs) {

	return (lhs._base < rhs._base);

}

template <class T, class Container>
bool operator<=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs) {

	return (lhs._base <= rhs._base);

}

template <class T, class Container>
bool operator>(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs) {

	return (lhs._base > rhs._base);

}

template <class T, class Container>
bool operator>=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs) {

	return (lhs._base >= rhs._base);

}
#endif