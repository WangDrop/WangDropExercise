public class Solution {
    public boolean isPalindrome(ListNode head) {
        ListNode p = head;
        Stack<ListNode> s = new Stack<ListNode>();
        while (p != null) {
            s.push(p);
            p = p.next;
        }
        while(!s.isEmpty()){
            if(head.val != s.pop().val)
                return false;
            head = head.next;
        }
        return true;
    }
}


public class Solution {
    ListNode helper;
    public boolean isPalindrome(ListNode head) {
        helper = head;
        return isValid(head);
    }

    public boolean isValid(ListNode first){
        if(first == null) return true;
        if(isValid(first.next) == false) return false;
        if(first.val == helper.val){
            helper = helper.next;
            return true;
        }else
            return false;
    }
}