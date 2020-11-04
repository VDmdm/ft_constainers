/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 18:28:02 by jalvaro           #+#    #+#             */
/*   Updated: 2020/11/04 10:16:24 by jalvaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <limits>
#include "RandomIterator.hpp"

#ifndef ENABLE
#define ENABLE

template<bool B, class T = void>
struct enable_if {};
 
template<class T>
struct enable_if<true, T> { typedef T type; };

#endif

namespace ft {

	template <typename T, typename Alloc = std::allocator<T> >
	class vector {
	
	public:
	
		typedef T											value_type;
		typedef Alloc										allocator_type;
		typedef std::size_t									size_type;
		typedef std::ptrdiff_t								difference_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename ft::VectIter<T>					iterator;
		typedef typename ft::ConstVectIter<T>				const_iterator;
		typedef typename ft::ReverseVectIter<T>				reverse_iterator;
		typedef typename ft::ConstReverseVectIter<T>		const_reverse_iterator;

	private:

		value_type				*_base;
		size_type				_size;
		size_type				_capacity;
		allocator_type			_Alloc;

	public:

		/* Coplien */
		explicit vector (const allocator_type& alloc = allocator_type()): _size(0), _capacity(0) {
			
			this->_size = 0;
			this->_capacity = 0;
			this->_Alloc = alloc;
			this->_base = nullptr;

		}

		explicit vector (size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type()) {
			
			this->_Alloc = alloc;
			if (n > 0)
			{
				this->_size = n;
				this->_capacity = n;
				this->_base = this->_Alloc.allocate(n);
				for (size_type i = 0; i < n; i++)
					this->_base[i] = val;
			}
			else
			{
				this->_capacity = 0;
				this->_size = 0;
				this->_base = nullptr;
			}
			
		}

		template <class InputIterator>
        vector (InputIterator first, typename enable_if < std::is_class <InputIterator>::value, InputIterator>::type last,
                const allocator_type& alloc = allocator_type()) {

			this->_Alloc = alloc;
			this->_size = 0;
			this->_capacity = 0;
			while (first != last)
			{
				this->push_back(*first);
				++first;
			}
		}

		vector (const vector& x)
		{ 
			this->_Alloc = x._Alloc;
			this->_size = 0;
			this->_capacity = 0;
			*this = x;
		}

		vector &operator=(const vector &other) {
			
			this->clear();
			if (other.empty())
				return (*this);
			for (const_iterator beg = other.begin(); beg != other.end(); beg++)
				this->push_back(*beg);
			return (*this);
			
		}

		~vector(void) {
			
			if (this->_capacity > 0)
				this->_Alloc.deallocate(this->_base, this->_capacity);

		};

		/* Iterators */

		iterator begin(void) { return iterator(this->_base);}
		const_iterator begin(void) const { return iterator(this->_base);}
		iterator end(void) { return iterator(this->_base + this->_size);}
		const_iterator end(void) const { return iterator(this->_base + this->_size);}
		reverse_iterator rbegin(void) { return reverse_iterator(this->_base + this->_size - 1);}
		const_reverse_iterator rbegin(void) const { return reverse_iterator(this->_base + this->_size - 1);}
		reverse_iterator rend(void) { return reverse_iterator(this->_base - 1);}
		const_reverse_iterator rend(void) const { return reverse_iterator(this->_base - 1);}

		/* Capacity */

		size_type size(void) const { return (this->_size); }
		size_type max_size(void) const { return std::numeric_limits<size_type>::max(); }
		void resize (size_type n, value_type val = value_type()) {

			if (this->_size == n)
				return ;
			while (this->_size != n)
			{
				if (this->_size > n)
					this->pop_back();
				else
					this->push_back(val);
			}
		};
		size_type capacity() const { return (this->_capacity); };
		bool empty(void) const { return !this->_size ? 1 : 0; }
		void reserve (size_type n) {

			value_type *tmp;

			if (this->_capacity >= n)
				return ;
			tmp = this->_Alloc.allocate(n);
			for (size_type i = 0; i < this->_size; i++)
				tmp[i] = this->_base[i];
			if (this->_capacity)
				this->_Alloc.deallocate(this->_base, this->_capacity);
			this->_base = tmp;
			this->_capacity = n;
			
		}
		/* Element access */
		reference operator[](size_type i) { return (this->_base[i]); }
		const_reference operator[](size_type i) const { return (this->_base[i]); }
		reference at (size_type n) {

			if (n >= this->_size)
				throw std::out_of_range("Out of range");
			return (this->_base[n]);

		}
		const_reference at (size_type n) const { return (this->at(n)); }
		reference front(void) { return (this->_base[0]); }
		const_reference front(void) const { return (this->_base[0]); }
		reference back(void) { return (this->_base[this->_size - 1]); }
		const_reference back(void) const { return (this->_base[this->_size - 1]); }
		
		/* Modifiers */
		template <class InputIterator>
		void assign (InputIterator first, typename enable_if < std::is_class <InputIterator>::value, InputIterator>::type last) {

			this->clear();
			while (first != last)
			{
				this->push_back(*first);
				++first;
			}

		}
		void assign (size_type n, const value_type& val) {

			this->clear();
			while (n--)
				this->push_back(val);

		}

		void push_back (const value_type& val) {

			if (this->_size >= this->_capacity)
				this->reserve(this->_capacity + 50);
			this->_base[this->_size] = val;
			this->_size++;

		}

		void pop_back(void) {

			if (this->_size)
				--this->_size;
			if (this->_capacity - this->_size > 50)
			{
				pointer tmp = this->_Alloc.allocate(this->_capacity - 50);
				for (size_type i = 0; i < this->_size; i++)
					tmp[i] = this->_base[i];
				this->_Alloc.deallocate(this->_base, this->_capacity);
				this->_base = tmp;
				this->_capacity = this->_capacity - 50;
			}
			
		}

		iterator insert (iterator position, const value_type& val) {

			iterator beg = this->begin();
			size_type head = position - beg;
			size_type tail = this->_size - head;
			size_type n = 1;

			if (this->_size + n > this->_capacity)
				this->reserve(this->_capacity + n);
			for (size_type i = 0; i < tail; i++)
				this->_base[(this->_size + n - 1) - i] = this->_base[(tail - 1) - i];
			for (size_type i = 0; i < n; i++)
				this->_base[head + i] = val;
			this->_size = this->_size + n;

			return (iterator(this->_base + head));

		}
		
    	void insert (iterator position, size_type n, const value_type& val) {
			
			iterator beg = this->begin();
			size_type head = position - beg;
			size_type tail = this->_size - head;
			if (n == 0)
				return ;
			if (this->_size + n > this->_capacity)
				this->reserve(this->_capacity + n);
			for (size_type i = 0; i < tail; i++)
				this->_base[(this->_size + n - 1) - i] = this->_base[(tail - 1) - i];
			for (size_type i = 0; i < n; i++)
				this->_base[head + i] = val;
			this->_size = this->_size + n;
		}

		template <class InputIterator>
    	void insert (iterator position, InputIterator first, typename enable_if < std::is_class <InputIterator>::value, InputIterator>::type last){
			
			iterator beg = this->begin();
			size_type head = position - beg;
			size_type tail = this->_size - head;
			InputIterator fst = first;
			size_type n = 0;

			while (fst != last)
			{
				n++;
				fst++;
			}
			if (n == 0)
				return ;
			if (this->_size + n > this->_capacity)
				this->reserve(this->_capacity + n);
			for (size_type i = 0; i < tail; i++)
				this->_base[(this->_size + n - 1) - i] = this->_base[(tail - 1) - i];
			for (size_type i = 0; i < n; i++)
			{
				this->_base[head + i] = *first;
				first++;
			}
			this->_size = this->_size + n;

		}

		iterator erase (iterator position) {
			
			iterator end = this->end();
			iterator ret = position;

			while (position != end)
			{
				if(position + 1 != end)
					*position = *(position + 1);
				++position;
			}
			this->_size--;
			return (ret);
		}

		iterator erase (iterator first, iterator last) {

			iterator end = this->end();
			iterator ret = (first == this->begin()? first: first - 1);
			size_type dif = last - first;

			if (dif == this->_size)
			{
				this->_size = 0;
				return (last);
			}

			while (last != end)
			{
				std::cout << *last << std::endl;
				*first = *last;
				last++;
				first++;
			}
			this->_size -= dif;
			return (ret);

		}

		void swap (vector& x)
		{
			value_type *tmp_base = this->_base;
			this->_base = x._base;
			x._base = tmp_base;

			size_type tmp = this->_capacity;
			this->_capacity = x._capacity;
			x._capacity = tmp;

			tmp = this->_size;
			this->_size = x._size;
			x._size = tmp;

			allocator_type tmp_alloc = this->_Alloc;
			this->_Alloc = x._Alloc;
			x._Alloc = tmp_alloc;
			
		}

		void clear() {

			if (this->_size == 0)
				return ;
			this->_Alloc.deallocate(this->_base, this->_capacity);
			this->_base = nullptr;
			this->_size = 0;
			this->_capacity = 0;

		}
	};
};

template <class T, class Alloc>
bool operator==(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {

	if (lhs.size() != rhs.size())
		return (false);
	if (lhs.size() == 0 && rhs.size() == 0)
		return (true);
	typename ft::vector<T>::const_iterator  beg1 = lhs.begin();
	typename ft::vector<T>::const_iterator  beg2 = rhs.begin();
	typename ft::vector<T>::const_iterator  end1 = lhs.end();
	typename ft::vector<T>::const_iterator  end2 = rhs.end();

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
bool operator!=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {

	return (!(lhs == rhs));
	
}

template <class T, class Alloc>
bool operator<(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {

	if (lhs.size() < rhs.size())
		return (true);
	if (lhs.size() > rhs.size() || (lhs.size() == 0 && rhs.size() == 0))
		return (false);
	
	typename ft::vector<T>::const_iterator  beg1 = lhs.begin();
	typename ft::vector<T>::const_iterator  beg2 = rhs.begin();
	typename ft::vector<T>::const_iterator  end1 = lhs.end();
	typename ft::vector<T>::const_iterator  end2 = rhs.end();

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
bool operator<=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {

	return (lhs < rhs || lhs == rhs);
	
}

template <class T, class Alloc>
bool operator>(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs){

	if (lhs.size() > rhs.size())
		return (true);
	if (lhs.size() < rhs.size() || (lhs.size() == 0 && rhs.size() == 0))
		return (false);
	typename ft::vector<T>::const_iterator beg1 = lhs.begin();
	typename ft::vector<T>::const_iterator  beg2 = rhs.begin();
	typename ft::vector<T>::const_iterator  end1 = lhs.end();
	typename ft::vector<T>::const_iterator  end2 = rhs.end();

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
bool operator>=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {

	return (lhs > rhs || lhs == rhs);

}

template <class T, class Alloc>
void swap(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {

	lhs.swap(rhs);

}

#endif