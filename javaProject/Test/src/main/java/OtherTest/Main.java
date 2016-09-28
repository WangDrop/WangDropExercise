package OtherTest;

import java.util.ArrayList;
import java.util.Scanner;
import java.util.concurrent.Semaphore;

/**
 * Created by 12083 on 2016/9/20.
 */
public class Main {
    public static void main(String[] args) {
//        Scanner sc = new Scanner(System.in);
//        String s1, s2, tmp;
//        while (sc.hasNext()) {
//            tmp = sc.nextLine();
//            String[] strs = tmp.trim().split(" ");
//            s1 = strs[0];
//            s2 = strs[strs.length - 1];
//            System.out.println("resullt=" + getLCSLength("", ""));
//        }
        Scanner sc = new Scanner(System.in);
        while(sc.hasNext()){
            int num = sc.nextInt();
            System.out.println(calDepth(num) + " " + calLeaf(num));
        }
//        while(sc.hasNext()){
//            String tmp = sc.nextLine();
//            String [] strs = tmp.trim().split(",");
//            strs[0] = strs[0].substring(1);
//            strs[strs.length - 1] = strs[strs.length - 1].substring(0, strs[strs.length - 1].length() - 1);
//            int [] arr = new int[strs.length];
//            for(int i = 0; i < strs.length; ++i){
//                arr[i] = Integer.valueOf(strs[i]);
//            }
//            System.out.println(MoreThanHalfNum(arr));
//        }
    }
    static int calDepth(int nodeNum) {
        int res = 0;
        int init = 1;
        while (init < nodeNum) {
            init *= 2;
            res++;
        }
        return res;
    }

    static int calLeaf(int nodeNum) {
        return (nodeNum + 1) / 2;
    }


    static String getLCSLength(String s, String t) {
        int p = s.length();
        int q = t.length();
        String[][] num = new String[p][q];

        char char1 = ' ';
        char char2 = ' ';

        int len = 0;
        String lcs = new String("");

        for (int i = 0; i < p; i++) {
            for (int j = 0; j < t.length(); j++) {
                char1 = s.charAt(i);
                char2 = t.charAt(j);
                if (char1 != char2) {
                    num[i][j] = "";
                } else {
                    if (i == 0 || j == 0) {
                        num[i][j] = "" + char1;
                    } else {
                        num[i][j] = num[i - 1][j - 1] + char1;
                    }
                    if (num[i][j].length() > len) {
                        len = num[i][j].length();
                        lcs = num[i][j];
                    } else if (num[i][j].length() == len) {
                        lcs = lcs + "," + num[i][j];
                    }
                }
            }
        }
        return lcs.trim().split(",")[0].trim();
    }

    static int MoreThanHalfNum(int[] nums) {
        int count;
        int res;
        int sz = nums.length;
        if (sz == 0) {
            return -1;
        }
        count = 1;
        res = nums[0];
        for (int i = 1; i < sz; ++i) {
            if (nums[i] == res)
                count++;
            else {
                count--;
                if (count == 0) {
                    res = nums[i];
                    count = 1; //这里注意要将计数重新变为1
                }
            }
        }
        count = 0;
        for (int i = 0; i < sz; ++i)
            if (nums[i] == res)
                count++;
        if (count <= sz / 2) //检查数组的有效性，如果数组不满足有
            return -1;   //一个数大于数组长度一半的话就标记无效
        return res;
    }


}
