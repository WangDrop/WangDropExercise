/*************************************************************************
	> File Name: mergeSort.h
	> Author: 
	> Mail: 
	> Created Time: 2016年03月07日 星期一 15时38分29秒
 ************************************************************************/

#ifndef _MERGESORT_H
#define _MERGESORT_H
template <typename Comparable>
void mergeSort(vector<Comparable> & vec);

template <template Comparable>
void mergeSort(vector<Comparable> &vec, vector<Comparable> & tmpArray, int left, int right);

template <typename Comparable>
void merge(vector<Comparable> & vec, vector<Comparable> & tmpArray, int leftBegin, int rightBegin, int rightEnd);

#endif
