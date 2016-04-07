class Solution {
public:
    bool isUgly(int num) {
        if(num == 0)
            return false;
        while(num % 2 == 0) num /= 2;//exclude 2 factor
        while(num % 3 == 0) num /= 3;//exclude 3 factor
        while(num % 5 == 0) num /= 5;//exclude 5 factor
        return (num == 1);//is Ugly
    }
};