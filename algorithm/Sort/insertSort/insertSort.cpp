#include <iostream>
	
template<typename Comparable>
void insertSort(vector<Comparable> vec)
{
    int j = 0;
    for(int i = 1; i < vec.size(); ++i){
	Comparable tmp = vec[i];
	for(j = i; j > 0 && vec[j-1] > tmp; --j){
	    vec[j] = vec[j-1];
	}
	vec[j] = tmp;
    }
}
