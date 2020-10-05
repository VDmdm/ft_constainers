/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListIterators.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 12:35:15 by jalvaro           #+#    #+#             */
/*   Updated: 2020/09/26 17:43:13 by jalvaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTITERATOR_HPP
#define LISTITERATOR_HPP

template <typename T>
struct dll
{
	T *data;
	struct dll *next;
	struct dll *prev;
};

namespace ft {
	
	template < class T >
	class ListIter {

		private:

			dll<T>*	ptr;

		  public:
			explicit ListIter(void) : ptr(nullptr) {}
			explicit ListIter(dll<T> *p) : ptr(p) {}
			ListIter(const ListIter &iter)
			{

				*this = iter;
			}

			ListIter &operator=(const ListIter &iter)
			{

				this->ptr = iter.ptr;
				return (*this);
			}

			~ListIter(void) {}

			ListIter &operator++()
			{

				this->ptr = this->ptr->next;
				return (*this);
			}

			ListIter operator++(int)
			{

				ListIter ret = *this;
				this->operator++();
				return ret;
			}

			ListIter &operator--()
			{

				this->ptr = this->ptr->prev;
				return (*this);
			}

			ListIter operator--(int)
			{

				ListIter ret = *this;
				this->operator--();
				return ret;
			}

			bool operator==(ListIter const &other)
			{
				return (this->ptr == other.ptr);
			}

			bool operator!=(ListIter const &other)
			{
				return (this->ptr != other.ptr);
			}

			T &operator*(void)
			{
				return (*(this->ptr->data));
			}

			const T &operator*(int)
			{
				return (*(this->ptr->data));
			}

			T *operator->(void)
			{
				return (this->ptr->data);
			}

			dll<T> *getNode() const
			{
				return (this->ptr);
			}
	};

	template < class T >
	class ConstListIter
	{

	  private:
		dll<T> *ptr;

	  public:
		explicit ConstListIter(void) : ptr(nullptr) {}
		explicit ConstListIter(dll<T> *p) : ptr(p) {}
		ConstListIter(const ConstListIter &iter)
		{

			*this = iter;
		}

		ConstListIter(const ListIter<T> &iter)
		{

			*this = iter;
		}

		ConstListIter &operator=(const ConstListIter &iter)
		{

			this->ptr = iter.ptr;
			return (*this);
		}

		ConstListIter &operator=(const ListIter<T> &iter)
		{

			this->ptr = iter.getNode();
			return (*this);
		}

		~ConstListIter(void) {}

		ConstListIter &operator++()
		{

			this->ptr = this->ptr->next;
			return (*this);
		}

		ConstListIter operator++(int)
		{

			ConstListIter ret = *this;
			this->operator++();
			return ret;
		}

		ConstListIter &operator--()
		{

			this->ptr = this->ptr->prev;
			return (*this);
		}

		ConstListIter operator--(int)
		{

			ConstListIter ret = *this;
			this->operator--();
			return ret;
		}

		bool operator==(ConstListIter const &other)
		{
			return (this->ptr == other.ptr);
		}

		bool operator!=(ConstListIter const &other)
		{
			return (this->ptr != other.ptr);
		}

		const T &operator*(void)
		{
			return (*(this->ptr->data));
		}
	};

	template < class T >
	class revListIter
	{

	  private:
		dll<T> *ptr;

	  public:
		explicit revListIter(void) : ptr(nullptr) {}

		explicit revListIter(dll<T> *p) : ptr(p){};

		revListIter(const revListIter &iter)
		{

			*this = iter;
		}

		revListIter &operator=(const revListIter &iter)
		{
			this->ptr = iter.ptr;
			return (*this);
		}

		revListIter &operator++()
		{

			this->ptr = this->ptr->prev;
			return (*this);
		}

		revListIter operator++(int)
		{

			revListIter ret = *this;
			this->operator++();
			return ret;
		}

		revListIter &operator--()
		{

			this->ptr = this->ptr->next;
			return (*this);
		}

		revListIter operator--(int)
		{

			revListIter ret = *this;
			this->operator--();
			return ret;
		}

		bool operator==(revListIter const &other)
		{
			return (this->ptr == other.ptr);
		}
		bool operator!=(revListIter const &other)
		{
			return (this->ptr != other.ptr);
		}
		T &operator*()
		{
			return (*this->ptr->data);
		}
		T *operator->()
		{
			return (this->ptr->data);
		}

		dll<T> *getNode() const
		{
			return (this->ptr);
		}
	};

	template < class T >
	class ConstRevListIter
	{

	  private:
		dll<T> *ptr;

	  public:
		explicit ConstRevListIter(void) : ptr(nullptr) {}
		explicit ConstRevListIter(dll<T> *p) : ptr(p){};
		ConstRevListIter(const ConstRevListIter &iter)
		{

			*this = iter;
		}

		ConstRevListIter(const revListIter<T> &iter)
		{

			*this = iter;
		}

		ConstRevListIter &operator=(const ConstRevListIter &iter)
		{

			this->ptr = iter.ptr;
			return (*this);
		}

		ConstRevListIter &operator=(const revListIter<T> &iter)
		{

			this->ptr = iter.getNode();
			return (*this);
		}

		~ConstRevListIter(void) {}

		ConstRevListIter &operator++()
		{

			this->ptr = this->ptr->prev;
			return (*this);
		}

		ConstRevListIter operator++(int)
		{

			ConstRevListIter ret = *this;
			this->operator++();
			return ret;
		}

		ConstRevListIter &operator--()
		{

			this->ptr = this->ptr->next;
			return (*this);
		}

		ConstRevListIter operator--(int)
		{

			ConstRevListIter ret = *this;
			this->operator--();
			return ret;
		}

		bool operator==(ConstRevListIter const &other)
		{
			return (this->ptr == other.ptr);
		}
		bool operator!=(ConstRevListIter const &other)
		{
			return (this->ptr != other.ptr);
		}
		const T &operator*()
		{
			return (*this->ptr->data);
		}
		T *operator->()
		{
			return (this->ptr->data);
		}
	};
}

#endif