class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
    int minVal = INT_MAX;
    int i = 0, j = 0;
    int currSum = 0;
    int sz = nums.size();
    while (currSum < s && j < sz){
        currSum += nums[j++];
    }
    j--;
    while (1){
        while (i <= j && currSum >= s){
            minVal = min(minVal, j - i + 1);
            currSum -= nums[i++];
        }
        while (j < sz - 1 && currSum < s){
            currSum += nums[++j];
        }
        if (currSum < s)
            return minVal == INT_MAX ? 0 : minVal;
    }
    if(minVal == INT_MAX)
        return 0;
    return minVal;
}

};