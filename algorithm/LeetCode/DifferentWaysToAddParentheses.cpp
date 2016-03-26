/*************************************************************************
	> File Name: DifferentWaysToAddParentheses.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年03月26日 星期六 22时57分47秒
 ************************************************************************/

#include<iostream>
using namespace std;
class Solution {
    public:
    vector<int> diffWaysToCompute(string input) {
        vector<int> result;
        int length = input.length();
        for(int i = 0; i < length; ++i){
            char c = input[i];
            if(c == '+' || c == '-' || c == '*'){
            string inputLeft = input.substr(0, i);     
            string inputRight = input.substr(i+1);
            vector<int>leftResult = diffWaysToCompute(inputLeft);
            vector<int>rightResult = diffWaysToCompute(inputRight);
            for(int j = 0; j < leftResult.size(); ++j){
            for(int k = 0; k < rightResult.size(); ++k){
            if(c == '+')
                result.push_back(leftResult[j] + rightResult[k]);
            else if(c == '-')
                result.push_back(leftResult[j] - rightResult[k]);
            else if(c == '*')
                result.push_back(leftResult[j] * rightResult[k]);                       
                    }                   
                }            
            }       
        }
        if(result.empty())//这一步主要的作用是讲分治得到的最后的字符转换成数字
        result.push_back(stoi(input));
        return result;    
    }
};
