/*************************************************************************
	> File Name: mergeSort.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年03月07日 星期一 14时24分33秒
 ************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;
template <typename Comparable>
void mergeSort(vector<Comparable> & vec)
{
    vector<Comparable> tmpArray(vec.size());
    mergeSort(vec, tmpArray, 0, vec.size() - 1);
}

template <typename Comparable>
void mergeSort(vector<Comparable> & vec, vector<Comparable> & tmpArray,
              int left, int right)
{
    if(left < right){
        int mid = (left + right)/2;
        mergeSort(vec, tmpArray, left, mid);
        mergeSort(vec, tmpArray, mid + 1, right);
        merge(vec, tmpArray, left, mid + 1, right);
    }
}

template<typename Comparable>
void merge(vector<Comparable> & vec, vector<Comparable> & tmpArray, int leftBegin, int rightBegin, int rightEnd)
{
    int leftEnd = rightBegin - 1;
    int nElems = rightEnd - leftBegin + 1;
    int tmpPos = leftBegin;
    while(leftBegin < leftEnd && rightBegin < rightEnd){
        if(vec[leftBegin] < vec[rightBegin])
            tmpArray[tmpPos++] = vec[leftBegin++];
        else
            tmpArray[tmpPos++] = vec[rightBegin++];
    }
    while(leftBegin < leftEnd)
        tmpArray[tmpPos++] = vec[leftBegin++];
    while(rightBegin < rightEnd)
        tmpArray[tmpPos++] = vec[rightBegin++];
    vec.clear();
    copy(tmpArray.begin(), tmpArray.end(), back_inserter(vec));
}

int main()
{
    int nums[10] = {9,1,4,2,7,5,6,8,0,22};
    vector<int> testArray(nums[0], nums[9]);
    mergeSort(testArray);

}
