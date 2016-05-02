class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        set<int>tmpSet(nums.begin(), nums.end());//因为set已经排好序了，所以用set
        int i = 0;
        set<int>::iterator sItor;
        if((sItor = (tmpSet.find(target))) == tmpSet.end())//不在set中的话，就先插入
            sItor = tmpSet.insert(target);
        for(auto itor = tmpSet.begin(); itor != it.first; ++itor){
            i++;   
        return i;
    }
};