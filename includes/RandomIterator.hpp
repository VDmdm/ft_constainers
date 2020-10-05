/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RandomIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 13:59:10 by jalvaro           #+#    #+#             */
/*   Updated: 2020/09/19 11:26:59 by jalvaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOMITERATOR_HPP
#define RANDOMITERATOR_HPP

namespace ft
{

template <typename T>
class VectIter
{

  private:
	T *ptr;

  public:
	VectIter(void) : ptr(nullptr) {}
	VectIter(T *p) : ptr(p) {}
	VectIter(const VectIter &iter) { *this = iter; }
	VectIter &operator=(const VectIter &iter)
	{

		this->ptr = iter.ptr;
		return (*this);
	}
	~VectIter(void) {}

	VectIter &operator++()
	{

		++this->ptr;
		return (*this);
	}

	VectIter operator++(int)
	{

		VectIter ret = *this;
		this->operator++();
		return ret;
	}

	VectIter &operator--()
	{

		--this->ptr;
		return (*this);
	}

	VectIter operator--(int)
	{

		VectIter ret = *this;
		this->operator--();
		return ret;
	}
	bool operator==(VectIter const &other) { return (this->ptr == other.ptr); }
	bool operator!=(VectIter const &other) { return (this->ptr != other.ptr); }
	VectIter operator+(std::ptrdiff_t n)
	{

		VectIter temp = *this;
		return (temp += n);
	}

	VectIter &operator+=(std::ptrdiff_t n)
	{

		std::ptrdiff_t m = n;
		if (m >= 0)
			while (m--)
				this->operator++();
		else
			while (m++)
				this->operator--();
		return (*this);
	}

	VectIter operator-(long n)
	{

		VectIter temp = *this;
		return temp -= n;
	}

	VectIter &operator-=(std::ptrdiff_t n) { return (*this += -n); }
	std::ptrdiff_t operator-(VectIter &a) { return (this->ptr - a.ptr); }
	T &operator[](std::ptrdiff_t n) { return (*(*this + n)); }
	T &operator*(void) { return (*(this->ptr)); }
	T *operator->(void) { return (this->ptr); }
	T *getPtr(void) const { return this->ptr; }
};

template <typename T>
class ConstVectIter
{

  private:
	T *ptr;

  public:
	ConstVectIter(void) : ptr(nullptr) {}
	ConstVectIter(T *p) : ptr(p) {}
	ConstVectIter(const ConstVectIter &iter) { *this = iter; }
	ConstVectIter(const VectIter<T> &iter) { *this = iter; }
	ConstVectIter &operator=(const ConstVectIter &iter)
	{

		this->ptr = iter.ptr;
		return (*this);
	}
	ConstVectIter &operator=(const VectIter<T> &iter)
	{

		this->ptr = iter.getPtr();
		return (*this);
	}
	~ConstVectIter(void) {}

	ConstVectIter &operator++()
	{

		++this->ptr;
		return (*this);
	}

	ConstVectIter operator++(int)
	{

		ConstVectIter ret = *this;
		this->operator++();
		return ret;
	}

	ConstVectIter &operator--()
	{

		--this->ptr;
		return (*this);
	}

	ConstVectIter operator--(int)
	{

		ConstVectIter ret = *this;
		this->operator--();
		return ret;
	}
	bool operator==(ConstVectIter const &other) { return (this->ptr == other.ptr); }
	bool operator!=(ConstVectIter const &other) { return (this->ptr != other.ptr); }
	ConstVectIter operator+(std::ptrdiff_t n)
	{

		ConstVectIter temp = *this;
		return (temp += n);
	}

	ConstVectIter &operator+=(std::ptrdiff_t n)
	{

		std::ptrdiff_t m = n;
		if (m >= 0)
			while (m--)
				this->operator++();
		else
			while (m++)
				this->operator--();
		return (*this);
	}

	ConstVectIter operator-(long n)
	{

		ConstVectIter temp = *this;
		return temp -= n;
	}

	ConstVectIter &operator-=(std::ptrdiff_t n) { return (*this += -n); }
	std::ptrdiff_t operator-(ConstVectIter &a) { return (this->ptr - a.ptr); }
	T &operator[](std::ptrdiff_t n) { return (*(*this + n)); }
	const T &operator*(void) { return (*(this->ptr)); }
	T *operator->(void) { return (this->ptr); }
};

template <typename T>
class ReverseVectIter
{

  private:
	T *ptr;

  public:
	ReverseVectIter(void) : ptr(nullptr) {}
	ReverseVectIter(T *p) : ptr(p) {}
	ReverseVectIter(const ReverseVectIter &iter) { *this = iter; }
	ReverseVectIter &operator=(const ReverseVectIter &iter)
	{

		this->ptr = iter.ptr;
		return (*this);
	}
	~ReverseVectIter(void) {}

	ReverseVectIter &operator++()
	{

		--this->ptr;
		return (*this);
	}

	ReverseVectIter operator++(int)
	{

		ReverseVectIter ret = *this;
		this->operator++();
		return ret;
	}

	ReverseVectIter &operator--()
	{

		++this->ptr;
		return (*this);
	}

	ReverseVectIter operator--(int)
	{

		ReverseVectIter ret = *this;
		this->operator--();
		return ret;
	}
	bool operator==(ReverseVectIter const &other) { return (this->ptr == other.ptr); }
	bool operator!=(ReverseVectIter const &other) { return (this->ptr != other.ptr); }
	ReverseVectIter operator+(std::ptrdiff_t n)
	{

		ReverseVectIter temp = *this;
		return (temp -= n);
	}

	ReverseVectIter &operator+=(std::ptrdiff_t n)
	{

		std::ptrdiff_t m = n;
		if (m >= 0)
			while (m--)
				this->operator++();
		else
			while (m++)
				this->operator--();
		return (*this);
	}

	ReverseVectIter operator-(long n)
	{

		ReverseVectIter temp = *this;
		return temp += n;
	}

	ReverseVectIter &operator-=(std::ptrdiff_t n) { return (*this -= -n); }
	std::ptrdiff_t operator-(ReverseVectIter &a) { return (this->ptr - a.ptr); }
	T &operator[](std::ptrdiff_t n) { return (*(*this - n)); }
	T &operator*(void) { return (*(this->ptr)); }
	T *operator->(void) { return (this->ptr); }
	T *getPtr(void) const { return this->ptr; }
};

template <typename T>
class ConstReverseVectIter
{

  private:
	T *ptr;

  public:
	ConstReverseVectIter(void) : ptr(nullptr) {}
	ConstReverseVectIter(T *p) : ptr(p) {}
	ConstReverseVectIter(const ConstReverseVectIter &iter) { *this = iter; }
	ConstReverseVectIter(const ReverseVectIter<T> &iter) { *this = iter; }
	ConstReverseVectIter &operator=(const ConstReverseVectIter &iter)
	{

		this->ptr = iter.ptr;
		return (*this);
	}
	ConstReverseVectIter &operator=(const ReverseVectIter<T> &iter)
	{

		this->ptr = iter.getPtr();
		return (*this);
	}
	~ConstReverseVectIter(void) {}

	ConstReverseVectIter &operator++()
	{

		--this->ptr;
		return (*this);
	}

	ConstReverseVectIter operator++(int)
	{

		ConstReverseVectIter ret = *this;
		this->operator++();
		return ret;
	}

	ConstReverseVectIter &operator--()
	{

		++this->ptr;
		return (*this);
	}

	ConstReverseVectIter operator--(int)
	{

		ConstReverseVectIter ret = *this;
		this->operator--();
		return ret;
	}
	bool operator==(ConstReverseVectIter const &other) { return (this->ptr == other.ptr); }
	bool operator!=(ConstReverseVectIter const &other) { return (this->ptr != other.ptr); }
	ConstReverseVectIter operator+(std::ptrdiff_t n)
	{

		ConstReverseVectIter temp = *this;
		return (temp -= n);
	}

	ConstReverseVectIter &operator+=(std::ptrdiff_t n)
	{

		std::ptrdiff_t m = n;
		if (m >= 0)
			while (m--)
				this->operator++();
		else
			while (m++)
				this->operator--();
		return (*this);
	}

	ConstReverseVectIter operator-(long n)
	{

		ConstReverseVectIter temp = *this;
		return temp += n;
	}

	ConstReverseVectIter &operator-=(std::ptrdiff_t n) { return (*this -= -n); }
	std::ptrdiff_t operator-(ConstReverseVectIter &a) { return (this->ptr - a.ptr); }
	T &operator[](std::ptrdiff_t n) { return (*(*this - n)); }
	const T &operator*(void) { return (*(this->ptr)); }
	T *operator->(void) { return (this->ptr); }
};
};

#endif