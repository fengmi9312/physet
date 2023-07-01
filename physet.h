#pragma once
template<class T>
class physet
{
public:
	class node														// define the node class
	{
	private:														//	only the physet<T> can read/write the data in class physet<T>::node
		friend class physet<T>;
		friend class physet<T>::iterator;
		friend class physet<T>::const_iterator;
		T obj;														//	the pointer pointing the object
		node* father;												//	the pointer of father
		node* lchild;												//	the pointer of left child
		node* rchild;												//	the pointer of right child
		node* prev;													//	the pointer of previous node
		node* next;													//	the pointer of next node
		int ischild();
		node* fatherofnext();
	public:
		node(T _obj);											//	constructor of class physet<T>::node
		~node();													//	destructor of class physet<T>::node
	};

	class iterator													//	define the iterator
	{
	private:
		friend class physet<T>::const_iterator;
		node* node_ptr;												//	the pointer of the node
	public:
		iterator(node* _node_ptr);
		T& operator*();
	};

	class const_iterator													//	define the iterator
	{
	private:
		node* node_ptr;												//	the pointer of the node
	public:
		const_iterator(node* _node_ptr);
		const_iterator(iterator const& it);
		T const& operator*();
		const_iterator& operator++();
		const_iterator operator++(int);
		const_iterator& operator--();
		const_iterator operator--(int);
	};
private:
	node* begin_node;												//	the pointer of the beginning node
	node* end_node;													//	the pointer of the ending node
	size_t node_amount;													//	the size of physet container
public:
	physet();														//	constructor of class physet
	~physet();														//	destructor of class physet
	iterator begin() const;
	iterator end() const;
	void add(T const&  val);
	bool remove(iterator const& it);
	bool empty() const noexcept;
	size_t size() const;
	T front();
	T back();
};

/*******************************************************************/
template<class T>
physet<T>::node::node(T _obj) : obj(_obj), father(nullptr), lchild(nullptr), rchild(nullptr), prev(nullptr), next(nullptr) {}

template<class T>
int physet<T>::node::ischild()
{
	if (father == nullptr) return 0;
	else if (father->lchild == this) return 1;
	else return 2;
}

template<class T>
typename physet<T>::node* physet<T>::node::fatherofnext()
{
	node* nodeptr = this;
	node* la = nullptr;
	int ic = nodeptr->ischild();
	if (ic == 0) return this;
	else if (ic == 1) return nodeptr->father;
	else
	{
		while (1)
		{
			if (nodeptr->ischild() == 1) 
			{
				la = nodeptr->father->rchild;
				break;
			}
			else if (nodeptr->father->father == nullptr)
			{
				la = nodeptr->father->lchild;
				break;
			}
			nodeptr = nodeptr->father;
		}
		while (la->lchild != nullptr) la = la->lchild;
		return la;
	}
}

/*******************************************************************/
template<class T>
physet<T>::iterator::iterator(physet<T>::node* _node_ptr) : node_ptr(_node_ptr) {}

template<class T>
T& physet<T>::iterator::operator*()
{
	return node_ptr->obj;
}

/*******************************************************************/
template<class T>
physet<T>::const_iterator::const_iterator(physet<T>::node* _node_ptr) : node_ptr(_node_ptr) {}

template<class T>
physet<T>::const_iterator::const_iterator(physet<T>::iterator const& it)
{
	node_ptr = it.node_ptr;
}

template<class T>
T const& physet<T>::const_iterator::operator*()
{
	return node_ptr->obj;
}

template<class T>
typename physet<T>::const_iterator& physet<T>::const_iterator::operator++()
{
	node_ptr = node_ptr->next;
	return *this;
}



/*******************************************************************/
template<class T>
physet<T>::physet() : begin_node(nullptr), end_node(nullptr), node_amount(0) {}

template<class T>
physet<T>::~physet()												//	delete all the nodes before deleting the container
{
	node* node_ptr{ begin_node };
	node* node_ptr_next{ nullptr };
	while (node_ptr)
	{
		node_ptr_next = node_ptr->next;
		delete node_ptr;
		node_ptr = node_ptr_next;
	}
}

template<class T>
typename physet<T>::iterator physet<T>::begin() const
{
	return begin_node;
}

template<class T>
typename physet<T>::iterator physet<T>::end() const
{
	return end_node;
}

template<class T>
void physet<T>::add(T const& val)
{
	node* node_a = new node{ val };
	if (end_node == nullptr)
	{
		end_node = node_a;
		begin_node = node_a;
		node_a->prev = nullptr;
		node_a->next = nullptr;
		node_a->father = nullptr;
		node_a->lchild = nullptr;
		node_a->rchild = nullptr;
	}
	else
	{
		node_a->prev = end_node;
		end_node->next = node_a;
		end_node = node_a;
		node_a->father = node_a->prev->fatherofnext();
		if (node_a->father->lchild == nullptr) node_a->father->lchild = node_a;
		else node_a->father->rchild = node_a;
		node_a->next = nullptr;
		node_a->lchild = nullptr;
		node_a->rchild = nullptr;
	}
	node_amount++;
}

template<class T>
bool physet<T>::remove(physet<T>::iterator const& it)
{
	return true;
}
