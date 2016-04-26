/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */
public class Solution {
    public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
        ListNode tmp = new ListNode(0);
        ListNode head = tmp;
        int carry = 0;
        while(l1!=null || l2!=null || carry != 0){
            int val = ((l1 != null)?l1.val:0) + ((l2!=null)?l2.val:0) + carry;
            carry = carry/10 + val/10;
            val %= 10;
            tmp.next = new ListNode(val);
            tmp = tmp.next;
            l1 = l1!=null ? l1.next : l1;
            l2 = l2!=null ? l2.next : l2;
        }
        return head.next;
    }
}