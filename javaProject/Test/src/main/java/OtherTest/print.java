package OtherTest;

import com.sun.corba.se.spi.ior.iiop.MaxStreamFormatVersionComponent;
import com.sun.org.apache.bcel.internal.generic.INEG;
import com.sun.org.apache.xml.internal.utils.Trie;
import org.omg.CORBA.INTERNAL;
import sun.awt.image.BufferedImageDevice;
import sun.awt.image.ImageWatched;
import sun.reflect.generics.tree.Tree;

import javax.swing.plaf.basic.BasicTreeUI;
import java.io.*;
import java.lang.reflect.Array;
import java.net.ResponseCache;
import java.util.*;

/**
 * Created by 12083 on 2016/9/10.
 */
public class print {
    public ArrayList<ArrayList<Integer>> print(TreeNode root) {
        int count = 0;
        ArrayList<ArrayList<Integer>> lists = new ArrayList<ArrayList<Integer>>();
        if (root == null)
            return lists;
        Stack<TreeNode> s1 = new Stack<TreeNode>();
        Stack<TreeNode> s2 = new Stack<TreeNode>();
        s1.add(root);
        while (!(s1.empty() && s2.empty())) {
            ArrayList<Integer> curr = new ArrayList<Integer>();
            if (!s1.empty()) {
                while (!s1.empty()) {
                    TreeNode n = s1.pop();
                    curr.add(n.val);
                    if (n.left != null) //从左到右
                        s2.add(n.left);
                    if (n.right != null)
                        s2.add(n.right);
                }
            } else {
                while (!s2.empty()) {
                    TreeNode n = s2.pop();
                    curr.add(n.val);
                    if (n.right != null) //从右到左
                        s1.add(n.right);
                    if (n.left != null)
                        s1.add(n.left);
                }
            }
            lists.add(curr);
        }
        return lists;
    }

    //the serilized tree is like 1,2,3,#,#,4,5
    TreeNode deserilize(String str) {
        String[] arr = str.trim().split(",");
        if (arr.length == 0)
            return null;
        TreeNode root = new TreeNode(Integer.valueOf(arr[0]));
        LinkedList<TreeNode> list = new LinkedList<TreeNode>();
        list.add(new TreeNode(Integer.valueOf(arr[0])));
        TreeNode curr = null;
        for (int i = 1; i < arr.length; ++i) {
            curr = list.poll();
            System.out.println(curr.val);
            if (!arr[i].equals("#")) {

                //System.out.println(arr[i]);
                curr.left = new TreeNode(Integer.valueOf(arr[i]));
                list.add(curr.left);
            }
            if (!arr[++i].equals("#")) {

                //System.out.println(arr[i]);
                curr.right = new TreeNode(Integer.valueOf(arr[i]));
                list.add(curr.right);
            }
        }
        return root;
    }


    int count;

    TreeNode kthNode(TreeNode root, int k) {
        if (root.left != null) {
            TreeNode next = kthNode(root.left, k);
            if (next != null) {
                return next;
            }
            if (++count == k)
                return root;
            return kthNode(root.right, k);
        }
        return null;
    }

    public static void main(String[] args) {
        print p = new print();

        int num = p.getMin(200);
        System.out.println(num);
    }

    public int floodFill(int[][] map, int n, int m) {
        boolean[][] passed = new boolean[map.length][map[0].length];
        int[][] count = new int[map.length][map[0].length];
        bfs(map, count, passed, 0, 0, 0);
        return count[n - 1][m - 1];
    }

    void bfs(int[][] map, int[][] count, boolean[][] passed, int curr, int x, int y) {
        if (x >= 0 && x < map.length &&
                y >= 0 && y < map[0].length && map[x][y] == 0 && passed[x][y] == false) {
            passed[x][y] = true;
            count[x][y] = Math.min(count[x][y], curr);
            bfs(map, count, passed, curr + 1, x - 1, y);
            bfs(map, count, passed, curr + 1, x, y - 1);
            bfs(map, count, passed, curr + 1, x, y + 1);
            bfs(map, count, passed, curr + 1, x + 1, y);
        }
    }

    int getMin(int total) {
        int x = 1;
        int sum = 0;
        while (sum < total) {
            sum += x;
            x += 1;
        }
        return x - 1; // 返回的是最坏可能下需要扔的次数
    }


    public String readFile(String fileName) throws FileNotFoundException {
        File file = new File(fileName);
        if (!file.exists()) {
            throw new FileNotFoundException("The file " + fileName + " not found!");
        }
        BufferedReader bf = new BufferedReader(new InputStreamReader(new FileInputStream(file)));
        StringBuilder sb = new StringBuilder();
        String tmp;
        try {
            while ((tmp = bf.readLine()) != null) {
                sb.append(tmp);
                sb.append("\n");
            }
        } catch (IOException ex) {
            ex.printStackTrace();
        }
        return sb.toString();
    }


    int candy(int[] arr) {
        int[] candy = new int[arr.length];
        for (int i = 0; i < candy.length; ++i)
            candy[i] = 1;
        for (int i = 1; i < arr.length; ++i) {
            if (arr[i] > arr[i - 1])
                candy[i] = candy[i - 1] + 1;
        }
        for (int i = candy.length - 2; i >= 0; --i) {
            if (arr[i] > arr[i + 1])
                candy[i] = Math.max(candy[i - 1], candy[i + 1]);
        }
        int total = 0;
        for (int i = 0; i < candy.length; ++i)
            total += candy[i];
        return total;
    }

    int count1Num(int num) {
        int higherNum = 0;
        int lowerNum = 0;
        int currNum = 0;
        int factor = 10;
        int total1Count = 0;
        while (factor / 10 < num) {
            higherNum = num / factor;
            currNum = (num % factor) / (factor / 10);
            lowerNum = num % (factor / 10);

            System.out.println(higherNum + " " + currNum + " " + lowerNum);
            if (currNum == 0) {
                total1Count += higherNum * (factor / 10);
            } else if (currNum == 1) {
                total1Count = total1Count + higherNum * (factor / 10) + lowerNum + 1;
            } else {
                total1Count += (higherNum + 1) * (factor / 10);
            }
            factor *= 10;
        }
        return total1Count;
    }

    int[] findNext(int[] arr) {
        Stack<Integer> s = new Stack<Integer>();
        int next[] = new int[arr.length];
        for (int i = arr.length - 1; i >= 0; i--) {
            if (s.empty()) {
                next[i] = -1;
                s.push(arr[i]);
            } else {
                if (s.peek() > arr[i]) {
                    next[i] = s.peek();
                    s.push(arr[i]);
                } else {
                    while (!s.empty() && s.peek() < arr[i]) {
                        s.pop();
                    }
                    if (s.empty()) {
                        next[i] = -1;
                        s.push(arr[i]);
                    } else {
                        next[i] = s.peek();
                        s.push(arr[i]);
                    }
                }
            }
        }
        return next;
    }


    public static ListNode createList() {
        ListNode node = new ListNode(1);
        ListNode node1 = new ListNode(2);
        ListNode node2 = new ListNode(3);
        ListNode node3 = new ListNode(4);
        ListNode node4 = new ListNode(4);
        node.next = node1;
        node1.next = node2;
        node2.next = node3;
        node3.next = node4;
        return node;
    }

    ListNode getPartion(ListNode begin, ListNode end) {
        if (begin == end || end == null)
            return null;
        ListNode p = begin, q = begin.next;
        while (q != end.next) {
            if (q.val < begin.val) {
                p = p.next;
                swap(p, q);
            }
            q = q.next;
        }
        swap(begin, p);
        return p;
    }

    String removeComments(String curr) {
        StringBuilder builder = new StringBuilder();
        boolean isQuote = false;
        for (int i = 0; i < curr.length(); ++i) {
            if (!isQuote) {
                //now meet the close quote
                if (curr.charAt(i) == '/' && i + 1 < curr.length() && curr.charAt(i + 1) == '/') {
                    while (i < curr.length() && curr.charAt(i) != '\n')
                        i++;
                    continue;
                } else if (curr.charAt(i) == '/' && i + 1 < curr.length() && curr.charAt(i + 1) == '*') {
                    i += 2;
                    while (i < curr.length() && curr.charAt(i) != '*' && i + 1 < curr.length() && curr.charAt(i + 1) != '/')
                        i++;
                    i++;
                    continue;
                } else if (curr.charAt(i) == '"') {
                    builder.append(curr.charAt(i));
                    isQuote = true;
                    continue;
                }
                builder.append(curr.charAt(i));
            } else {
                while (i < curr.length() && curr.charAt(i) != '"')
                    builder.append(curr.charAt(i++));
                builder.append('"');
                isQuote = false;
            }
        }
        return builder.toString();
    }

    public int maxProfit(ArrayList<Integer> arr) {
        if (arr.size() == 0)
            return 0;
        int start = 0, end = 1;
        int maxProfit = 0;
        while (end < arr.size()) {
            if (arr.get(end) < arr.get(start)) {
                start = end;
                end++;
            } else {
                maxProfit = Math.max(maxProfit, arr.get(end) - arr.get(start));
                end++;
            }
        }
        return maxProfit;
    }

    int maxProducts(int[] arr) {
        if (arr.length == 0)
            return 0;
        int maxVal = arr[0], minVal = arr[0];
        int a, b;
        for (int i = 1; i < arr.length; ++i) {
            a = Math.max(maxVal * arr[i], minVal * arr[i]);
            b = Math.min(maxVal * arr[i], minVal * arr[i]);
            maxVal = Math.max(maxVal, a);
            minVal = Math.min(minVal, b);
        }
        return Math.max(maxVal, minVal);
    }

    int getChanges(int[] arr, int n) {
        Arrays.sort(arr);
        int dp[] = new int[n + 1];
        dp[0] = 0;
        for (int i = 1; i < dp.length; ++i) {
            dp[i] = n + 1;
        }
        for (int i = 0; i < arr.length; ++i) {
            for (int j = 0; j <= n; ++j) {
                if (j >= arr[i])
                    dp[j] = Math.min(dp[j], dp[j - arr[i]] + 1);
            }
        }
        return dp[n];
    }

    int[] getNext(String str) {
        int[] next = new int[str.length() + 1];
        next[0] = next[1] = 0;
        int j = 0;
        for (int i = 1; i < str.length() - 1; ++i) {
            while (j > 0 && str.charAt(i) != str.charAt(j)) {
                j = next[j];
            }
            if (str.charAt(i) == str.charAt(j))
                j++;
            next[i + 1] = j;
        }
        return next;
    }

    int kmp(String str, String substr) {
        int[] next = getNext(substr);
        int j = 0;
        for (int i = 0; i < str.length(); ++i) {
            while (j > 0 && str.charAt(i) != substr.charAt(j))
                j = next[j];
            if (str.charAt(i) == substr.charAt(j))
                j++;
            if (j == substr.length())
                return i - (substr.length() - 1);
        }
        return -1;// can't find the substr
    }


    public int wigglemaxLength(ArrayList<Integer> list) {
        int f = 1, d = 1;
        for (int i = 1; i < list.size(); ++i) {
            if (list.get(i) < list.get(i - 1))
                d = f + 1;
            else if (list.get(i) > list.get(i - 1))
                f = d + 1;
        }
        return Math.min(list.size(), Math.max(f, d));
    }

    private void swap(ListNode node1, ListNode node2) {
        int tmp = node1.val;
        node1.val = node2.val;
        node2.val = tmp;
    }

    ListNode quickSortLinkedList(ListNode begin, ListNode end) {
        ListNode mid = getPartion(begin, end);
        if (mid != null) {
            quickSortLinkedList(begin, mid);
            quickSortLinkedList(mid.next, end);
        }
        return begin;
    }

    Result getMaxDis(TreeNode node) {
        if (node == null)
            return new Result(-1, 0);
        Result resLeft = getMaxDis(node.left);
        Result resRight = getMaxDis(node.right);
        Result res = new Result(0, 0);
        res.nMaxDepth = Math.max(resLeft.nMaxDepth, resRight.nMaxDepth) + 1;
        res.nMaxDistance = Math.max(Math.max(resLeft.nMaxDistance, resRight.nMaxDistance), resLeft.nMaxDepth + resRight.nMaxDepth + 2);
        return res;
    }

    TreeNode lca(TreeNode root, TreeNode p, TreeNode q) {
        if (root == null)
            return null;
        if (root == p || root == q)
            return root;
        TreeNode left = lca(root.left, p, q);
        TreeNode right = lca(root.right, p, q);
        if (left != null && right != null)
            return root;
        if (left != null)
            return left;
        return right;
    }

    int minDepth(TreeNode root) {
        if (root == null)
            return 0;
        int leftDep = minDepth(root.left);
        int rightDep = minDepth(root.right);
        if (leftDep == 0 && rightDep == 0)
            return 1;
        if (leftDep == 0)
            leftDep = Integer.MAX_VALUE;
        if (rightDep == 0)
            rightDep = Integer.MAX_VALUE;
        return Math.min(leftDep, rightDep) + 1;
    }

    int lengthOfLis(int[] nums) {
        if (nums.length == 0)
            return 0;
        int[] dp = new int[nums.length];
        for (int i = 0; i < nums.length; ++i) {
            dp[i] = 1;
            for (int j = 0; j < i; ++j) {
                if (nums[j] < nums[i])
                    dp[i] = Math.max(dp[i], dp[j] + 1);
            }
        }
        return dp[nums.length - 1];
    }

    int countNode(TreeNode root) {
        if (root == null)
            return 0;
        int leftDep = 0, rightDep = 0;
        TreeNode left = root, right = root;
        while (left != null) {
            left = left.left;
            leftDep++;
        }
        while (right != null) {
            right = right.right;
            rightDep++;
        }
        if (leftDep == rightDep)
            return (1 << leftDep) - 1;
        else
            return countNode(root.left) + countNode(root.right) + 1;
    }

    void bfs(TreeNode root, int depth, ArrayList<ArrayList<Integer>> arr) {
        if (root == null)
            return;
        if (arr.size() < depth) {
            ArrayList<Integer> list = new ArrayList<Integer>();
            list.add(root.val);
            arr.add(list);
        } else {
            arr.get(depth - 1).add(root.val);
        }
        if (root.left != null)
            bfs(root.left, depth + 1, arr);
        if (root.right != null)
            bfs(root.right, depth + 1, arr);
    }

    int numTrees(int n) {
        if (n == 0)
            return 0;
        int[] arr = new int[n + 1];
        arr[0] = 1;
        for (int i = 1; i <= n; ++i) {
            if (i < 3) {
                arr[i] = i;
            } else {
                for (int j = 0; j < i; ++j) {
                    arr[i] += arr[j] * arr[i - j - 1];
                }
            }
        }
        return arr[n];
    }

    ArrayList<TreeNode> genTrees(int n) {
        return createNodes(1, n);
    }

    ArrayList<TreeNode> createNodes(int start, int end) {
        ArrayList<TreeNode> res = new ArrayList<TreeNode>();
        if (start > end) {
            res.add(null);
            return res;
        }
        for (int i = start; i <= end; ++i) {
            ArrayList<TreeNode> leftNodes = createNodes(start, i - 1);//the node value is i - 1
            ArrayList<TreeNode> rightNodes = createNodes(i + 1, end);
            for (int j = 0; j < leftNodes.size(); ++j) {
                for (int k = 0; k < rightNodes.size(); ++k) {
                    TreeNode curr = new TreeNode(i);
                    curr.left = leftNodes.get(j);
                    curr.right = rightNodes.get(k);
                    res.add(curr);
                }
            }
        }
        return res;
    }


    TreeNode p = null, q = null;
    TreeNode prev = null;

    void tranverse(TreeNode root) {
        if (root == null)
            return;
        tranverse(root.left);
        if (prev != null && prev.val > root.val) {
            if (p == null)
                p = prev;
            q = root; //watch
        }
        prev = root;
        tranverse(root.right);
    }

    boolean canJump(int[] arr) {
        int reachable = 0;
        for (int i = 0; i < arr.length; ++i) {
            if (i > reachable) return false;
            reachable = Math.max(i + arr[i], reachable);
        }
        return true;
    }


    void recoverTree(TreeNode root) {
        tranverse(root);
        int tmp = p.val;
        p.val = q.val;
        q.val = tmp;
    }

    ListNode rotateList(ListNode node, int k) {
        ListNode p = node, q = null;
        while (p.next != null) {
            if (k == 0)
                q = node;
            p = p.next;
            k--;
            if (k < 0)
                q = q.next;
        }
        p.next = node;
        ListNode res = q.next;
        q.next = null;
        return res;
    }

    int perfectSquare(int n) {
        int[] dp = new int[n + 1];
        for (int i = 1; i <= n; ++i)
            dp[i] = i; //注意pf数字最大只可能是i
        for (int i = 4; i <= n; ++i) {
            for (int j = 1; (double) j <= Math.sqrt(i); ++j) {
                if (j * j == i)
                    dp[i] = 1;
                else
                    dp[i] = Math.min(dp[i], dp[i - j * j] + 1);
            }
        }
        return dp[n];
    }

    int packages(int[] weight, int[] value, int maxWeight) {
        int[] dp = new int[maxWeight + 1];
        for (int i = 0; i < weight.length; ++i) {
//            for (int j = maxWeight; j >= weight[i]; --j) {
//                dp[j] = Math.max(dp[j - weight[i]] + value[i], dp[j]);
//            }

            for (int j = 0; j <= maxWeight; ++j) {
                if (j >= weight[i])
                    dp[j] = Math.max(dp[j - weight[i]] + value[i], dp[j]);
            }
        }
        return dp[maxWeight];
    }

    boolean validSudoku(char[][] board) {
        boolean[][] testRow = new boolean[board.length][board[0].length];
        boolean[][] testCol = new boolean[board.length][board[0].length];
        boolean[][] testBlock = new boolean[board.length][board[0].length];
        for (int i = 0; i < board.length; ++i) {
            for (int j = 0; j < board[0].length; ++j) {
                if (board[i][j] != '.') {
                    int num = board[i][j] - '0';
                    if (testRow[i][num] == true) return false;
                    else testRow[i][num] = true;
                    if (testCol[j][num] == true) return false;
                    else testCol[j][num] = true;
                    if (testBlock[i - i % 3 + j / 3][num] == true) return false;
                    else testBlock[i - i % 3 + j / 3][num] = true;
                }
            }
        }
        return true;
    }

    boolean solveSudoku(char[][] board) {

        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                if (board[row][col] == '.') {
                    for (char c = '1'; c <= '9'; ++c) {
                        board[row][col] = c;
                        if (validSudoku(board)) {
                            if (solveSudoku(board))
                                return true;
                        }
                        board[row][col] = '.';
                    }
                    return false;// 这种方式不可行
                }
            }
        }
        return true;
    }

    int findElement(int[] arr, int target) {
        int start = 0, end = arr.length - 1;
        int mid = -1;
        while (start <= end) {
            mid = (start + end) / 2;
            if (arr[mid] == target)
                return mid;
            else if (arr[mid] < target) {
                if (arr[end] > arr[mid] && arr[end] < target)
                    end = mid - 1;
                else
                    start = mid + 1;
            } else {
                if (arr[end] > arr[mid] && arr[end] > target) { //更小的出现在左边
                    end = mid - 1;
                } else
                    start = mid + 1;
            }
        }
        return mid;
    }

    int maxNum(int a, int b) {
        b = a - b;
        System.out.println((b >> 31) + "***");
        a -= b & (b >> 31);
        return a;
    }

    int[] getPV(char[] A, char[] guess) {
        HashMap<Character, Integer> map = new HashMap<Character, Integer>();
        int p = 0, v = 0;
        for (int i = 0; i < A.length; ++i) {
            if (A[i] == guess[i]) {
                p++;
            } else {
                if (!map.containsKey(A[i]))
                    map.put(A[i], 1);
                else
                    map.put(A[i], map.get(A[i]) + 1);
            }
        }
        for (int i = 0; i < guess.length; ++i) {
            if (A[i] != guess[i]) {
                if (map.containsKey(guess[i])) {
                    if (map.get(guess[i]) != 0) {
                        map.put(guess[i], map.get(guess[i]) - 1);
                        v++;
                    }
                }
            }
        }
        return new int[]{p, v};
    }

    //单论小写字母
    void buildTrie(String str, TrieNode root) {
        if (root == null)
            return;
        TrieNode curr = root;
        char[] arr = str.toCharArray();
        for (int i = 0; i < arr.length; ++i) {
            if (curr.nodes[arr[i] - 'a'] == null) {
                curr.nodes[arr[i] - 'a'] = new TrieNode();
            }
            curr = curr.nodes[arr[i] - 'a'];
            if (i == arr.length - 1) {
                curr.isSentence = true;
                curr.count++;
            }
        }
    }

    int findStr(String str, TrieNode root) {
        if (root == null)
            return 0;
        TrieNode curr = root;
        char arr[] = str.toCharArray();
        for (int i = 0; i < arr.length; ++i) {
            if (curr.nodes[arr[i] - 'a'] == null)
                return 0;
            curr = curr.nodes[arr[i] - 'a'];
            if (arr.length - 1 == i && curr.isSentence) {
                return curr.count;
            }
        }
        return 0;
    }


}

class TrieNode {
    TrieNode nodes[];
    boolean isSentence; //称为一个句子的话仍然可能会有子节点
    int count; //表示当前节点实际上代表了多少个相同的单词

    public TrieNode() {
        nodes = new TrieNode[26]; //26个英文字母
        isSentence = false;
        count = 0;

    }
}

class TreeNode {
    TreeNode left;
    TreeNode right;
    int val;

    public TreeNode(int val) {
        this.val = val;
    }

    TreeNode(TreeNode left, TreeNode right, int val) {
        this.left = left;
        this.right = right;
        this.val = val;
    }
}

class ListNode {
    int val;
    ListNode next;

    public ListNode(int val) {
        this.val = val;
    }

    public ListNode(int val, ListNode next) {
        this.val = val;
        this.next = next;
    }
}

class Result {
    int nMaxDistance;
    int nMaxDepth;

    public Result(int nMaxDistance, int nMaxDepth) {
        this.nMaxDistance = nMaxDistance;
        this.nMaxDepth = nMaxDepth;
    }
}

