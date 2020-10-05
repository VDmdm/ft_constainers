/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapIterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 12:11:00 by jalvaro           #+#    #+#             */
/*   Updated: 2020/09/19 13:52:33 by jalvaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPITERATOR_HPP
#define MAPITERATOR_HPP

#include "Node.hpp"

namespace ft {
	
	template < class Key, class T, class Compare >
	class MapIter {

	private:

		_Node < Key, T, Compare >    base;
        node < Key, T >              *ptr;

	public:
		MapIter(void) : ptr(nullptr) {}
		MapIter(node < Key, T > *p) : ptr(p) {}
		MapIter(const MapIter &iter)
		{
			*this = iter;
		}

		MapIter &operator=(const MapIter &iter)
		{

			this->ptr = iter.ptr;
			return (*this);
		}

		~MapIter(void) {}

		MapIter &operator++()
		{
            this->ptr = base.node_increment(this->ptr);
			return (*this);
		}

		MapIter operator++(int)
		{

			MapIter ret = *this;
			this->operator++();
			return (ret);
		}

		MapIter &operator--()
		{

			this->ptr = base.node_decrement(this->ptr);
			return (*this);
            
		}

		MapIter operator--(int)
		{

			MapIter ret = *this;
			this->operator--();
			return (ret);
		}

		bool operator==(const MapIter &other)
		{
			return (this->ptr == other.ptr);
		}

		bool operator!=(const MapIter &other)
		{
			return (this->ptr != other.ptr);
		}

		bool operator!=(const MapIter &other) const
		{
			return (this->ptr != other.ptr);
		}

		std::pair <const Key, T > &operator*(void)
		{
			return (*(this->ptr->value));
		}

		std::pair <const Key, T > *operator->(void)
		{
			return (this->ptr->value);
		}

		node < Key, T > *getNode(void) const
		{
			return this->ptr;
		}
	};

	template < class Key, class T, class Compare >
	class ConstMapIter {

	private:

		_Node < Key, T, Compare >    base;
        node < Key, T >              *ptr;

	public:
		ConstMapIter(void) : ptr(nullptr) {}
		ConstMapIter(node < Key, T > *p) : ptr(p) {}
		ConstMapIter(const ConstMapIter &iter)
		{
			*this = iter;
		}

		ConstMapIter(const MapIter< Key, T, Compare> &iter)
		{
			*this = iter;
		}

		ConstMapIter &operator=(const ConstMapIter &iter)
		{

			this->ptr = iter.ptr;
			return (*this);
		}

		ConstMapIter &operator=(const MapIter< Key, T, Compare> &iter)
		{

			this->ptr = iter.getNode();
			return (*this);
		}

		~ConstMapIter(void) {}

		ConstMapIter &operator++()
		{
            this->ptr = base.node_increment(this->ptr);
			return (*this);
		}

		ConstMapIter operator++(int)
		{

			ConstMapIter ret = *this;
			this->operator++();
			return (ret);
		}

		ConstMapIter &operator--()
		{

			this->ptr = base.node_decrement(this->ptr);
			return (*this);
            
		}

		ConstMapIter operator--(int)
		{

			ConstMapIter ret = *this;
			this->operator--();
			return (ret);
		}

		bool operator==(const ConstMapIter &other)
		{
			return (this->ptr == other.ptr);
		}

		bool operator!=(const ConstMapIter &other)
		{
			return (this->ptr != other.ptr);
		}

		bool operator!=(const ConstMapIter &other) const
		{
			return (this->ptr != other.ptr);
		}

		const std::pair <const Key, T > &operator*(void)
		{
			return (*(this->ptr->value));
		}

		std::pair <const Key, T > *operator->(void)
		{
			return (this->ptr->value);
		}
	};

	template < class Key, class T, class Compare >
	class MapRevIter {

	private:

		_Node< Key, T, Compare >    base;
        node < Key, T >             *ptr;

	public:
		MapRevIter(node < Key, T > *p) : ptr(p){};

		MapRevIter(const MapRevIter &iter)
		{
			*this = iter;
		}

		MapRevIter &operator=(const MapRevIter &iter)
		{

			this->ptr = iter.ptr;
			return (*this);
		}

		~MapRevIter(void) {};


		MapRevIter &operator++()
		{
            this->ptr = base.node_decrement(this->ptr);
			return (*this);
		}

		MapRevIter operator++(int)
		{

			MapRevIter ret = *this;
			this->operator++();
			return ret;
		}

		MapRevIter &operator--()
		{

			this->ptr = base.node_increment(this->ptr);
			return (*this);
		}

		MapRevIter operator--(int)
		{

			MapRevIter ret = *this;
			this->operator--();
			return ret;
		}

		bool operator==(const MapRevIter &other)
		{
			return (this->ptr == other.ptr);
		}
		bool operator!=(const MapRevIter &other)
		{
			return (this->ptr != other.ptr);
		}
		std::pair <const Key, T > &operator*()
		{
			return (*this->ptr->value);
		}
		std::pair <const Key, T > *operator->()
		{
			return (this->ptr->value);
		}

		node < Key, T > *getNode(void) const
		{
			return this->ptr;
		}
	};

	template < class Key, class T, class Compare >
	class ConstMapRevIter: public std::iterator<std::bidirectional_iterator_tag, T> {

	private:

		_Node< Key, T, Compare >    base;
        node < Key, T >             *ptr;

	public:
		ConstMapRevIter(node < Key, T > *p) : ptr(p){};

		ConstMapRevIter(const ConstMapRevIter &iter)
		{
			*this = iter;
		}

		ConstMapRevIter(const MapRevIter< Key, T, Compare> &iter)
		{
			*this = iter;
		}

		ConstMapRevIter &operator=(const ConstMapRevIter &iter)
		{
			this->ptr = iter.ptr;
			return (*this);
		}

		ConstMapRevIter &operator=(const MapRevIter< Key, T, Compare> &iter)
		{
			this->ptr = iter.getNode();
			return (*this);
		}

		~ConstMapRevIter(void) {};

		ConstMapRevIter &operator++()
		{
            this->ptr = base.node_decrement(this->ptr);
			return (*this);
		}

		ConstMapRevIter operator++(int)
		{

			ConstMapRevIter ret = *this;
			this->operator++();
			return ret;
		}

		ConstMapRevIter &operator--()
		{

			this->ptr = base.node_increment(this->ptr);
			return (*this);
		}

		ConstMapRevIter operator--(int)
		{

			ConstMapRevIter ret = *this;
			this->operator--();
			return ret;
		}

		bool operator==(const ConstMapRevIter &other)
		{
			return (this->ptr == other.ptr);
		}
		bool operator!=(const ConstMapRevIter &other)
		{
			return (this->ptr != other.ptr);
		}
		const std::pair <const Key, T > &operator*()
		{
			return (*this->ptr->value);
		}
		std::pair <const Key, T > *operator->()
		{
			return (this->ptr->value);
		}
	};
}

#endif