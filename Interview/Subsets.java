package com.wc.day0801;

import java.util.Arrays;
import java.util.List;
import java.util.ArrayList;

public class Subsets {
	public static void main(String[] args) {
		int nums[] = new int[] { 1, 2, 3, 4, 5 };
		System.out.println(new Subsets().getSubsets(nums));
	}

	public List<List<Integer>> getSubsets(int[] nums) {
		Arrays.sort(nums);
		List<List<Integer>> ret = new ArrayList<List<Integer>>();
		List<Integer> curr = new ArrayList<Integer>();
		dfs(ret, curr, 0, nums, nums.length);
		return ret;
	}

	void dfs(List<List<Integer>> ret, List<Integer> curr, int index,
			int[] nums, int len) {
		if (index > len)
			return;
		else if (index == len) {
			ret.add(new ArrayList<Integer>(curr));
		} else {
			ret.add(new ArrayList<Integer>(curr));
			for (int i = index; i < len; ++i) {
				curr.add(nums[i]);
				dfs(ret, curr, i + 1, nums, len);
				curr.remove((Integer) nums[i]);
			}
		}
	}
}
