/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 20:53:01 by jalvaro           #+#    #+#             */
/*   Updated: 2020/09/26 18:36:24 by jalvaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>

template <class Key_type, class Value_type>
struct node
{
	node* parent;
	node* left;
	node* right;
	bool end;
	std::pair< const Key_type, Value_type > *value;

};

template < class Key, class T, class Compare,
			class Alloc = std::allocator<std::pair<const Key,T> > >

class _Node {

	public:

		typedef node< Key, T >							_self;
		typedef Key										key_type;
		typedef T										mapped_type;
		typedef Alloc									allocator_type;
		typedef std::pair< const key_type, mapped_type>	value_type;
		typedef Compare									value_compare;
		typedef value_type&								reference;
		typedef const value_type&						const_reference;
		typedef _self*									pointer;
		typedef const _self*							const_pointer;
		typedef std::size_t								size_type;

	private:

		pointer			_base;
		pointer			_rend;
		pointer			_end;
		allocator_type	_alloc;
		value_compare	_cmp;

	public:

		/* coplien */

		_Node (void) {

			this->_end = this->node_end(nullptr);
			this->_rend = this->node_end(nullptr);
			this->_base = nullptr;

		}

		_Node (const allocator_type &alloc) {

			this->_alloc = alloc;
			this->_end = this->node_end(nullptr);
			this->_rend = this->node_end(nullptr);
			this->_base = nullptr;

		}

		_Node (value_type* val) {

			this->_base = this->node_new(val);
			this->_end = this->node_end(nullptr);
			this->_rend = this->node_end(nullptr);
			this->base->left = this->_end;
			this->base->right = this->_end;

		}

		_Node &operator=(const _Node &x) {

			this->_base = x._base;
			this->_alloc = x._alloc;
			this->_cmp = x._cmp;
			if (this->_base)
			{
				node_set_rend();
				node_set_end();
			}
			return (*this);
		}
		
		~_Node(void) {
		
			this->node_clear();
			this->_alloc.deallocate(this->_end->value, 1);
			delete this->_end;
			this->_alloc.deallocate(this->_rend->value, 1);
			delete this->_rend;

		}

		pointer node_new(const_reference val) {

			pointer tmp = new _self;
			tmp->value = this->_alloc.allocate(1);
			this->_alloc.construct(tmp->value, val);
			tmp->parent = nullptr;
			tmp->left = nullptr;
			tmp->right = nullptr;
			tmp->end = false;
			return (tmp);

		}

		pointer node_end(pointer par) {

			pointer tmp = new _self;
			tmp->value = this->_alloc.allocate(1);
			tmp->parent = par;
			tmp->left = nullptr;
			tmp->right = nullptr;
			tmp->end = true;
			return tmp;

		}

		void	node_set_rend(void)
		{
			this->node_min()->left = this->_rend;
			this->_rend->parent = this->node_min();
		}

		void	node_set_end(void)
		{
			this->node_max()->right = this->_end;
			this->_end->parent = this->node_max();
		}

		pointer node_add(const_reference value, pointer root = nullptr)
		{
			if (this->node_search(value))
				return nullptr;
			pointer tmp = this->node_new(value);
			if (this->_base == 0 || this->_base->end)
			{
				this->_base = tmp;
				this->_base->left = this->_rend;
				this->_rend->parent = this->_base;
				this->_base->right = this->_end;
				this->_end->parent = this->_base;
				return (tmp);
			}
			if (!root)
				root = this->_base;
			while (root != nullptr && !root->end)
			{
				if (!this->_cmp(tmp->value->first, root->value->first))
				{
					if (root->right != nullptr && !root->right->end)
						root = root->right;
					else
					{
						tmp->parent = root;
						root->right = tmp;
						break;
					}
				}
				else if (this->_cmp(tmp->value->first, root->value->first))
				{
					if (root->left != nullptr && !root->left->end)
						root = root->left;
					else
					{
						tmp->parent = root;
						root->left = tmp;
						break;
					}
				}
			}
			node_set_rend();
			node_set_end();
			return (tmp);

		}

		pointer node_min(pointer root = nullptr, bool fst = true) const {

			if (fst && !root)
				root = this->_base;
			if (root->left == nullptr || root->left->end)
				return root;
			return (node_min(root->left, false));

		}

		pointer node_max(pointer root = nullptr, bool fst = true) const {

			if (fst && !root)
				root = this->_base;
			if (root->right == nullptr || root->right->end)
				return root;
			return (node_max(root->right, false));

		}

		pointer node_search(const_reference val, pointer root = nullptr, bool fst = false) {

			if (!fst)
				root = this->_base;
			if (root == nullptr || root->end)
				return (nullptr);
			if (val.first == root->value->first)
				return (root);
			if (this->_cmp(val.first, root->value->first))
				return (node_search(val, root->left, true));
			else
				return (node_search(val, root->right, true));

		}

		pointer node_search(key_type key, pointer root = nullptr, bool fst = false) const {

			if (!fst)
				root = this->_base;
			if (root == nullptr || root->end)
				return (nullptr);
			if (key == root->value->first)
				return (root);
			if (this->_cmp(key, root->value->first))
				return (node_search(key, root->left, true));
			else
				return (node_search(key, root->right, true));

		}

		pointer node_delete(pointer root, const key_type key) {

			pointer tmp;

			if (root == nullptr || root->end)
				return root;
			if (this->_cmp(key, root->value->first))
				root->left = node_delete(root->left, key);
			else if (!this->_cmp(key, root->value->first) && key != root->value->first)
				root->right = node_delete(root->right, key);
			else if (root->left != nullptr && !root->left->end && root->right != nullptr && !root->right->end)
			{
				this->_alloc.destroy(root->value);
				this->_alloc.deallocate(root->value, 1);
				root->value = this->_alloc.allocate(1);
				this->_alloc.construct(root->value, *this->node_min(root->right)->value);
				root->right = node_delete(root->right, root->value->first);
			}
			else if (root->left != nullptr && !root->left->end)
			{
				if (this->_base == root)
					this->_base = root->left;
				tmp = root->left;
				root->left->parent = root->parent;
				this->_alloc.destroy(root->value);
				this->_alloc.deallocate(root->value, 1);
				delete root;
				root = tmp;
			}
			else if (root->right != nullptr && !root->right->end)
			{
				if (this->_base == root)
					this->_base = root->right;
				tmp = root->right;
				root->right->parent = root->parent;
				this->_alloc.destroy(root->value);
				this->_alloc.deallocate(root->value, 1);
				delete root;
				root = tmp;
			}
			else
			{
				if (this->_base == root)
					this->_base = nullptr;
				if (root->left)
					root->left->parent = root->parent;
				if (root->right)
					root->right->parent = root->parent;
				this->_alloc.destroy(root->value);
				this->_alloc.deallocate(root->value, 1);
				delete root;
				root = nullptr;
			}
			return (root);
		}

		pointer node_increment(pointer root) {

			Key k;
			if (root && root->end)
				return root->parent;
			if (!root || root->end)
				return root;
			if (root->right)
			{
				root = root->right;
				while (root->left)
					root = root->left;
			}
			else if (root->parent && root == root->parent->left)
				root = root->parent;
			else if (!root->right)
			{
				k = root->value->first;
				while (root->parent)
				{
					root = root->parent;
					if (_cmp(k, root->value->first))
						break;
				}
				if (!root->parent && !_cmp(k, root->value->first))
					root = root->right;
			}
			else
				root = root->right;
			return (root);

		}

		pointer node_decrement(pointer root) {

			Key k;
			if (root && root->end)
				return root->parent;
			if (!root || root->end)
				return root;
			if (root->left)
			{
				root = root->left;
				while (root->right)
					root = root->right;
			}
			else if (root->parent && root == root->parent->right)
				root = root->parent;
			else if (!root->left)
			{
				k = root->value->first;
				while (root->parent)
				{
					root = root->parent;
					if (!_cmp(k, root->value->first))
						break;
				}
				if (!root->parent && _cmp(k, root->value->first))
					root = root->left;
			}
			else
				root = root->left;
			return (root);

		}

		pointer get_base(void) const { return this->_base; }

		void	set_base(pointer x) {

			this->_base = x;
			node_set_rend();
			node_set_end();

		}

		pointer get_rend(void) const { return this->_rend; }

		pointer get_end(void) const { return this->_end; }

		void node_print_inorder(pointer x) {

			if (x != nullptr && !x->end)
			{
				node_print_inorder(x->left);
				std::cout << x->value->first << " ";
				node_print_inorder(x->right);
			}
		}

		void node_clear (pointer root = nullptr, bool fst = true) {

			if (fst)
			{
				root = this->_base;
				this->_base = nullptr;
			}
			if (root && !root->end) {
				node_clear(root->left, false);
				node_clear(root->right, false);
				this->_alloc.destroy(root->value);
				this->_alloc.deallocate(root->value, 1);
				delete root;
			}
		}

		void node_destroy(void) {

		}

};

#endif