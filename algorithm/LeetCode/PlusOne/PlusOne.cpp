vector<int> plusOne(vector<int>& digits) {
        reverse(digits.begin(), digits.end());
        int sz = digits.size();
        int flag = 0;
        for(int i = 0; i< sz; ++i){
            int val = digits[i] + flag;
            digits[i] %= val;
            flag = val/10;
        }
        if(flag != 10)
            digits.push_back(flag);
        reverse(digits.begin(), digits.end());
        return digits;
    }