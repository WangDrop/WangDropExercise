class Solution {
public:
    string addBinary(string a, string b) {
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        int len1 = a.length();
        int len2 = b.length();
        string result;
        int flag ,val;
        flag = val = 0;
        int i;
        for(i = 0; i < len1 && i < len2; ++i){
            val = (a[i] - '0') + (b[i] - '0') + flag;
            result.append(1, val % 2 + '0');
            flag = val/2;
        }
        while (i < len1) {
            val = a[i] - '0'+ flag;
            result.append(1, val % 2 + '0');
            flag = val/2;
            ++i;
        }
        while (i < len2 ){
            val = b[i] - '0'+ flag;
            result.append(1, val % 2 + '0');
            flag = val/2;
            ++i;
        }
        cout << "flag " << flag << endl;
        if(flag != 0)
            result.append(1, '1');
        reverse(result.begin(), result.end());
        return result;
    }
};