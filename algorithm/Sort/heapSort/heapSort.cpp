/*************************************************************************
	> File Name: heapSort.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年03月07日 星期一 13时14分31秒
 ************************************************************************/

#include<iostream>
using namespace std;
template<typename Comparable>
void heapSort(vector<Comparable> vec)
{
    for(int i = vec.size()/2; i >= 0; i--)//build the heap
        percDown(vec, i, vec.size());
    for(int j = vec.size() - 1; j > 0; j--){//delete the max
        swap(vec[0], vec[j]);
        percDown(vec, 0, j);
    }
}

inline int leftchild(int i)
{
    return 2 * i + 1; //return the left child
}

template<typename Comparable>
void percDown(vector<Comparable> & a, int i, int n)
{
    int child;
    Comparable tmp;
    for(tmp = a[i]; leftchild(i) < n; i = leftchild(i)){
        child = leftchild(i);
        if(child != n - 1 && a[child] < a[child + 1])
            child++; //右孩子比较大
        if(tmp < a[child])
            a[i] = a[child];
        else
            break;
    }
    a[i] = tmp;
}




