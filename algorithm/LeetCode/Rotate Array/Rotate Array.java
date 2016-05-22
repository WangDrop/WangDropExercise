public class Solution {
    public void rotate(int[] nums, int k) {
        k = k % nums.length;
        rev(nums, nums.length-k, nums.length - 1);
        rev(nums, 0, nums.length-k-1);
        rev(nums, 0, nums.length - 1);
    }
    
    //自己要单独的写一个rev函数
    public void rev(int [] arr, int start, int end){
        int tmp = 0;
        while(start < end){
            tmp = arr[start];
            arr[start] = arr[end];
            arr[end] = tmp;
            start++;
            end--;
        }
    }
}