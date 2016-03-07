#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

template<typename Comparable>
void shellSort(vector<Comparable> & vec)
{
    for(int gap = vec.size()/2; gap > 0; --gap){
        for(int i = gap; i < vec.size(); i++){
            Comparable tmp = vec[i];
            int j = i;
            for(; j >= gap && tmp < vec[j-gap]; j-=gap){
                vec[j] = vec[j-gap];
            }
            vec[j] = tmp;
        }   
    }
}

int main()
{
    int nums[15] = {1,2,3,4,5,6,7,8,9,12,22,55,1,2,3};
    vector<int>tmp(nums, nums + 15);
    cout << "The original vector is : " << endl;
    copy(tmp.begin(), tmp.end(), ostream_iterator<int>(cout, " "));
    shellSort(tmp);
    cout << "After sort : " << endl;
    copy(tmp.begin(), tmp.end(), ostream_iterator<int>(cout, " "));
}
