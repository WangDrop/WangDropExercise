class Solution {
public:
    bool isPalindrome(string s) {
        if (s.size() == 0)
            return true;
        int end = s.size() - 1;
        int beg = 0;
        while (beg < end){
            while (!isalpha(s[beg]) && !isdigit(s[beg])){
                if(beg < end)
                    beg++;
                else
                    return true;
            }
            while (!isalpha(s[end]) && !isdigit(s[end])){
                if(end > beg)
                    end--;
                else
                    return true;
            }
            if (toupper(s[beg]) == toupper(s[end])){
                beg++, end--;
            }
            else{
                return false;
            }
        }
        return true;
    }
};