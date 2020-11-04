/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 16:00:42 by jalvaro           #+#    #+#             */
/*   Updated: 2020/11/04 10:16:27 by jalvaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <limits>
#include "Node.hpp"
#include "MapIterator.hpp"

#ifndef ENABLE
#define ENABLE

template<bool B, class T = void>
struct enable_if {};
 
template<class T>
struct enable_if<true, T> { typedef T type; };

#endif

namespace ft
{

	template < class Key, class T, class Compare = std::less<Key>, 
				class Alloc = std::allocator<std::pair<const Key,T> > >

	class map {

	public:

		typedef Key														key_type;
		typedef T														mapped_type;
		typedef std::pair<const key_type, mapped_type>					value_type;
		typedef Compare													key_compare;
		typedef Alloc													allocator_type;
		typedef typename allocator_type::reference						reference;
		typedef typename allocator_type::const_reference				const_reference;
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_pointer					const_pointer;
		typedef typename ft::MapIter< Key, T, Compare>					iterator;
		typedef typename ft::ConstMapIter< Key, T, Compare>				const_iterator;
		typedef typename ft::MapRevIter< Key, T, Compare>				reverse_iterator;
		typedef typename ft::ConstMapRevIter< Key, T, Compare>			const_reverse_iterator;
		typedef std::ptrdiff_t											difference_type;
		typedef std::size_t												size_type;

	private :

		_Node<key_type, mapped_type, key_compare, allocator_type>			_base;
		allocator_type														_alloc;
		size_type															_size;
		key_compare															_k_cmp;

		template <class Cmp>
		class value_cmp
		{
			friend class map;
		protected:
			Cmp comp;
			value_cmp(Cmp c) : comp(c) {} // constructed with map's comparison object
		public:
			typedef bool result_type;
			typedef std::pair<const Key, T> first_argument_type;
			typedef std::pair<const Key, T> second_argument_type;
			bool operator()(const first_argument_type &x, const second_argument_type &y) const
			{
				return comp(x.first, y.first);
			}
		};

	public:

		typedef value_cmp < key_compare >								value_compare;

		/* coplien */

		explicit map(const key_compare &comp = key_compare(),
					 const allocator_type &alloc = allocator_type()):
					 _base(alloc), _alloc(alloc), _k_cmp(comp) {
			
			this->_size = 0;

		}

		template <class InputIterator>
		map(InputIterator first, InputIterator last,
			const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type()):
			_base(alloc), _alloc(alloc), _k_cmp(comp) {
				
				this->_k_cmp = comp;
				this->_size = 0;
				this->_alloc = alloc;
				this->insert(first, last);

			}

		map(const map &x) {

			*this = x;

		}

		map &operator=(const map &other) {

			this->clear();
			this->_k_cmp = other._k_cmp;
			this->_alloc = other._alloc;
			const_iterator beg = other.begin();
			const_iterator end = other.end();
			while (beg != end)
			{
				this->insert(*beg);
				++beg;
			}
			return (*this);

		}

		~map(void) {

			if (this->_size)
				this->_base.node_destroy();

		};

		/* iterators */

		iterator begin(void) { 
			
			if (!this->_size)
				return (this->end());
			return iterator(this->_base.node_min()); 
		
		}

		const_iterator begin(void) const { 
			
			if (!this->_size)
				return (this->end());
			return const_iterator(this->_base.node_min()); 
		
		}

		iterator end(void) { return iterator(this->_base.get_end()); }
		const_iterator end(void) const { return const_iterator(this->_base.get_end()); }

		reverse_iterator rbegin(void) { 
			
			if (!this->_size)
				return (this->rend());
			return reverse_iterator(this->_base.node_max()); 
		}

		const_reverse_iterator rbegin(void) const {

			if (!this->_size)
				return (this->rend());
			return reverse_iterator(this->_base.node_max());
			
		}

		reverse_iterator rend(void) { return reverse_iterator(this->_base.get_rend()); }
		const_reverse_iterator rend(void) const { return const_reverse_iterator(this->_base.get_rend()); }

		/* capacity */

		size_type size(void) const { return (this->_size); }
		size_type max_size(void) const { return std::numeric_limits<size_type>::max(); }
		bool empty(void) const { return !this->_size ? 1 : 0; }

		/* element access */

		mapped_type& operator[] (const key_type& k) {

			node < Key, T > *tmp = this->_base.node_search(k);
			if (!tmp)
			{
				this->_size++;
				return ((this->_base.node_add(std::pair < key_type, mapped_type >(k, T())))->value->second);
			}
			return (tmp->value->second);

		}

		/* modifiers */

		std::pair<iterator, bool> insert(const value_type &val) {

			if (!this->_base.node_search(val))
			{
				this->_size++;
				return (std::pair < iterator, bool > (iterator(this->_base.node_add(val)), true));
			}
			return (std::pair < iterator, bool > (iterator(this->_base.node_search(val)), false));

		}

		iterator insert(iterator hint, const value_type &val) {
			
			(void)hint;
			if (!this->_base.node_search(val))
			{
				this->_size++;
				return (iterator(this->_base.node_add(val)));
			}
			return (iterator(this->_base.node_search(val)));
		}

		template <class InputIterator>
		void insert(InputIterator first, 
			typename enable_if < std::is_class <InputIterator>::value, InputIterator>::type last) {

			while (first != last)
			{
				insert(*first);
				first++;
			}
		}

		void erase (iterator position) {

			if (this->_size)
			{
				this->_base.node_delete(this->_base.get_base(), (*position).first);
				this->_base.node_set_end();
				this->_base.node_set_rend();
				this->_size--;
			}

		}

		size_type erase (const key_type& k) {
			
			node < Key, T > *tmp = this->_base.node_search(k);
			
			if (tmp)
			{
				this->_base.node_delete(this->_base.get_base(), k);
				this->_base.node_set_end();
				this->_base.node_set_rend();
				this->_size--;
				return (1);
			}
			return (0);

		}
		
		void erase (iterator first, iterator last)
		{
			iterator tmp = first;
			while (first != last)
			{
				tmp++;
				this->_base.node_delete(this->_base.get_base(), (*first).first);
				this->_size--;
				first = tmp;
			}
		}

		void swap (map & x) {

			node< Key, T >														*base;
			base = x._base.get_base();
			x._base.set_base(this->_base.get_base());
			this->_base.set_base(base);
			allocator_type														alloc;
			alloc = this->_alloc;
			this->_alloc = x._alloc;
			x._alloc = alloc;
			size_type															size;
			size = x._size;
			x._size = this->_size;
			this->_size = size;
			key_compare															key;
			key = this->_k_cmp;
			this->_k_cmp = x._k_cmp;
			x._k_cmp = key;

		}

		void clear(void) {

			this->_size = 0;
			this->_base.node_clear();

		}

		/* Observers */

		key_compare key_comp(void) const {

			return (this->_k_cmp);

		};
		value_compare value_comp() const {

			return (value_compare(this->_k_cmp));
		}

		/* operations */

		iterator find (const key_type& k) {

			node < Key, T > *tmp = this->_base.node_search(k);
			if (!tmp)
				return (this->end());
			return (iterator(tmp));

		};

		const_iterator find (const key_type& k) const {
			
			node < Key, T > *tmp;
			tmp = this->_base.node_search(k);
			if (!tmp)
				return (this->end());
			return (const_iterator(tmp));

		}

		size_type count (const key_type& k) const {

			if (this->_base.node_search(k))
				return (1);
			return (0);

		}

		iterator lower_bound (const key_type& k) {

			node < Key, T > *tmp = this->_base.node_search(k);
			if (tmp)
				return (iterator(tmp));
			iterator beg = this->begin();
			iterator end = this->end();
			while (beg != end)
			{
				if (!this->_k_cmp((*beg).first, k))
					return (beg);
				beg++;
			}
			return (iterator(this->_base.get_base()));

		}

		const_iterator lower_bound (const key_type& k) const {

			node < Key, T > *tmp = this->_base.node_search(k);
			if (tmp)
				return (iterator(tmp));
			iterator beg = this->begin();
			iterator end = this->end();
			while (beg != end)
			{
				if (!this->_k_cmp((*beg).first, k))
					return (beg);
				beg++;
			}
			return (const_iterator(this->_base.get_base()));

		};

		iterator upper_bound (const key_type& k) {

			iterator beg = this->begin();
			iterator end = this->end();
			while (beg != end)
			{
				if (this->_k_cmp(k, (*beg).first))
					break;
				beg++;
			}
			return (beg);

		}
		const_iterator upper_bound (const key_type& k) const {

			const_iterator beg = this->begin();
			const_iterator end = this->end();
			while (beg != end)
			{
				if (this->_k_cmp(k, (*beg).first))
					break;
				beg++;
			}
			return (beg);
		}

		std::pair<iterator,iterator>             equal_range (const key_type& k) {
			
			return (std::pair < iterator, iterator > (this->lower_bound(k), this->upper_bound(k)));
			
		}
		std::pair<const_iterator,const_iterator> equal_range (const key_type& k) const {

			return (std::pair < const_iterator, const_iterator > (this->lower_bound(k), this->upper_bound(k)));

		}
	};
	
	template < class Key, class T, class Compare, class Alloc >
	bool operator==(const ft::map<Key, T, Compare, Alloc > &lhs, const ft::map<Key, T, Compare, Alloc > &rhs)
	{

		if (lhs.size() != rhs.size())
			return (false);
		typename ft::map<Key, T, Compare, Alloc >::const_iterator beg1 = lhs.begin();
		typename ft::map<Key, T, Compare, Alloc >::const_iterator beg2 = rhs.begin();
		typename ft::map<Key, T, Compare, Alloc >::const_iterator end1 = lhs.end();
		typename ft::map<Key, T, Compare, Alloc >::const_iterator end2 = rhs.end();

		while (beg1 != end1 && beg2 != end2 && *beg1 == *beg2)
		{
			beg1++;
			beg2++;
		}

		if (beg1 == end1 && beg2 == end2)
			return (true);
		return (false);
	}

	template < class Key, class T, class Compare, class Alloc >
	bool operator!=(const ft::map<Key, T, Compare, Alloc > &lhs, const ft::map<Key, T, Compare, Alloc > &rhs)
	{

		return (!(lhs == rhs));
	}

	template < class Key, class T, class Compare, class Alloc >
	bool operator<(const ft::map<Key, T, Compare, Alloc > &lhs, const ft::map<Key, T, Compare, Alloc > &rhs)
	{

		if (lhs.size() < rhs.size())
			return (true);
		if (lhs.size() > rhs.size())
			return (false);
		typename ft::map<Key, T, Compare, Alloc >::const_iterator beg1 = lhs.begin();
		typename ft::map<Key, T, Compare, Alloc >::const_iterator beg2 = rhs.begin();
		typename ft::map<Key, T, Compare, Alloc >::const_iterator end1 = lhs.end();
		typename ft::map<Key, T, Compare, Alloc >::const_iterator end2 = rhs.end();

		while (beg1 != end1 && beg2 != end2 && *beg1 == *beg2)
		{
			beg1++;
			beg2++;
		}

		if ((beg1 == end1 && beg2 == end2) || beg2 == end2 || *beg1 >= *beg2)
			return (false);
		return (true);
	}

	template < class Key, class T, class Compare, class Alloc >
	bool operator<=(const ft::map<Key, T, Compare, Alloc > &lhs, const ft::map<Key, T, Compare, Alloc > &rhs)
	{

		return (lhs < rhs || lhs == rhs);
	}

	template < class Key, class T, class Compare, class Alloc >
	bool operator>(const ft::map<Key, T, Compare, Alloc > &lhs, const ft::map<Key, T, Compare, Alloc > &rhs)
	{

		if (lhs.size() > rhs.size())
			return (true);
		if (lhs.size() < rhs.size())
			return (false);
		typename ft::map<Key, T, Compare, Alloc >::const_iterator beg1 = lhs.begin();
		typename ft::map<Key, T, Compare, Alloc >::const_iterator beg2 = rhs.begin();
		typename ft::map<Key, T, Compare, Alloc >::const_iterator end1 = lhs.end();
		typename ft::map<Key, T, Compare, Alloc >::const_iterator end2 = rhs.end();

		while (beg1 != end1 && beg2 != end2 && *beg1 == *beg2)
		{
			beg1++;
			beg2++;
		}
		if ((beg1 == end1 && beg2 == end2) || beg1 == end1 || *beg1 <= *beg2)
			return (false);
		return (true);
	}

	template < class Key, class T, class Compare, class Alloc >
	bool operator>=(const ft::map<Key, T, Compare, Alloc > &lhs, const ft::map<Key, T, Compare, Alloc > &rhs)
	{

		return (lhs > rhs || lhs == rhs);
	}

	template < class Key, class T, class Compare, class Alloc >
	void swap(const ft::map<Key, T, Compare, Alloc > &lhs, const ft::map<Key, T, Compare, Alloc > &rhs)
	{
		lhs.swap(rhs);
	}
}
#endif