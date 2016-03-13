/*************************************************************************
	> File Name: quickSort.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年03月13日 星期日 17时57分32秒
 ************************************************************************/

#include<iostream>
using namespace std;

template<typename Comparable>
void quickSort(vector<Comparable> vec)
{
    quickSort(a, 0, a.size()-1);
}



template <typename Comparable>
const Comparable & median3(vector<Comparable> & a, int left, int right)
{
    int center = (left + right)/2;
    if(a[center] < a[left])
        swap(a[center], a[left]);
    if(a[right] < a[left])
        swap(a[right], a[left]);
    if(a[right] < a[center])
        swap(a[right], a[center]);
    swap(a[right - 1], a[center]); //将枢纽元放置到right-1的位置上
    return a[right - 1];
}

template<typename Comparable>
