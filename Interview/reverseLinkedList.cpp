class Solution{
public:
    ListNode * reverseList(ListNode * head){
        if(head == NULL || head->next == NULL)
            return head;
        ListNode * prev = NULL, * curr = head, * tmp = NULL;
        while(curr ->next != NULL){
            tmp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = tmp;
        }
        curr->next = prev;
        return curr;
    }
};