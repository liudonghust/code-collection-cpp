#ifndef SINGLELIST_H
#define SINGLELIST_H
#include <iosfwd>
#include <cstddef>
#include <initializer_list>
#include <type_traits>
#include <iterator>
#include <string>

template<typename _Iter>
struct _Is_Iterator
	: public std::integral_constant<bool, !std::is_integral<_Iter>::value>
{};
template<typename T>
class __single_list_node{
public:
	typedef __single_list_node node;
	typedef T value_type;
	value_type __data;
	node *__next;
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
		return node->__data;
	}

	const_iterator& operator++(){
		node = node->__next;
		return *this;
	}

	const_iterator& operator++(int) {
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

// iterator is based on const_iterator.
// so we can use const_iterator as param in container.
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
		return node->__data;
	}

	iterator& operator++(){
		node = node->__next;
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
	explicit SingleList(size_type n){
		empty_init();
		insert_after(before_begin(), n, T());
	}
	explicit SingleList(size_type n, const value_type& val)
	{
		empty_init();
		insert_after(before_begin(), n, T(val));
	}
	template<typename _Iter,
		typename = std::enable_if<_Is_Iterator<_Iter>::value, void>::type>
	SingleList(_Iter first, _Iter last){
		empty_init();
		insert_after(before_begin(), first, last);
	}
	SingleList(std::initializer_list<T> init_list){
		empty_init();
		insert_after(before_begin(), init_list.begin(), init_list.end());
	}
	// copy constructor
	SingleList(const SingleList& sl){
		empty_init();
		insert_after(before_begin(), sl.begin(), sl.end());
	}
	// move constructor
	SingleList(SingleList&& rs)
	{
		head = rs.head;
		rs.head = nullptr;
	}
	
	SingleList& operator=(const SingleList& sl)
	{
		assign(sl.begin(), sl.end());
		return *this;
	}
	SingleList& operator=(std::initializer_list<T> init_list){
		assign(init_list.begin(), init_list.end());
		return *this;
	}
	SingleList& operator=(SingleList&& rs){
		// first delete old memory;
		clear();
		head = rs.head;
		rs.head = nullptr;
		return *this;
	}
	template<typename _Iter,
		typename = std::enable_if<_Is_Iterator<_Iter>::value, void>::type>
	void assign(_Iter first, _Iter last)
	{
		iterator _bef_beg = before_begin();
		iterator _beg = begin();
		iterator _end = end();
		// copy data;
		while (_beg != _end && first != last){
			if (*_beg != *first)
				*_beg = *first;
			++_beg;
			++_bef_beg;
			++first;
		}
		// if this is longer than sl, delete left
		if (_beg != _end){
			erase_after(_bef_beg, _end);
		}
		// if sl is longer than this, alloc new node
		if (first != last){
			insert_after(_bef_beg, first, last);
		}
	}
	void assign(size_type n, const value_type& elem){
		iterator _bef_beg = before_begin();
		iterator _beg = begin();
		iterator _end = end();
		while (_beg != _end && n > 0){
			*_beg = elem;
			++_beg;
			++_bef_beg;
			--n;
		}
		if (n > 0){
			insert_after(_bef_beg, n, elem);
		}
		if (_beg != _end){
			erase_after(_bef_beg, _end);
		}
	}
	void assign(std::initializer_list<T> init_list){
		assign(init_list.begin(), init_list.end());
	}
	
	// ignore head node
	bool operator==(const SingleList& sl) const {
		const_iterator _beg = begin();
		const_iterator _end = end();
		const_iterator _first = sl.begin();
		const_iterator _last = sl.end();
		while (_beg != _end && _first != _last){
			if (*_beg != *_first)
				return false;
			++_beg;
			++_first;
		}
		return _beg == _first;
	}
	bool operator!=(const SingleList& sl)const {
		return (!(*this == sl));
	}
	bool operator<(const SingleList& sl) const {
		const_iterator _beg = begin();
		const_iterator _end = end();
		const_iterator _first = sl.begin();
		const_iterator _last = sl.end();
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
		// if this is longer than sl
		if (_beg != _end)
			return false;
		// if this == sl
		if (_beg == _end && _first == _last)
			return false;
		return true;
	}
	bool operator>(const SingleList& sl) const{
		return sl < *this;
	}
	bool operator<=(const SingleList& sl) const{
		return (!(*this > sl));
	}
	bool operator>=(const SingleList& sl) const{
		return (!(*this < sl));
	}
	bool empty(){ // not include head node
		return begin() == end();
	}

	reference front(){
		return *(begin());
	}
	const_reference front() const{
		return *(begin());
	}
	void push_front(const value_type& elem){
		insert_after(before_begin(), elem);
	}
	
	iterator insert_after(const_iterator pos, const value_type& elem)
	{
		_insert_after(pos, elem);
		return iterator(++pos.node);
	}
	iterator insert_after(const_iterator pos, size_type n, const value_type& val)
	{
		for (; 0 < n; --n, ++pos){
			_insert_after(pos, val);
		}
		return iterator(pos.node);
	}
	template<typename _Iter = std::enable_if<_Is_Iterator<_Iter>::value, void>::type>
	iterator insert_after(const_iterator pos, _Iter first, _Iter last)
	{
		for (; pos != end() && first != last; ++first, ++pos)
			_insert_after(pos, *first);
		return iterator(pos.node);
	}
	iterator insert_after(const_iterator pos, std::initializer_list<T> init_list){
		return insert_after(pos, init_list.begin(), init_list.end());
	}

	void pop_front(){
		link_type temp = begin().node;
		head->__next = temp->__next;
		delete temp;
	}
	void remove(const value_type& val){
		iterator _bef_beg = before_begin();
		iterator _beg = begin();
		iterator _end = end();
		while (_beg != _end){
			if (*_beg == val){
				link_type temp = _beg.node;
				_bef_beg.node->__next = temp->__next;
				++_beg;
				delete temp;
			}
			else{
				++_beg;
				++_bef_beg;
			}
			
		}
	}
	
	template<typename _Pr>
	void remove_if(_Pr Pred){
		iterator _bef_beg = before_begin();
		iterator _beg = begin();
		iterator _end = end();
		while (_beg != _end){
			if (Pred(*_beg)){
				link_type temp = _beg.node;
				_bef_beg.node->__next = temp->__next;
				++_beg;
				delete temp;
			}
			else{
				++_beg;
				++_bef_beg;
			}
		}
	}

	void unique(){
		iterator _i = begin();
		iterator _e = end();
		for (; _i != _e;){
			iterator _j = _i;
			++_j;
			// loop to find first pair<i, j> not equal.
			for (; _j != _e && *_i == *_j; ++_j);
			// if i is not adjacent with j, erase duplicate elem.
			if (_i.node->__next != _j.node)
				erase_after(_i, _j);
			_i = _j;
		}
	}

	template<typename _Pr>
	void unique(_Pr Pred){
		iterator _i = begin();
		iterator _e = end();
		for (; _i != _e;){
			iterator _j = _i;
			++_j;
			// loop to find first pair<i, j> not equal.
			for (; _j != _e && Pred(*_i, *_j); ++_j);
			// if i is not adjacent with j, erase duplicate elem.
			if (_i.node->__next != _j.node)
				erase_after(_i, _j);
			_i = _j;
		}
	}

	void splice_after(const_iterator pos, SingleList& sl, const_iterator pos2){
		// assume pos and pos2 != end
		/*if(pos2 == sl.end() || next(pos2) == sl.end() || pos == end()*/
		const_iterator _j = pos2;
		++_j;
		if (pos != pos2 && pos != _j){
			// relink sl
			pos2.node->__next = _j.node->__next;
			// relink this
			_j.node->__next = pos.node->__next;
			pos.node->__next = _j.node;
		}
	}
	void splice_after(const_iterator pos, SingleList& sl, const_iterator first2, const_iterator last2){
		if (first2 != last2 && pos != first2){
			// find the position before last2
			const_iterator _bef_last2 = first2;
			while (_bef_last2.node->__next != last2.node)
				++_bef_last2;
			// relink this
			_bef_last2.node->__next = pos.node->__next;
			pos.node->__next = first2.node->__next;
			// relink sl
			first2.node->__next = last2.node;
		}
	}
	void splice_after(const_iterator pos, SingleList& sl){
		if (!sl.empty()){
			if (pos != end()){
				// find last position in sl
				const_iterator _bef_last2 = sl.begin();
				for (; _bef_last2.node->__next != nullptr; ++_bef_last2);
				// relink this
				_bef_last2.node->__next = pos.node->__next;
				pos.node->__next = sl.before_begin().node->__next;
				// relink sl
				sl.before_begin().node->__next = nullptr;
			}
		}
	}

	void reverse(){
		if (empty()) return;
		link_type prevNode = head->__next;
		link_type revNode = prevNode->__next;
		while (revNode != nullptr){
			prevNode->__next = revNode->__next;
			revNode->__next = head->__next;
			head->__next = revNode;
			revNode = prevNode->__next;
		}
	}
	void erase_after(const_iterator pos){
		erase_after(pos, end());
	}
	void erase_after(const_iterator first, const_iterator last)
	{
		link_type f = first.node;
		link_type p = f->__next;
		link_type l = last.node;
		while (p != l){
			link_type temp = p->__next;
			delete p;
			p = temp;
		}
		f->__next = l;
	}

	iterator begin(){
		return iterator(head->__next);
	}
	// for const SingleList to call
	const_iterator begin() const{
		return const_iterator(head->__next);
	}
	const_iterator cbegin() const{
		return const_iterator(head->__next);
	}
	iterator end(){
		return iterator(nullptr);
	}
	const_iterator end() const{
		return const_iterator(nullptr);
	}
	const_iterator cend() const{
		return const_iterator(nullptr);
	}
	iterator before_begin(){
		return iterator(head);
	}
	const_iterator before_begin() const {
		return const_iterator(head);
	}
	const_iterator cbefore_begin(){
		return const_iterator(head);
	}

	void resize(size_type n){
		resize(n, T());
	}
	void resize(size_type n, const value_type& val){
		iterator _bef_beg = before_begin();
		iterator _beg = begin();
		iterator _end = end();
		for (; n > 0 && _beg != _end; --n, ++_beg, ++_bef_beg);
		// if n > length, insert.
		if (n > 0){
			insert_after(_bef_beg, n, T(val));
		}
		// if n < length, erase.
		if (_beg != _end){
			erase_after(_bef_beg);
		}
	}
	void clear(){
		if (head != nullptr){
			link_type p = head->__next;
			while (p != nullptr){
				link_type temp = p->__next;
				delete p;
				p = temp;
			}
			delete head;
		}
	}

	~SingleList(){
		clear();
	}
	// traversal
	friend std::ostream& operator<<(std::ostream& os, const my_type& l){
		const_iterator iter = l.begin();
		while (iter != l.end()){
			os << *iter << " ";
			++iter;
		}
		return os;
	}

protected:
	link_type head;       // head node in the list

	// reuse code when define constructor
	void empty_init(){
		head = new __single_list_node<T>;
		head->__next = nullptr;
	}

	void _insert_after(const_iterator pos, const value_type& elem){
		link_type temp = new __single_list_node < T >;
		temp->__data = elem;
		temp->__next = pos.node->__next;
		pos.node->__next = temp;
	}
	
};

#endif