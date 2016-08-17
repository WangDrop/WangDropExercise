- 输入n个整数，找出其中最小的K个数。例如输入4,5,1,6,2,7,3,8这8个数字，则最小的4个数字是1,2,3,4,。
- topK问题，有下面两种思路：
- 1. 最小堆：
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
class Solution {
public:
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
		vector<int>res;
        if(k > input.size())
            return res;
        priority_queue<int, vector<int>, greater<int>> pq;
        for(int i = 0; i < input.size(); ++i)
            pq.push(input[i]);

        for(int i = 0; i < k; ++i){
            res.push_back(pq.top());
        	pq.pop();
        }
    	return res;
    }
};


- 2.冒泡法，但是只冒泡k次

import java.util.ArrayList;
public class Solution {
	public ArrayList<Integer> GetLeastNumbers_Solution(int [] input, int k) {
        ArrayList<Integer> al = new ArrayList<Integer>();
        if (k > input.length) {
            return al;
        }
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < input.length - i - 1; j++) {
                if (input[j] < input[j + 1]) {
                    int temp = input[j];
                    input[j] = input[j + 1];
                    input[j + 1] = temp;
                }
            }
            al.add(input[input.length - i - 1]);
        }
        return al;
    }
}