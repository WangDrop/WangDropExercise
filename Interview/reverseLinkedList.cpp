#include <iostream>
using namespace std;
struct Node{
	int val;
	Node * next;
};
Node* rever(Node* header){
	if (header == NULL)
		return NULL;
	Node * next = header;
	Node * prev = NULL;
	Node * tmp = NULL;
	while (next != NULL){
		tmp = next->next;
		next->next = prev;
		prev = next;
		next = tmp;
	}
	return prev;
}

int main()
{
	Node * n1 = new Node();
	Node * n2 = new Node();
	Node * n3 = new Node();
	Node * n4 = new Node();
	Node * n5 = new Node();
	n1->val = 1;
	n2->val = 2;
	n3->val = 3;
	n4->val = 4;
	n5->val = 5;
	n1->next = n2;
	n2->next = n3;
	n3->next = n4;
	n4->next = n5;
	n5->next = NULL;
	for (Node * node = n1; node != NULL; node = node->next)
		cout << " " << node->val << " ";
	cout << endl;
	Node * rev = rever(n1);
	for (; rev != NULL; rev = rev->next)
		cout << " " << rev->val << " ";
	system("pause");
}