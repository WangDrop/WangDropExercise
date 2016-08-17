class Solution {
public:
    int LastRemaining_Solution(unsigned int n, unsigned int m)
    {
        if(n==0)
            return -1;
        if(n==1)
            return 0;
        else
            return (LastRemaining_Solution(n-1,m)+m)%n;
    }
};
