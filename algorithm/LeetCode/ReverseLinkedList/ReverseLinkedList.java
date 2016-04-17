/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */
public class Solution {
    public ListNode reverseList(ListNode head) {
        if(head == null)return null;
        ListNode helper = new ListNode(-1);
        helper.next = head;
        ListNode p = helper;
        ListNode pPre = helper.next;
        ListNode tmp = null;
        while(p.next!=null){
            tmp = p.next;
            p.next = pPre;
            pPre = p;
            p = tmp;
        }
        p.next = pPre;
        helper.next.next = null; //记得将尾节点的下一个指向null
        return p;
    }
}