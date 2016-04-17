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
    ListNode* reverseList(ListNode* head) {
        if(head == NULL) return NULL;
        ListNode * prev = NULL;
        ListNode * p = head;
        ListNode * next;
        while(p != NULL){
            next = p->next;
            p->next = prev;
            prev = p;
            p = next;
        }
        return prev;
    }
};