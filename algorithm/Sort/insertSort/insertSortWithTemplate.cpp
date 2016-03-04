#include <iostream>
#include <algorithm>
#include <functional>
//两参数，实际上借助于三参数的来进行排序
using namespace std;
template<typename Iterator, typename Comparator>
void insertSort(const Iterator & begin, const Iterator & end, Comparator lessThan);

template<typename Iterator>
void insertSort(const Iterator & begin, const Iterator & end)
{
	if(begin != end)
		insertSortHelp(begin, end, *begin);
}

template<typename Iterator, typename Object>
void insertSortHelp(const Iterator & begin, const Iterator & end, const Object & obj)
{
	insertSort(begin, end, less<Object>());
}

//下面就可以实现上面的三参数排序了，为了得到一个泛型，还是需要建立一个四参数的排序
template<typename Iterator, typename Comparator>
void insertSort(const Iterator & begin, const Iterator & end, Comparator lessThan)
{
	if(begin != end)
		insertSort(begin, end, lessThan, *begin);
}

template<typename Iterator, typename Comparator, typename Object>
void insertSort(const Iterator & begin, const Iterator & end, Comparator lessThan,  const Object & obj)
{
	Iterator j;
	for(Iterator i = begin+1; i != end; ++i){
		Object tmp = *i;
		for(j = i; j != begin && lessThan(tmp, *(j-1)); --j)
			*j = *(j-1);
		*j = tmp;
	}
}

