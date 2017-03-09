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


template <typename _FwdIt> inline
_FwdIt min_element(_FwdIt first, _FwdIt last)
{
	_FwdIt _Min = first;
	for(; first != last; ++first)
		if(*first < *_Min)
			_Min = first;
	return _Min;
}

templat <typename _FwdIt, typename _Pr> inline
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

