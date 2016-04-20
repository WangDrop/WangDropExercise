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
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        if(head == NULL) return NULL;
        ListNode * p = head;
        int i, j;
        for(i = 1; i < m; ++i){
            p = p->next;
        }
        ListNode * q = p;
        for(i = m; i < n; ++i){
            for(j = i; j < n; ++j){
                q = q->next;
            }
            swap(p->val, q->val);
            n--;
            p = p->next;
            q = p;
        }
        return head;
    }
};