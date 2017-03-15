#ifndef SINGLELIST_H
#define SINGLELIST_H
#include <iosfwd>
#include <cstddef>
#include <initializer_list>

template<typename T>
class __single_list_node{
public:
	typedef __single_list_node node;
	T data;
	node *next;
};

template<typename T>
class __single_list_iterator{
public:
	typedef __single_list_iterator<T> iterator;

	typedef T value_type;
	typedef value_type* pointer;
	typedef value_type& reference;
	typedef __single_list_node<T>* link_type;

	link_type node;

	// default constructor
	__single_list_iterator() : node{ nullptr }{}

	// constructor
	explicit __single_list_iterator(link_type node) : node{ node }{}

	// copy constructor
	__single_list_iteraor(const iterator& iter2) : node{ iter2.node }{}

	value_type& operator*(){
		return node->data;
	}

	iterator& operator++(){
		node = node->next;
		return *this;
	}

	iterator operator++(int){
		iterator temp = *this;
		//node = node->next;
		++ *this;
		return temp;
	}

	bool operator==(const iterator& iter2){
		return node == iter2.node;
	}

	bool operator!=(const iterator& iter2){
		return !(*this == iter2);
	}
};

template<typename T>
class SingleList{
public:
	typedef SingleList<T> my_type;
	typedef T value_type;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef size_t size_type;
	typedef __single_list_node<T>* link_type;

	// defalut constructor. an empty list
	SingleList(){
		empty_init();
	}

	// construct a list with size n and defualt value
	explicit SingleList(size_type n){
		empty_init();
		init_n(n, T());
	}
	// construct a list with size n and value elem.
	SingleList(size_type n, const T& elem){
		empty_init();
		init_n(n, T(elem));
	}

	// construct a list using initializer list
	explicit SingleList(std::initializer_list<T> init_list)
	{
		empty_init();
		link_type p = head;
		for (auto& elem : init_list){
			link_type temp = new __single_list_node < T > ;
			temp->data = elem;
			temp->next = nullptr;
			p->next = temp;
			p = p->next;
		}
	}

	// traversal
	friend std::ostream& operator<<(std::ostream& os, const my_type& l){
		link_type p = l.head->next;
		while (p != nullptr){
			os << p->data << " ";
			p = p->next;
		}
		return os << endl;
	}

protected:
	link_type head;       // head node in the list

	// reuse code when define constructor
	void empty_init(){
		head = new __single_list_node<T>;
		head->next = nullptr;
	}

	void init_n(size_type n, const T& value){
		link_type p = head;
		while (n-- > 0){
			link_type temp = new __single_list_node<T>;
			temp->data = value;
			temp->next = nullptr;
			p->next = temp;
			p = p->next;
		}
	}
};

#endif