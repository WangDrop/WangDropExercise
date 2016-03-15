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
void quickSort(vector<Comparable> & vec,  int left, int right)
{
    if(left + 10 <= right){//元素较多的时候选用块排
        Comparable pivot = median3(vec, left, right);
        int i = left, j = right - 1;//这时候最后位置的元素实际上存放的是枢纽元
        for(;;){
            while(a[++i] < pivot);
            while(a[--j] > pivot);
            if(i < j)
                swap(a[i], a[j]);
            else
                break;
        }
        swap(a[i], a[right - 1]);//将枢纽元放置到对的位置上
        quickSort(vec, left, i - 1);
        quickSort(vec, i + 1, right);
    }else//元素较少的时候选用插入排序
        insertSort(vec, left, right);
}
