/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 18:28:02 by jalvaro           #+#    #+#             */
/*   Updated: 2020/09/21 10:57:39 by jalvaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <limits>
#include "ListIterators.hpp"

#ifndef ENABLE
#define ENABLE

template<bool B, class T = void>
struct enable_if {};
 
template<class T>
struct enable_if<true, T> { typedef T type; };

#endif

namespace ft {

	template <typename T, typename Alloc = std::allocator<T> >
	class list {
	
	public:
	
		typedef T										value_type;
		typedef Alloc									allocator_type;
		typedef std::size_t								size_type;
		typedef std::ptrdiff_t							difference_type;
		typedef T&										reference;
		typedef const T&								const_reference;
		typedef T*										pointer;
		typedef const T*								const_pointer;
		typedef typename ft::ListIter<T>				iterator;
		typedef typename ft::ConstListIter <T>			const_iterator;
		typedef typename ft::revListIter <T>			reverse_iterator;
		typedef typename ft::ConstRevListIter<T>		const_reverse_iterator;

	private:

		dll<value_type>			*_front;
		dll<value_type>			*_back;
		dll<value_type>			*_end;
		size_type				_length;
		allocator_type			_Alloc;
		std::allocator< dll < T > >	_nodeAlloc;

	public:

		/* Coplien */
		list(void): _length(0) {

			this->_end = this->_nodeAlloc.allocate(1);
			this->_nodeAlloc.construct(this->_end);
			this->_end->data = new T();
			this->_end->prev = this->_end;
			this->_end->next = this->_end;
			this->_front = this->_end;
			this->_back = this->_end;

		}

		explicit list(const Alloc &alloc): _length(0) {
			
			this->_end = this->_nodeAlloc.allocate(1);
			this->_nodeAlloc.construct(this->_end);
			this->_end->data = new T();
			this->_end->prev = this->_end;
			this->_end->next = this->_end;
			this->_front = this->_end;
			this->_back = this->_end;
			this->_Alloc = alloc;
			
		}

		explicit list(size_type count, const T &value = T(),
						const Alloc &alloc = Alloc()) {
			
			this->_end = this->_nodeAlloc.allocate(1);
			this->_nodeAlloc.construct(this->_end);
			this->_end->data = new T();
			this->_end->prev = this->_end;
			this->_end->next = this->_end;
			this->_Alloc = alloc;
			this->_front = this->_end;
			this->_back = this->_end;
			this->_length = 0;
			while (count--)
				this->push_back(value);
	
		}

		template< class InputIt >
		list(InputIt first, typename enable_if < std::is_class <InputIt>::value, InputIt>::type last,
						const Alloc &alloc = Alloc()) {
			
			this->_end = this->_nodeAlloc.allocate(1);
			this->_nodeAlloc.construct(this->_end);
			this->_end->data = new T();
			this->_end->prev = this->_end;
			this->_end->next = this->_end;
			this->_front = this->_end;
			this->_back = this->_end;
			this->_length = 0;
			this->_Alloc = alloc;
			while (first != last)
			{
				this->push_back(*first);
				++first;
			}
		}
		
		list (const list &other): _length(0) {

			this->_end = this->_nodeAlloc.allocate(1);
			this->_nodeAlloc.construct(this->_end);
			this->_end->data = new T();
			this->_end->prev = this->_end;
			this->_end->next = this->_end;
			this->_front = this->_end;
			this->_back = this->_end;
			*this = other;
	
		}

		list &operator=(const list &other) {

			this->clear();
			if (other.empty())
				return (*this);
			for (const_iterator beg = other.begin(); beg != other.end(); beg++)
				this->push_back(*beg);
			return (*this);
		}

		~list(void) {

			this->clear();
			delete this->_end->data;
			this->_nodeAlloc.destroy(this->_end);
			this->_nodeAlloc.deallocate(this->_end, 1);
			
		}

		/* Methods */
		void assign( size_type count, const T& value ) {

			this->clear();
			while(count--)
				this->push_back(value);

		}
		template< class InputIt >
		void assign( InputIt first, typename enable_if < std::is_class <InputIt>::value, InputIt>::type last ) {

			this->clear();
			while (first != last)
			{
				this->push_back(*first);
				first++;
			}
			
		}

		/* Element access */
		reference				front(void) { return *this->_front->data; }
		const_reference 		front(void) const { return *this->_front->data; }
		reference				back(void) { return *this->_back->data; }
		const_reference 		back(void) const { return *this->_back->data; }
		
		/* Iterators */
		iterator				begin(void) { return iterator(this->_front); }
		const_iterator			begin(void) const { return const_iterator(this->_front); }
		iterator				end(void) { return iterator( this->_end ); }
		const_iterator			end(void) const { return const_iterator( this->_end ); }
		reverse_iterator		rbegin(void) { return reverse_iterator( this->_back ); }
		const_reverse_iterator	rbegin(void) const { return const_reverse_iterator(this->_back ); }
		reverse_iterator		rend(void) { return reverse_iterator( this->_end ); }
		const_reverse_iterator	rend(void) const { return const_reverse_iterator( this->_end ); }
		
		/* Capacity */
		bool 					empty(void) const { return !this->_length ? 1 : 0; }
		size_type				size(void) const { return this->_length; };
		size_type				max_size(void) const { return std::numeric_limits<size_type>::max(); }

		/* Modifiers */
		void clear(void) {

			while (this->_length)
				this->pop_back();

		}

		iterator insert( iterator pos, const T& value ) {
			
			dll<T> *tmp = this->_nodeAlloc.allocate(1);
			this->_nodeAlloc.construct(tmp);

			tmp->data = this->_Alloc.allocate(1);
			this->_Alloc.construct(tmp->data, value);
			tmp->next = pos.getNode();
			tmp->prev = pos.getNode()->prev;
			tmp->next->prev = tmp;
			tmp->prev->next = tmp;
			if (tmp->prev == this->_end)
				this->_front = tmp;
			if (tmp->next == this->_end)
				this->_back = tmp;
			this->_length++;
			return (iterator(tmp));

		}
		
		void insert( iterator pos, size_type count, const T& value ) {

			while (count--)
				this->insert(pos, value);

		}

		template< class InputIt >
		void insert( iterator pos, InputIt first, typename enable_if < std::is_class <InputIt>::value, InputIt>::type last) {

			while (first != last)
			{
				this->insert(pos, *first);
				first++;
			}

		}

		iterator erase( iterator pos ) {

			dll<T> *cur = pos.getNode();
			dll<T> *next = cur->next;
			dll<T> *prev = cur->prev;
			if (cur == this->_end)
				return (iterator(this->_end));
			next->prev = prev;
			prev->next = next;
			this->_Alloc.destroy(cur->data);
			this->_Alloc.deallocate(cur->data, 1);
			this->_nodeAlloc.destroy(cur);
			this->_nodeAlloc.deallocate(cur, 1);
			if (prev == this->_end)
				this->_front = next;
			if (next == this->_end)
				this->_back = prev;
			this->_length--;
			return (iterator(next));

		}

		iterator erase( iterator first, iterator last ) {

			if (first == last)
				return last;
			while (first != last)
				first = this->erase(first);
			this->erase(first);
			if (last.getNode() == this->_end)
				return (iterator(this->_end));
			last++;
			return (iterator(last.getNode()));
		}
		
		void push_back( const T& value ) {
			
			if (this->_back == this->_end)
			{
				this->_back = this->_nodeAlloc.allocate(1);
				this->_nodeAlloc.construct(this->_back);
				this->_back->next = this->_end;
				this->_back->prev = this->_end;
				this->_back->data = this->_Alloc.allocate(1);
				this->_Alloc.construct(this->_back->data, value);
				this->_end->next = this->_back;
				this->_end->prev = this->_back;
				this->_front = this->_back;
			}
			else
			{
				this->_back->next = this->_nodeAlloc.allocate(1);
				this->_nodeAlloc.construct(this->_back->next);
				this->_back->next->prev = this->_back;
				this->_back = this->_back->next;
				this->_back->next = this->_end;
				this->_back->data = this->_Alloc.allocate(1);
				this->_Alloc.construct(this->_back->data, value);
				this->_end->prev = this->_back;
			}
			this->_length++;
		}
		
		void pop_back(void) {
			
			dll<T> *tmp;

			if (this->_back == this->_end)
				return ;
			tmp = this->_back->prev;
			this->_Alloc.destroy(this->_back->data);
			this->_Alloc.deallocate(this->_back->data, 1);
			this->_nodeAlloc.destroy(this->_back);
			this->_nodeAlloc.deallocate(this->_back, 1);
			if (tmp == this->_end)
			{
				this->_front = this->_end;
				this->_back = this->_end;
			}
			else
			{
				this->_back = tmp;
				this->_back->next = this->_end;
				this->_end->prev = this->_back;
			}
			this->_length--;
		}

		void push_front( const T& value ) {

			if (this->_front == this->_end)
			{
				this->_front = this->_nodeAlloc.allocate(1);
				this->_nodeAlloc.construct(this->_front);
				this->_front->next = this->_end;
				this->_front->prev = this->_end;
				this->_front->data = this->_Alloc.allocate(1);
				this->_Alloc.construct(this->_back->data, value);
				this->_end->next = this->_front;
				this->_end->prev = this->_front;
				this->_back = this->_front;
			}
			else
			{
				this->_front->prev = this->_nodeAlloc.allocate(1);
				this->_nodeAlloc.construct(this->_front->prev);
				this->_front->prev->next = this->_front;
				this->_front = this->_front->prev;
				this->_front->prev = this->_end;
				this->_front->data = this->_Alloc.allocate(1);
				this->_Alloc.construct(this->_front->data, value);
				this->_end->next = this->_front;
			}
			this->_length++;
		}
		
		void pop_front() {

			dll<T> *tmp;

			if (this->_front == this->_end)
				return ;
			tmp = this->_front->next;
			this->_Alloc.destroy(this->_front->data);
			this->_Alloc.deallocate(this->_front->data, 1);
			this->_nodeAlloc.destroy(this->_front);
			this->_nodeAlloc.deallocate(this->_front, 1);
			if (tmp == this->_end)
			{
				this->_back = this->_end;
				this->_front = this->_end;
			}
			else
			{
				this->_front = tmp;
				this->_front->prev = this->_end;
			}
			this->_length--;
		}

		void resize( size_type count, T value = T() ) {
			
			if (this->_length == count)
				return ;
			while (this->_length != count)
			{
				if (this->_length > count)
					this->pop_back();
				else
					this->push_back(value);
			}
		}

		void swap( list& other ) {

			dll<T> *tmp;
			size_type lngth;
			allocator_type All;

			/* _back ptr */
			tmp = other._back;
			other._back = this->_back;
			this->_back = tmp;
			/* _front ptr */
			tmp = other._front;
			other._front = this->_front;
			this->_front = tmp;
			/* _end ptr */
			tmp = other._end;
			other._end = this->_end;
			this->_end = tmp;
			/* _length ptr */
			lngth = other._length;
			other._length = this->_length;
			this->_length = lngth;
			/* _Alloc ptr */
			All = other._Alloc;
			other._Alloc = this->_Alloc;
			this->_Alloc = All;
		}

		/* Operations */
		void merge( list& other ) {
			
			iterator beg1 = this->begin();
			iterator end1 = this->end();
			iterator beg2 = other.begin();
			iterator end2 = other.end();
			iterator next;

			//if (this == other)
			//	return ;
			while (other._length)
			{
				if (*beg2 < *beg1 || beg1 == end1)
				{
					next = beg2;
					next++;
					splice(beg1, other, beg2);
					beg2 = next;
				}
				else
					beg1++;
			}
		}

		template <class Compare>
		void merge( list& other, Compare comp ) {
			
			iterator beg1 = this->begin();
			iterator end1 = this->end();
			iterator beg2 = other.begin();
			iterator end2 = other.end();
			iterator next;

			//if (this == other)
			//	return ;
			while (other._length)
			{
				if (comp(*beg2, *beg1) || beg1 == end1)
				{
					next = beg2;
					next++;
					splice(beg1, other, beg2);
					beg2 = next;
				}
				else
					beg1++;
			}
		}

		void splice( iterator pos, list& other ) {

			this->splice(pos, other, other.begin(), other.end());
			/*iterator beg = other.begin();
			iterator end = other.end();
			
			pos.getNode().prev.next = beg.getNode();
			beg.getNode().prev = pos.getNode().prev;
			pos.getNode().prev = end.getNode().prev;
			end.getNode().prev.next = pos.getNode();
			other._front = other._end;
			other._back = other._end;
			other._end.next = other._end;
			other._end.prev = other._end;*/
			
		}

		void splice( iterator pos, list& other, iterator it ) {

			if (it.getNode() == other._end)
				return ;
			it.getNode()->prev->next = it.getNode()->next;
			it.getNode()->next->prev = it.getNode()->prev;
			other._front = other._end->next;
			other._back = other._end->prev;
			pos.getNode()->prev->next = it.getNode();
			it.getNode()->prev = pos.getNode()->prev;
			pos.getNode()->prev = it.getNode();
			it.getNode()->next = pos.getNode();
			this->_front = this->_end->next;
			this->_back = this->_end->prev;
			other._length--;
			this->_length++;

		}

		void splice( iterator pos, list& other,
            		iterator first, iterator last) {
			
			if (first.getNode() == other._end)
				return ;
			if (last.getNode() == other._end)
				last--;
			first.getNode()->prev->next = last.getNode()->next;
			last.getNode()->next->prev = first.getNode()->prev;
			other._front = other._end->next;
			other._back = other._end->prev;

			pos.getNode()->prev->next = first.getNode();
			first.getNode()->prev = pos.getNode()->prev;
			pos.getNode()->prev = last.getNode();
			last.getNode()->next = pos.getNode();
			this->_front = this->_end->next;
			this->_back = this->_end->prev;
			this->_length = 0;
			for (iterator beg = this->begin(); beg != this->end(); beg++)
				this->_length++;
			other._length = 0;
			for (iterator beg = other.begin(); beg != other.end(); beg++)
				other._length++;
			
		}

		void remove( const T& value ) {

			iterator beg = this->begin();
			iterator end = this->end();

			while (beg != end)
			{
				if (*beg == value)
					beg = this->erase(beg);
				else
					beg++;
			}
		}

		template< class UnaryPredicate >
		void remove_if( UnaryPredicate p ) {

			iterator beg = this->begin();
			iterator end = this->end();

			while (beg != end)
			{
				if (p(*beg))
					beg = this->erase(beg);
				else
					beg++;
			}
		}

		void reverse(void) {

			iterator beg = this->begin();
			iterator end = this->end();
			dll<T> *tmp;

			while (beg != end)
			{
				tmp = beg.getNode()->next;
				beg.getNode()->next = beg.getNode()->prev;
				beg.getNode()->prev = tmp;
				beg++;
			}
			tmp = this->_end->next;
			this->next = this->_end->prev;
			this->_end->prev = tmp;
			this->_front = tmp->next;
			this->_back = tmp->prev;

		}

		void unique(void) {

			iterator beg = this->begin();
			iterator end = this->end();
			T* elem = nullptr;

			while (beg != end)
			{
				if (elem && *elem == *beg)
					beg = this->erase(beg);
				else
				{
					elem = &(*beg);
					beg++;
				}
			}

		}
		template< class BinaryPredicate >
		void unique( BinaryPredicate p ) {

			iterator beg1 = this->begin();
			iterator beg2 = this->begin();
			iterator end = this->end();

			while (++beg2 != end)
			{
				if (p(*beg1, *beg2))
				{
					this->erase(beg2);
					beg2 = beg1;
				}
				else
					beg1++;
			}
		}

		void sort(void) {

			iterator beg1 = this->begin();
			iterator beg2 = this->begin();
			iterator end = this->end();
			T* tmp;

			while (++beg2 != end)
			{
				if (*beg2  < *beg1)
				{
					tmp = beg1.getNode()->data;
					beg1.getNode()->data = beg2.getNode()->data;
					beg2.getNode()->data = tmp;
					beg1 = this->begin();
					beg2 = this->begin();
				}
				else
					beg1++;
			}
		}

		template< class Compare >
		void sort( Compare comp ) {

			iterator beg1 = this->begin();
			iterator beg2 = this->begin();
			iterator end = this->end();
			T* tmp;

			while (++beg2 != end)
			{
				if (comp(*beg2, *beg1))
				{
					tmp = beg1.getNode()->data;
					beg1.getNode()->data = beg2.getNode()->data;
					beg2.getNode()->data = tmp;
					beg1 = this->begin();
					beg2 = this->begin();
				}
				else
					beg1++;
			}
		}

	};
	
};

template <class T, class Alloc>
bool operator==(const ft::list<T, Alloc> &lhs, const ft::list<T, Alloc> &rhs) {

	if (lhs.size() != rhs.size())
		return (false);
	typename ft::list<T>::const_iterator beg1 = lhs.begin();
	typename ft::list<T>::const_iterator beg2 = rhs.begin();
	typename ft::list<T>::const_iterator end1 = lhs.end();
	typename ft::list<T>::const_iterator end2 = rhs.end();

	while (beg1 != end1 && beg2 != end2 && *beg1 == *beg2)
	{
		beg1++;
		beg2++;
	}
	
	if (beg1 == end1 && beg2 == end2)
		return (true);
	return (false);

}

template <class T, class Alloc>
bool operator!=(const ft::list<T, Alloc> &lhs, const ft::list<T, Alloc> &rhs) {

	return (!(lhs == rhs));
	
}

template <class T, class Alloc>
bool operator<(const ft::list<T, Alloc> &lhs, const ft::list<T, Alloc> &rhs) {

	if (lhs.size() < rhs.size())
		return (true);
	if (lhs.size() > rhs.size())
		return (false);
	typename ft::list<T>::const_iterator beg1 = lhs.begin();
	typename ft::list<T>::const_iterator beg2 = rhs.begin();
	typename ft::list<T>::const_iterator end1 = lhs.end();
	typename ft::list<T>::const_iterator end2 = rhs.end();

	while (beg1 != end1 && beg2 != end2 && *beg1 == *beg2)
	{
		beg1++;
		beg2++;
	}
	
	if ((beg1 == end1 && beg2 == end2) || beg2 == end2 || *beg1 >= *beg2)
		return (false);
	return (true);
	
}

template <class T, class Alloc>
bool operator<=(const ft::list<T, Alloc> &lhs, const ft::list<T, Alloc> &rhs) {

	return (lhs < rhs || lhs == rhs);
	
}

template <class T, class Alloc>
bool operator>(const ft::list<T, Alloc> &lhs, const ft::list<T, Alloc> &rhs) {

	if (lhs.size() > rhs.size())
		return (true);
	if (lhs.size() < rhs.size())
		return (false);
	typename ft::list<T>::const_iterator beg1 = lhs.begin();
	typename ft::list<T>::const_iterator beg2 = rhs.begin();
	typename ft::list<T>::const_iterator end1 = lhs.end();
	typename ft::list<T>::const_iterator end2 = rhs.end();

	while (beg1 != end1 && beg2 != end2 && *beg1 == *beg2)
	{
		beg1++;
		beg2++;
	}
	
	if ((beg1 == end1 && beg2 == end2) || beg1 == end1 || *beg1 <= *beg2)
		return (false);
	return (true);
	
}

template <class T, class Alloc>
bool operator>=(const ft::list<T, Alloc> &lhs, const ft::list<T, Alloc> &rhs) {

	return (lhs > rhs || lhs == rhs);

}

template <class T, class Alloc>
void swap(const ft::list<T, Alloc> &lhs, const ft::list<T, Alloc> &rhs) {

	lhs.swap(rhs);

}

#endif