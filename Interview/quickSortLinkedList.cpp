struct ListNode{
	ListNode * next;
	int val;
	ListNode(ListNode * _next, int _val) :
		next(_next), val(_val){}
};


//快排链表，使用的是值交换的方式
ListNode * quickSort(ListNode * pBegin, ListNode * pEnd)
{
	if (pBegin != pEnd){
		ListNode * mid = getPartion(pBegin, pEnd);
		quickSort(pBegin, mid);
		quickSort(mid->next, pEnd);
	}
	return pBegin;
}



ListNode * getPartion(ListNode * pHead, ListNode * pEnd)
{
	int key = pHead->val;
	ListNode * p = pHead;
	ListNode * q = pHead->next;
	while (q != pEnd->next){
		if (q->val < key){
			p = p->next;
			swap(p->val, q->val);
		}
		q = q->next;
	}
	swap(pHead->val, p->val);
	return p;
}


