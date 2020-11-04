/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 19:56:42 by jalvaro           #+#    #+#             */
/*   Updated: 2020/11/04 10:32:03 by jalvaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include "List.hpp"

namespace ft {

	template< class T, class Container = ft::list<T> >
	class queue {

	public:

		typedef Container							container_type;
		typedef typename Container::value_type		value_type;
		typedef	typename Container::size_type		size_type;
		typedef	typename Container::reference		reference;
		typedef	typename Container::const_reference const_reference;

	private:

		container_type	_base;
		size_type		_size;

	public:

		/* Coplien */
		explicit queue (const container_type& ctnr = container_type()):
		_base(ctnr), _size(0) {}

		queue( const queue& other ): _size(0) { *this = other; }

		queue& operator=( const queue& other ) {

			this->_base = other._base;
			this->_size = other._size;
			return (*this);

		}

		~queue(void) {}

		/* Member functions */

		bool empty() const { return (this->_size == 0); }

		size_type size(void) const { return (this->_size); }

		value_type& front(void) { return (this->_base.front()); }

		const value_type& front(void) const { return (this->_base.front()); }

		value_type& back(void) { return (this->_base.back()); }

		const value_type& back(void) const { return (this->_base.back()); }

		void push (const value_type& val) {
			
			this->_size++;
			return (this->_base.push_back(val));
			
		}

		void pop (void) { 
			
			if (this->_size)
				this->_size--;
			return (this->_base.pop_front());
		
		}

	};
}

template <class T, class Container>
bool operator==(const ft::queue<T, Container> &lhs, const ft::queue<T, Container> &rhs) {

	return (lhs._base == rhs._base);

}

template <class T, class Container>
bool operator!=(const ft::queue<T, Container> &lhs, const ft::queue<T, Container> &rhs) {

	return (lhs._base != rhs._base);

}

template <class T, class Container>
bool operator<(const ft::queue<T, Container> &lhs, const ft::queue<T, Container> &rhs) {

	return (lhs._base < rhs._base);

}

template <class T, class Container>
bool operator<=(const ft::queue<T, Container> &lhs, const ft::queue<T, Container> &rhs) {

	return (lhs._base <= rhs._base);

}

template <class T, class Container>
bool operator>(const ft::queue<T, Container> &lhs, const ft::queue<T, Container> &rhs) {

	return (lhs._base > rhs._base);

}

template <class T, class Container>
bool operator>=(const ft::queue<T, Container> &lhs, const ft::queue<T, Container> &rhs) {

	return (lhs._base >= rhs._base);

}

#endif