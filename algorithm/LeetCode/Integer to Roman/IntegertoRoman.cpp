class Solution {
public:
    string intToRoman(int num) {
        vector<int> digitNumber{1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        vector<string> alpha{"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
        string result = "";
        int sz = digitNumber.size();
        for(int i = 0; num != 0; ++i){
            while(num >= digitNumber[i]){
                num -= digitNumber[i];
                result.append(alpha[i]);
            }
        }
        return result;
    }
};