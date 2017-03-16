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
class __single_list_const_iterator{
public:
	typedef __single_list_const_iterator<T> const_iterator;
	typedef T value_type;
	typedef value_type* pointer;
	typedef value_type& reference;
	typedef __single_list_node<T>* link_type;

	link_type node;

	// defaul constructor
	__single_list_const_iterator() : node{ nullptr }{}

	// constructor
	explicit __single_list_const_iterator(link_type node) : node{ node }{}

	// copy constructor
	__single_list_const_iterator(const const_iterator& iter2) : node{ iter2.node }{}

	const value_type& operator*() const{
		return node->data;
	}

	const const_iterator& operator++(){
		node = node->next;
		return *this;
	}

	const const_iterator& operator++(int){
		const_iterator temp = *this;
		++(*this);
		return temp;
	}

	bool operator==(const const_iterator& iter2) const{
		return node == iter2.node;
	}

	bool operator!=(const const_iterator& iter2) const{
		return !(*this == iter2);
	}
};
template<typename T>
class __single_list_iterator : public __single_list_const_iterator<T>{
public:
	typedef __single_list_iterator<T> iterator;
	typedef T value_type;
	typedef value_type* pointer;
	typedef value_type& reference;
	typedef __single_list_node<T>* link_type;

	// default constructor
	__single_list_iterator() : node{ nullptr }{}

	// constructor
	explicit __single_list_iterator(link_type node) : __single_list_const_iterator<T>(node){}

	// copy constructor
	__single_list_iterator(const iterator& iter2) : __single_list_const_iterator<T>(iter2.node){}

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

	typedef __single_list_const_iterator<T> const_iterator;
	typedef __single_list_iterator<T> iterator;

	// defalut constructor. an empty list
	SingleList(){
		empty_init();
	}

	// construct a list with size n and defualt value
	explicit SingleList(size_type n){
		empty_init();
		init_n(before_begin(), n, T());
	}
	// construct a list with size n and value elem.
	SingleList(size_type n, const T& elem){
		empty_init();
		init_n(before_begin(), n, T(elem));
	}

	// construct a list using initializer list
	explicit SingleList(std::initializer_list<T> init_list)
	{
		init_range(init_list.begin(), init_list.end());
	}
	
	// constructor using range [first, last)
	template<typename _FwdIt>
	SingleList(_FwdIt first, _FwdIt last)
	{
		init_range(first, last);
	}

	// copy constructor: deep copy
	SingleList(const SingleList& sl){
		empty_init();
		link_type p1 = head;
		link_type p2 = sl.head->next;
		while (p2 != nullptr){
			link_type temp = new __single_list_node<T>;
			temp->data = p2->data;
			temp->next = nullptr;
			p1->next = temp;
			p1 = p1->next;
			p2 = p2->next;
		}
	}

	//move constructor
	SingleList(SingleList&& rsl) : head(rsl.head){
		rsl.head = nullptr;
	}

	// copy assignment
	SingleList& operator=(const SingleList& sl2)
	{
		return assign(sl2);
	}

	//move assignment
	SingleList& operator=(SingleList&& rsl)
	{
		return assign(std::forward<SingleList>(rsl));
	}

	SingleList& assign(const SingleList& sl2)
	{
		if (this == &sl2) return *this;
		link_type p1 = head;
		link_type p2 = sl2.head;
		// just copy data
		while (p1->next != nullptr && p2->next != nullptr){
			p1->next->data = p2->next->data;
			p1 = p1->next;
			p2 = p2->next;
		}
		// if sl1 is longer than sl2, delete left
		if (p1->next != nullptr){
			p1->data = p2->data;
			p1 = p1->next;
			while (p1 != nullptr){
				link_type temp = p1->next;
				delete p1;
				p1 = temp;
			}
		}
		// if sl2 is longer than sl1, alloc new memory for sl1
		if (p2->next != nullptr){
			//p1->data = p2->data;
			p2 = p2->next;
			while (p2 != nullptr){
				link_type temp = new __single_list_node < T >;
				temp->data = p2->data;
				temp->next = nullptr;
				p1->next = temp;
				p1 = p1->next;
				p2 = p2->next;
			}
		}
		return *this;
	}
	SingleList& assign(size_type n, const T& val)
	{
		link_type p = head;
		while (n > 0 && p->next != nullptr){
			p->next->data = val;
			p = p->next;
			--n;
		}
		while (n-- > 0){
			link_type temp = new __single_list_node < T > ;
			temp->data = val;
			temp->next = nullptr;
			p->next = temp;
			p = p->next;
		}
		if (p->next != nullptr){
			link_type pnext = p->next;
			while (pnext != nullptr){
				link_type temp = pnext->next;
				delete pnext;
				pnext = temp;
			}
			p->next = nullptr;
		}
		return *this;
	}

	/*
	template<typename _FwdIt>
	SingleList& assign(_FwdIt first, _FwdIt last)
	{
		return assign_range(first, last);
	}
	*/
	SingleList& assign(std::initializer_list<T> init_list){
		return assign_range(init_list.begin(), init_list.end());
	}

	SingleList& assign(SingleList&& rsl)
	{
		// before move assignment, free old memory first.
		clear();
		head = rsl.head;
		rsl.head = nullptr;
		return *this;
	}

	value_type& front(){
		return head->next->data;
	}

	// insert elements
	void push_front(const T& elem){
		link_type temp = new __single_list_node < T > ;
		temp->data = elem;
		temp->next = head->next;
		head->next = temp;
	}

	template<typename _FwdIt>
	iterator insert_after(_FwdIt pos, const T& elem)
	{
		link_type temp = new __single_list_node < T > ;
		temp->data = elem;
		// problem: how to get link_node according to pos.
		// so class iterator contains link_type node.
		temp->next = pos.node->next;
		pos.node->next = temp;
		return iterator(temp);
	}

	template<typename _FwdIt>
	iterator insert_after(_FwdIt pos, size_type n, const T& elem)
	{
		while (n > 0){
			pos = insert_after(pos, elem);
			--n;
		}
		return pos;
	}
	/*
	template<typename _FwdIt1, typename _FwdIt2>
	iterator insert_after(_FwdIt1 pos, _FwdIt2 first, _FwdIt2 last)
	{
		return insert_range(pos, first, last);
	}
	*/
	template<typename _FwdIt>
	iterator insert_after(_FwdIt pos, std::initializer_list<T> init_list)
	{
		return insert_range(pos, init_list.begin(), init_list.end());
	}

	template<typename _FwdIt>
	void erase_after(_FwdIt pos){
		erase_after(pos, end());
	}
	template<typename _FwdIt>
	void erase_after(_FwdIt first, _FwdIt last)
	{
		if (first != last){
			_FwdIt temp = first;
			_FwdIt pos = ++temp;
			while (pos != last){
				delete (pos++).node;
			}
			first.node->next = pos.node;
		}
	}

	void remove(const T& val){
		if (head != nullptr){
			link_type p = head;
			while (p->next != nullptr){
				if (p->next->data == val){
					link_type temp = p->next;
					p -> next = p->next->next;
					delete temp;
				}
				else
					p = p->next; // no else will result in one val left
			}
		}
	}
	template<typename _Pr>
	void remove_if(_Pr _Pred){

	}

	void resize(size_type n)
	{
		_resize(n, T());
	}

	void resize(size_type n, const T& val)
	{
		_resize(n, val);
	}

	void clear(){
		if (head != nullptr){
			link_type p = head->next;
			while (p != nullptr){
				link_type temp = p->next;
				delete p;
				p = temp;
			}
			delete head;
		}
	}

	iterator before_begin(){
		return iterator(head);
	}

	iterator begin(){
		return iterator(head->next);
	}

	iterator end(){
		return iterator(nullptr);
	}


	// destructor
	~SingleList(){
		clear();
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
	template<typename _FwdIt>
	void init_n(_FwdIt first, size_type n, const T& value){
		link_type p = first.node;
		while (n-- > 0){
			link_type temp = new __single_list_node<T>;
			temp->data = value;
			temp->next = nullptr;
			p->next = temp;
			p = p->next;
		}
	}
	template<typename _FwdIt>
	void init_range(_FwdIt first, _FwdIt last)
	{
		empty_init();
		link_type p = head;
		for (; first != last; ++first){
			link_type temp = new __single_list_node < T >;
			temp->data = *first;
			temp->next = nullptr;
			p->next = temp;
			p = p->next;
		}
	}
	
	template<typename _FwdIt>
	SingleList& assign_range(_FwdIt first, _FwdIt last)
	{
		link_type p1 = head;
		// just copy data
		while (p1->next != nullptr && first != last){
			p1->next->data = *first;
			p1 = p1->next;
			++first;
		}
		// if sl1 is longer than sl2, delete left
		if (p1->next != nullptr){
			link_type p = p1->next;
			while (p != nullptr){
				link_type temp = p->next;
				delete p;
				p = temp;
			}
			p1->next = nullptr;
		}
		// if sl2 is longer than sl1, alloc new memory for sl1
		while (first != last){
			link_type temp = new __single_list_node < T > ;
			temp->data = *(first++);
			temp->next = nullptr;
			p1->next = temp;
			p1 = p1->next;
		}
		return *this;
	}

	template<typename _FwdIt1, typename _FwdIt2>
	iterator insert_range(_FwdIt1 pos, _FwdIt2 first, _FwdIt2 last)
	{
		while (first != last){
			pos = insert_after(pos, *first);
			++first;
		}
		return pos;
	}

	void _resize(size_type n, const T& val)
	{
		if (head == nullptr)
			init_n(before_begin(), n, val);
		else{
			link_type p = head;
			while (p->next != nullptr && n > 0){
				p = p->next;
				--n;
			}
			while (p->next != nullptr){
				erase_after(iterator(p));
			}
			if (n > 0){
				init_n(iterator(p), n, val);
			}
		}
	}
};

#endif