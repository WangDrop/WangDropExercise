class Solution {
public:
    bool isHappy(int n) {
        set<int> sample;
        sample.insert(n);
        int s = 0;
        for(;;){
            while(n != 0){
                s += (n % 10) * (n % 10);
                n /= 10;
            }
            if(s == 1)
                return true;
            else{
                if(sample.find(s) != sample.end())
                    return false;
                sample.insert(s);
                n = s;
                s = 0;
            }
        }
    }
};