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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode * curr = new ListNode(0);
        ListNode * root = curr;
        ListNode * prev = curr;
        int currVal = 0;
        while(l1 != NULL && l2 != NULL){
            currVal = l1->val + l2->val;
            curr->val += currVal;
            curr->next = new ListNode(curr->val/10);
            curr->val%=10;
            prev = curr;
            curr = curr->next;
            l1 = l1->next;
            l2 = l2->next;
        }
        while(l1 != NULL){
            curr->val += l1->val;
            curr->next = new ListNode(curr->val/10);
            curr->val %= 10;
            prev = curr;
            curr = curr->next;
            l1 = l1->next;
        }
        while(l2 != NULL){
            curr->val += l2->val;
            curr->next = new ListNode(curr->val/10);
            curr->val %= 10;
            prev = curr;
            curr = curr->next;
            l2 = l2->next;
        }
        if(curr->val == 0){
            prev->next = NULL;
            delete curr;
        }
        return root;
    }
};