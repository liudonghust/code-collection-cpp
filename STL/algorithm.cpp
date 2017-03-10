/*
for simply, assume 
1、all range [first, las) is valid.
2、all Compare Op is strict weak ordering

introduction to arguments:
_InIt:  input iterator type
_FwdIt: Forward iterator type
_Fn1:   Unary function type
_Pr:    predicate operation
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

template <typename _FwdIt, typename _Pr> inline
_FwdIt min_element(_FwdIt first, _FwdIt last, _Pr _Pred)
{
	_FwdIt _Min = first;
	for(; first != last; ++first)
		if(_Pred(*first, *_Min))
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

template <typename _FwdIt, typename _Pr> inline
_FwdIt max_element(_FwdIt first, _FwdIt last, _Pr _Pred)
{
	_FwdIt _Max = first;
	for(; first != last; ++first)
		if(!(_Pred(*first, *_Min)))
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
pair<FowIt, FowIt> minmax_element(FowIt first, FowIt last, _Pr _Pred)
{
	pair<FowIt, FowIt> result{ first, first };
	if (first == last) return result;       // empty range
	if (++first == last) return result;     // one element range
	// two elements range
	if (_Pred(*first, *result.first))
		result.first = first;
	else
		resul.second = first;
	// one time two elements: first, next
	while(++first != last){
		FowIt next = first;
		if ( ++next == last)  // only one element(first) left
			if(_Pred(*first, *(result.first)))
				result.first = first;
			else(!(_Pred(*first, *result.second)))
				result.second = first;
		else{
			if(_Pred(*first, *next))     // first < next
				if(_Pred(*first, *result.first))
					result.first = first;
				else if(!(_Pred(*next, *result.second)))
					result.second = next;
			else
				if(_Pred(*next, *result.first))
					result.first = next;
				else if(!(_Pred(*first, *result.second)))
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
			if(_Pred(*cur, first))
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





template <typename _InIt1, typename _InIt2> inline
bool equal(_InIt1 first1, _InIt1 last1, _InIt2 first2)

template <typename _InIt, typename _Fn1> inline
_Fn1 for_each(_InIt first, _InIt last, _Fn1 _Func)
{
	for(; first != last; ++first)
		_Func(first);

	return (move(_Func));       // since C++11
}

