/*
for simply, assume 
1、all range [first, las) is valid.
2、all Compare Op is strict weak ordering

introduction to arguments:
_InIt:  input iterator type
_FwdIt: Forward iterator type
_Fn1:   Unary function type
_Fn2:   Binary function type
_Pr:    predicate operation
_Comp:  compare function
*/

template <typename _InIt, typename T> inline
typename iterator_traits<_InIt>::difference_type
count(_InIt first, _InIt last, const T& val)
{
	typename iterator_traits<_InIt>::difference_type _Count = 0;
	for(; first != last; ++first)
		if(*first == val)
			++_Count;
	return _Count;
}

template <typename _InIt, typename _Pr> inline
typename iterator_traits<_InIt>::difference_type
count_if(_InIt first, _InIt last, _Pr _Pred)
{
	typename iterator_traits<_InIt>::difference_type _Count = 0;
	for(; first != last; ++first)
		if(_Pred(*first))
			++_Count;
	return _Count;
}

template<typename _InIt, typename T, typename _Pr> inline
typename iterator_traits<_InIt>::difference_type
_count_pr(_InIt first, _InIt last, const T&val, _Pr _Pred)
{
	iterator_traits<_InIt>::difference_type _count = 0;
	for(; first != last; ++first){
		if(_Pred(*first, val))
			++_cout;
	}
	return _count;
}

/*----------------search---------------------*/
template <typename _FwdIt> inline
_FwdIt min_element(_FwdIt first, _FwdIt last)
{
	_FwdIt _Min = first;
	for(; first != last; ++first)
		if(*first < *_Min)
			_Min = first;
	return _Min;
}

template <typename _FwdIt, typename _Comp> inline
_FwdIt min_element(_FwdIt first, _FwdIt last, _Comp comp)
{
	_FwdIt _Min = first;
	for(; first != last; ++first)
		if(comp(*first, *_Min))
			_Min = first;
	return _Min;
}

template <typename _FwdIt> inline
_FwdIt max_element(_FwdIt first, _FwdIt last)
{
	_FwdIt _Max = first;
	for(; first != last; ++first)
		if(*first > *_Max)
			_Max = first;
	return _Max;
}

template <typename _FwdIt, typename _Comp> inline
_FwdIt max_element(_FwdIt first, _FwdIt last, _Comp comp)
{
	_FwdIt _Max = first;
	for(; first != last; ++first)
		if(!(comp(*first, *_Min)))
			_Max = first;
	return _Max;
}

template <typename _FwdIt> inline
pair<_FwdIt, _FwdIt> minmax_element(_FwdIt first, _FwdIt last)
{
	return minmax_element(first, last, less<>());
}

/* one time two element ,
1. compare these two elements 
2. compare the miner with result.first; maxer with second
so (1 + 2) * (numElem - 1) / 2 times compare
*/
template<typename FowIt, typename _Pr> inline
pair<FowIt, FowIt> minmax_element(FowIt first, FowIt last, _Comp comp)
{
	pair<FowIt, FowIt> result{ first, first };
	if (first == last) return result;       // empty range
	if (++first == last) return result;     // one element range
	// two elements range
	if (comp(*first, *result.first))
		result.first = first;
	else
		resul.second = first;
	// one time two elements: first, next
	while(++first != last){
		FowIt next = first;
		if ( ++next == last)  // only one element(first) left
			if(comp(*first, *(result.first)))
				result.first = first;
			else(!(comp(*first, *result.second)))
				result.second = first;
		else{
			if(comp(*first, *next))     // first < next
				if(comp(*first, *result.first))
					result.first = first;
				else if(!(comp(*next, *result.second)))
					result.second = next;
			else
				if(comp(*next, *result.first))
					result.first = next;
				else if(!(comp(*first, *result.second)))
					result.second = first;
		}
	}
	return result;
}


template<typename _InIt, typename T> inline
_InIt find(_InIt first, _InIt last, const T& val)
{
	for(; first != last; ++first){
		if(*first == val)
			return first;
	}
	return last;
}

template<typename _InIt, typename _Pr> inline
_InIt find_if(_InIt first, _InIt last, _Pr _Pred)
{
	for(; first != last; ++first)
		if(_Pred(*first))
			return first;
	return last;
}

template<typename _InIt, typename T, typename _Pr> inline
_InIt _find_pr(_InIt first, _InIt last, const T&val, _Pr _Pred)
{
	for(; first != last; ++first)
		if(_Pred(*first, val))
			return first;
	return last;
}

template<typename _InIt, typename _Pr> inline
_InIt find_if_not(_InIt first, _InIt last, _Pr _Pred)
{
	for(; first != last; ++first)
		if(! _Pred(*first))
			return first;
	return last;
}


template<typename _FwdIt, typename Sz, typename T> inline
_FwdIt search_n(_FwdIt first, _FwdIt last, Sz count, const T& val)
{
	return search_n(first, last, count, val, equal_to<>());
}

template<typename _FwdIt, typename Sz, typename T, typename _Pr> inline
_FwdIt search_n(_FwdIt first, _FwdIt last, Sz count, const T& val, _Pr _Pred)
{
	for(; first != last; ++first){
		if(_Pred(*first, val)){
			_FwdIt found = first;
			Sz num = count;
			while(1){
				if(--num == 0)
					return first;
				else if(++found == last)
					return last;
				else if(! _Pred(*found, val))
					break;
			}
			first = found;
		}
	}
	return last;
}

template<typename _FwdIt1, typename _FwdIt2> inline
_FwdIt search(_FwdIt1 first1, _FwdIt1 last1, _FwdIt2 first2, _FwdIt2 last2)
{
	return search(first1, last1, first2, last2, equal_to<>());
}

template<typename _FwdIt1, typename _FwdIt2, typename _Pr> inline
_FwdIt1 search(_FwdIt1 first1, _FwdIt1 last1, _FwdIt2 first2, _FwdIt2 last2, _Pr _Pred)
{
	typename iterator_traits<_FwdIt1>::difference_type count1 = 0;
	typename iterator_traits<_FwdIt2>::difference_type count2 = 0;
	count1 = distance(first1, last1);
	count2 = distance(first2, last2);
	for(; conut2 <= count1; ++first1, --count1){
		_FwdIt1 found1 = first1;
		for(_FwdIt2 found2 = first2;; ++found2, ++found1){
			if(found2 == last2)
				return first;
			else if(! _Pred(*found1, *found2))
				break;
		}
	}
	return last1;
}


template<typename _FwdIt1, typename _FwdIt2> inline
_FwdIt1 find_end(_FwdIt1 first1, _FwdIt1 last1, _FwdIt2 first2, _FwdIt last2)
{
	find_end(first1, last1, first2, last2, equal_to<>());
}

template<typename _FwdIt1, typename _FwdIt2, typename _Pr> inline
_FwdIt1 find_end(_FwdIt1 first1, _FwdIt1 last1, _FwdIt2 first2, _FwdIt last2, _Pr _Pred)
{
	_FwdIt1 result = last1;
	for(; ; ++first1){
		_FwdIt1 found1 = first1;
		for(_FwdIt2 found2 = first2; ; ++found2, ++found1){
			if(found2 == last2){
				result = first1;
				break;
			}
			else if(found1 == last1)
				return result;
			else if(!_Pred(*found1, *found2))
				break;
		}
	}
	return result;
}


template<typename _InIt, typename _FwdIt> inline
_InIt find_first_of(_InIt first1, _InIt last1, _FwdIt first2, _FwdIt last2)
{
	return find_first_of(first1, last1, first2, last2, equal_to<>());
}

template<typename _InIt, typename _FwdIt, typenmae _Pr> inline
_InIt find_first_of(_InIt first1, _InIt last1, _FwdIt first2, _FwdIt last2, _Pr _Pred)
{
	for(; first1 != last1; ++first1)
		for(_FwdIt mid2 = first2; mid2 != last2; ++mid2)
			if(_Pred(*first1, *mid2))
				return first1;
	return last1;
}


template<typename _FwdIt> inline
_FwdIt adjacent_find(_FwdIt first, _FwdIt last)
{
	return adjacent_find(first, last, equal_to<>())
}

template<typename _FwdIt, typename _Pr> inline
_FwdIt adjacent_find(_FwdIt first, _FwdIt last, _Pr _Pred)
{
	if(first != last)
		for(_FwdIt cur; cur = first, ++first != last; )
			if(_Pred(*cur, *first))
				return cur;
	return last;
}
/*------------algorithm to predicate**************/

template <typename _InIt1, typename _InIt2> inline
bool equal(_InIt1 first1, _InIt1 last1, _InIt2 first2)
{
	for(; first1 != last1; ++first1, ++last1)
		if((*first1 != *first2))
			return false;
	return true;
}

template <typename _InIt1, typename _InIt2, typename _Pr> inline
bool equal(_InIt1 first1, _InIt1 last1, _InIt2 first2, _Pr _Pred)
{
	for(; first1 != last1; ++first1, ++first2)
		if(! _Pred(*first1, *first2))
			return false
	return true;
}

template<typename _InIt, typename _Pr> inline
bool all_of(_InIt first, _InIt last, _Pr _Pred)
{
	for(; first != last; ++first)
		if(!_Pred(*first))
			return false;
	return true;
}

template<typename _InIt, typename _Pr> inline
bool any_of(_InIt first, _InIt last, _Pr _Pred)
{
	for(; first != last; ++first)
		if(_Pred(*first))
			return true;
	return false;
}

template<typename _InIt, typename _Pr> inline
bool none_of(_InIt first, _InIt last, _Pr _Pred)
{
	return for(; first != last; ++first)
		if(_Pred(*first))
			return false;
	return true;
}

template<typename _FwdIt1, typename _FwdIt2> inline
bool is_permutation(_FwdIt1 first1, _FwdIt1 last1, _FwdIt2 first2, _FwdIt2 last2)
{
	return is_permutation(first1, last1, first2, last2, equal_to<>());
}


/*because no sort, compare count of each number appears in both ranges*/
template<typename _FwdIt1, typename _FwdIt2, _Pr _Pred> inline
bool is_permutation(_FwdIt1 first1, _FwdIt1 last1, _FwdIt2 first2, _Pred)
{
	// find the first inequality of two range
	for(; first1 != last1; ++first1, ++first2)
		if(! _Pred(*first1, *first2))
			break;
	if(first1 != last1){
		//calculate the end of the range2
		_FwdIt2 last2 = first2;
		advance(last2, distance(first1, last1));
		for(_FwdIt1 next1 = first1; next1 != last1; ++next1){
			if(next1 != _find_pr(first1, next1, *next1, _Pred))  // element *next has been counted
				continue;
			// element *next appreas _count2 time in range2
			auto _count2 = _count_pr(first2, last2, *next1, _Pred);  
			if(_count2 ==0 ||                 // dose not appear
				_count2 != _count_pr(first1, last1, *next1, _Pred))  // count does not match!
				return false;
		}
	}
	return true;
}


template<typename _InIt1, typename _InIt2> inline
pair<_InIt1, _InIt2>
mismatch(_InIt1 first1, _InIt1 last1, _InIt2 first2)
{
	return mismatch(first1, last1, first2, equal_to<>());
}

template<typename _InIt1, typename _InIt2, typename _Pr> inline
pair<_InIt1, _InIt2>
mismatch(_InIt1 first1, _InIt1 last1, _InIt2 first2, _Pr _Pred)
{
	while (first1 != last1 && _Pred(*first1, *first2)){
		++first1;
		++first2;
	}
	return make_pair(first1, first2);
}

template<typename _InIt1, typename _InIt2> inline
bool lexicographical_compare(_InIt1 first1, _InIt1 last1, _InIt2 first2, _InIt2 last2)
{
	return lexicographical_compare(first1, last1, first2, last2, less<>());
}

template<typename _InIt1, typename _InIt2, typename _Pr> inline
bool lexicographical_compare(_InIt1 first1, _InIt1 last1, _InIt2 first2, _InIt2 last2, _Pr _Pred)
{
	for(;first1 != last1 && first2 != last2; ++first1, ++first2){
		if(!_Pred(*first1, *first2))
			return false
		if(_Pred(*first1, *first2))
			return true;
	}
	 return (first1 == last1 && first2 != last2);
}

template<typename _FwdIt> inline
bool is_sorted(_FwdIt first, _FwdIt last)
{
	return is_sorted(first, last, less<>());
}

template<typename _FwdIt, typename _Pr> inline
bool is_sorted(_FwdIt first, _FwdIt last, _Pr _Pred)
{
	return is_sorted_until(first, last, _Pred) == last;
}

template<typename _FwdIt> inline
_FwdIt is_sorted_until(_FwdIt first, _FwdIt last)
{
	return is_sorted_until(first, last, less<>());
}

template<typename _FwdIt, typename _Pr> inline
_FwdIt is_sorted_until(_FwdIt first, _FwdIt last, _Pr _Pred)
{
	if(first != last){
		for(_FwdIt cur = first; ++first != last;){
			if(! _Pred(*first, *cur))
				return first;
			cur = first;
		}
	}
	return last;
}

template<typename _InIt, typename _Pr> inline
bool is_partitioned(_InIt first, _InIt last, _Pr _Pred)
{
	for(; first != last; ++first)
		if(!_Pred(*first))
			break;
	for(; first != last; ++first)
		if(_Pred(*first))
			return false;
	return true;
}

template<typename _FwdIt, typename _Pr> inline
_FwdIt partition_point(_FwdIt first, _FwdIt last, _Pr _Pred)
{
	typename iterator_traits<_FwdIt>::difference_type count = 0;
	count = distance(first, last);
	while(0 < count){
		auto count2 = count / 2;
		_FwdIt first2 = first;
		advance(first2, count2);

		if(_Pred(*first2)){
			first = ++first2;
			count = count2 + 1;
		}
		else
			count = count2;
	}
	return first;
}

/*---------------modifying-----------------------*/
template <typename _InIt, typename _Fn1> inline
_Fn1 for_each(_InIt first, _InIt last, _Fn1 _Func)
{
	for(; first != last; ++first)
		_Func(*first);

	return (move(_Func));       // since C++11
}

template<typename _OutIt, typename _InIt> inline
_OutIt copy(_InIt first, _InIt last, _OutIt destFirst)
{
	for(; first != last; ++first, ++destFirst)
		*destFirst = *first;
	return destFirst;
}

template<typename _OutIt, typename _InIt, typename _Pr> inline
_OutIt copy_if(_InIt first, _InIt last, _OutIt destFirst, _Pr _Pred)
{
	for(; first != last; ++first){
		if(_Pred(*first)){
			*destFirst = *first;
			++destFirst;
		}
	}
	return destFirst;
}

template<typename _OutIt, typename _InIt, typename Sz> inline
_OutIt copy_n(_InIt first, Sz num, _OutIt destFirst)
{
	for(Sz i = 0; i < num; ++i){
		*destFirst = *first;
		++first;
		++destFirst;
	}
	return destFirst;
}

template<typename _BiIt1, typename _BiIt2> inline
_BiIt2 copy_backward(_BiIt1 first, _BiIt1 last, _BiIt2 destEnd)
{
	while(first != last){
		--destEnd;
		--last;
		*destEnd = *last;
	}
	return destEnd;
}

template<typename _OutIt, typename _InIt> inline
_OutIt move(_InIt first, _InIt last, _OutIt destFirst)
{
	for(; first != last; ++first, ++destFirst)
		*destFirst = move(*first);
	return destFirst;
}

template<typename _BiIt1, typename _BiIt2> inline
_BiIt2 move_backward(_BiIt1 first, _BiIt1 last, _BiIt2 destEnd)
{
	while(first != last){
		--destEnd;
		--last;
		*destEnd = move(*last);
	}
	return destEnd;
}

template<typename _InIt, typename _OutIt, typename _Fn1> inline
_OutIt transform(_InIt first, _InIt last, _OutIt destFirst, _Fn1 fn1)
{
	for(; first != last; ++first, ++destFirst)
		*destFirst = fn1(*first);
	return destFirst;
}

template<typename _InIt1, typename _InIt2, typename _OutIt, typename _Fn2> inline
_OutIt transform(_InIt first1, _InIt last1, _InIt first2, _OutIt destFirst, _Fn1 fn2)
{
	for(; first1 != last1; ++first1, ++first2, ++destFirst)
		*destFirst = fn2(*first1, *first2);
	return destFirst;
}

