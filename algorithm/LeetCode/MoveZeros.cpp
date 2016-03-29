#include <vector>
using namespace std;
class Solution{
public:
    void moveZeros(vector<int> & nums){
        auto sz = nums.size();
        int pos = 0;
        for (int i = 0; i < sz; ++i){
            if (nums[i] != 0)
                nums[pos++] = nums[i];
        }
        for (int i = pos; i < sz; ++i)
            nums[i] = 0;
    }
};
