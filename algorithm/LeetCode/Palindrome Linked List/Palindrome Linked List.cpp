/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        ListNode * tmpHead = head;
        stack<int> lt;
        while (tmpHead){
            lt.push(tmpHead->val);
            tmpHead = tmpHead->next;
        }

        while (!lt.empty()){
            if (head->val != lt.top()) return false;
            lt.pop();
            head = head->next;
        }
        return true;
    }
};


//下面的是递归方法
class Solution{
private:
    ListNode * theHead;

public:
    bool isPalindrome(ListNode* head) {
        theHead = head;　　//先将head保存到一个theHead里面，便于与后面的递归了得指针相比较。
        return valid(head);
    }

    bool valid(ListNode * first)
    {
        if (first == NULL) return true;
        if (valid(first->next) == false) return false;
        if (first->val == theHead->val){
            theHead = theHead->next;
            return true;
        }
        else
            return false;
    }
};