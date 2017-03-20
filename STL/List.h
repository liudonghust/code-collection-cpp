#ifndef LIST_H
#define LIST_H
#include <type_traits>
#include <cstddef>
#include <initializer_list>

template<typename _Iter>
struct _Is_Iterator
	: public std::integral_constant<bool, !std::is_integral<_Iter>::value>
{};

template<typename T>
struct __list_node{
	typedef T value_type;
	typedef __list_node<T> _MyT;
	_MyT* __prev;
	_MyT* __next;
	value_type __data;
};

template<typename T>
class __list_const_iterator{
public:
	typedef T value_type;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef __list_const_iterator<T> const_iterator;
	typedef __list_node<T>* link_type;

	link_type nodePtr;

	__list_const_iterator() : nodePtr(nullptr) {}
	__list_const_iterator(link_type nodePtr) : nodePtr(nodePtr) {}
	__list_const_iterator(const const_iterator& iter2) : nodePtr( iter2.nodePtr ) {}

	const_reference operator*(){
		return nodePtr->__data;
	}

	const_iterator operator++(){
		nodePtr = nodePtr->__next;
		return *this;
	}

	const_iterator operator++(int){
		const_iterator temp = *this;
		++(*this);
		return temp;
	}

	const_iterator operator--(){
		nodePtr = nodePtr->__prev;
		return *this;
	}

	const_iterator operator--(int){
		const_iterator temp = *this;
		--(*this);
		return temp;
	}

	bool operator==(const const_iterator& iter){
		return nodePtr == iter.nodePtr;
	}
	bool operator!=(const const_iterator& iter){
		return (!(*this == iter));
	}
};

template<typename T>
class __list_iterator : public __list_const_iterator < T >
{
public:
	typedef T value_type;
	typedef value_type* pointer;
	typedef value_type& reference;
	typedef __list_iterator<T> iterator;
	typedef __list_const_iterator<T> _BaseType;
	typedef typename _BaseType::link_type link_type;

	__list_iterator(){}
	__list_iterator(link_type nodePtr) : _BaseType(nodePtr) {}
	__list_iterator(const iterator& iter2) : _BaseType(iter2) {}

	reference operator*(){
		return nodePtr->__data;
	}

	iterator operator++(){
		nodePtr = nodePtr->__next;
		return *this;
	}
	iterator operator++(int){
		iterator temp = *this;
		++(*this);
		return temp;
	}

	iterator operator--(){
		nodePtr = nodePtr->__prev;
		return *this;
	}
	iterator operator--(int){
		iterator temp = *this;
		--(*this);
		return temp;
	}
};

// cycle double link 
template<typename T>
class List{
public:
	typedef T value_type;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef size_t size_type;
	typedef List<T> MyType;
	typedef __list_node<T>* link_type;
	typedef __list_iterator<T> iterator;
	typedef __list_const_iterator<T> const_iterator;

protected:
	link_type head;

public:
	List(){
		empty_init();
	}
	explicit List(size_type n){
		empty_init();
		insert(begin(), n, T());
	}
	List(size_type n, const T& val){
		empty_init();
		insert(begin(), n, val);
	}
	explicit List(std::initializer_list<T> init_list){
		empty_init();
		insert(begin(), init_list.begin(), init_list.end());
	}
	template<typename _Iter,
		typename = std::enable_if<_Is_Iterator<_Iter>::value, void>::type>
	List(_Iter first, _Iter last){
		empty_init();
		insert(begin(), first, last);
	}
	List(const MyType& l){
		empty_init();
		insert(begin(), l.begin(), l.end());
	}
	List(MyType&& rl){
		head = rl.head;
		rl.head = nullptr;
	}

	void assign(size_type n, const T& val){
		iterator _beg = begin();
		iterator _end = end();
		while (_beg != _end && n > 0){
			*_beg = val;
			++_beg;
			--n;
		}
		if (n > 0)
			insert(_beg, n, val);
		if (_beg != _end)
			erase(_beg, _end);
	}
	template<typename _Iter,
		typename = std::enable_if<_Is_Iterator<_Iter>::value, void>::type>
		void assign(_Iter first, _Iter last){
		iterator _beg = begin();
		iterator _end = end();
		while (_beg != _end && first != last){
			*_beg = *first;
			++_beg;
			++first;
		}
		if (_beg != _end)
			erase(_beg, _end);
		if (first != last)
			insert(_beg, first, last);
	}
	void assign(std::initializer_list<T> init_list){
		assign(init_list.begin(), init_list.end());
	}

	MyType& operator=(const MyType& l){
		assign(l.begin(), l.end());
		return *this;
	}
	MyType& operator=(MyType&& rl){
		clear();
		head = rl.head;
		rl.head = nullptr;
		return *this;
	}
	MyType& operator=(std::initializer_list<T> init_list){
		assign(init_list.begin(), init_list.end());
		return *this;
	}

	reference front(){
		return (*(begin()));
	}
	const_reference front() const {
		return (*(begin()));
	}
	reference back(){
		return head->__prev->__data;
	}
	const_reference back() const{
		return head->__prev->__data;
	}

	bool operator==(const MyType& l) const{
		const_iterator _beg = begin();
		const_iterator _end = end();
		const_iterator _first = l.begin();
		const_iterator _last = l.end();
		while (_beg != _end && _first != _last){
			if (*_beg != *_first)
				return false;
			++_beg;
			++_first;
		}
		return _beg == _end && _first == _last;
	}
	bool operator!=(const MyType& l) const {
		return !(*this == l);
	}
	bool operator<(const MyType& l) const {
		const_iterator _beg = begin();
		const_iterator _end = end();
		const_iterator _first = l.begin();
		const_iterator _last = l.end();
		while (_beg != _end && _first != _last){
			if (*_beg < *_first)
				return true;
			else if (*_beg > *_first)
				return false;
			else{
				++_beg;
				++_first;
			}
		}
		if (_first != _last)
			return true;
		return false;
	}
	bool operator<=(const MyType& l) const {
		return *this < l || *this == l;
	}
	bool operator>(const MyType& l) const {
		return l < *this;
	}
	bool operator>=(const MyType& l) const {
		return *this > l || *this == l;
	}

	void push_front(const T& val){
		insert(begin(), val);
	}
	void pop_front(){
		erase(begin());
	}
	void push_back(const T& val){
		insert(end(), val);
	}
	void pop_back(){
		erase(iterator(head->__prev));
	}
	iterator insert(const_iterator pos, const T& val){
		_insert(pos, val);
		return iterator((++pos).nodePtr);
	}
	iterator insert(const_iterator pos, size_type n, const T& val){
		for (; n > 0; --n){
			_insert(pos, val);
		}
		return iterator((++pos).nodePtr);
	}
	template<typename _Iter,
		typename = std::enable_if<_Is_Iterator<_Iter>::value, void>::type>
	iterator insert(const_iterator pos, _Iter first, _Iter last){
		for (; first != last; ++first)
			_insert(pos, *first);
		return iterator((++pos).nodePtr);
	}
	iterator insert(const_iterator pos, std::initializer_list<T> init_list){
		insert(pos, init_list.begin(), init_list.end());
		return iterator((++pos).nodePtr);
	}

	size_type size() const{
		size_type ret = 0;
		const_iterator _beg = begin();
		for (; _beg != end(); ++_beg, ++ret);
		return ret;
	}
	bool empty() const{
		return head->__next == head;
	}

	void remove(const T& val){
		iterator _beg = begin();
		iterator _end = end();
		while (_beg != _end){
			if (*_beg == val){
				iterator temp = _beg;
				_beg.nodePtr->__next->__prev = _beg.nodePtr->__prev;
				_beg.nodePtr->__prev->__next = _beg.nodePtr->__next;
				++_beg;
				delete temp.nodePtr;
			}
			else
				++_beg;
		}
	}
	
	void unique(){
		iterator _i = begin();
		iterator _end = end();
		while (_i != _end){
			iterator _j = _i;
			++_j;
			for (; _j != _end && *_i == *_j; ++_j);
			if (++_i != _j)
				erase(_i, _j);
			_i = _j;
		}
	}

	void splice(const_iterator pos, MyType& l2){
		splice(pos, l2, l2.begin(), l2.end());
		l2.head->__next = l2.head;
		l2.head->__prev = l2.head;
	}
	void splice(const_iterator pos, MyType& l2, const_iterator pos2){
		// if (std::next(pos2) == pos || pos2 == l2.end())
		// relink l2;
		pos2.nodePtr->__next->__prev = pos2.nodePtr->__prev;
		pos2.nodePtr->__prev->__next = pos2.nodePtr->__next;
		// relink l1
		pos.nodePtr->__prev->__next = pos2.nodePtr;
		pos2.nodePtr->__prev = pos.nodePtr->__prev;
		pos2.nodePtr->__next = pos.nodePtr;
		pos.nodePtr->__prev = pos2.nodePtr;
	}
	void splice(const_iterator pos, MyType& l2, const_iterator first2, const_iterator last2){
		while (first2 != last2){
			const_iterator temp = first2;
			++first2;
			splice(pos, l2, temp);
		}
	}

	void reverse  (){
		iterator _j = begin();
		iterator _end = end();
		if (_j == _end) return;
		for (++_j; _j != _end;){
			link_type prev = _j.nodePtr->__prev;
			link_type next = _j.nodePtr->__next;
			_j.nodePtr->__next = head->__next;
			_j.nodePtr->__prev = head;
			head->__next->__prev = _j.nodePtr;
			head->__next = _j.nodePtr;
			prev->__next = next;
			next->__prev = prev;
			_j = next;
		}
	}
	void resize(size_type n){
		resize(n, T());
	}
	void resize(size_type n, const T& val){
		iterator _beg = begin();
		iterator _end = end();
		for (; n > 0 && _beg != _end; --n, ++_beg);
		// if n > length, insert.
		if (n > 0){
			insert(_beg, n, val);
		}
		// if n < length, erase.
		if (_beg != _end){
			erase(_beg, _end);
		}
	}
	iterator erase(iterator pos){
		link_type prev = pos.nodePtr->__prev;
		link_type next = pos.nodePtr->__next;
		next->__prev = prev;
		prev->__next = next;
		delete pos.nodePtr;
		return iterator(next);
	}
	iterator erase(iterator first, iterator last){
		while (first != last){
			first = erase(first);
		}
		return first;
	}

	void clear(){
		if (head != nullptr){
			iterator _beg = begin();
			iterator _end = end();
			while (_beg != _end){
				iterator del = _beg;
				++_beg;
				delete del.nodePtr;
			}
			delete head;
		}
	}

	iterator begin(){
		return iterator(head->__next);
	}
	const_iterator begin() const {
		return const_iterator(head->__next);
	}
	// end() is pointer to head
	iterator end(){
		return iterator(head);
	}
	const_iterator end() const{
		return const_iterator(head);
	}
	const_iterator cbegin() const {
		return const_iterator(head->__next);
	}
	const_iterator cend() const {
		return const_iterator(head);
	}

	~List(){
		clear();
	}

protected:
	void empty_init(){
		head = new __list_node < T > ;
		head->__next = head;
		head->__prev = head;
	}

	void _insert(const_iterator pos, const T& val){
		link_type temp = new __list_node < T > ;
		temp->__data = val;
		pos.nodePtr->__prev->__next = temp;
		temp->__prev = pos.nodePtr->__prev;
		pos.nodePtr->__prev = temp;
		temp->__next = pos.nodePtr;
	}
};
#endif