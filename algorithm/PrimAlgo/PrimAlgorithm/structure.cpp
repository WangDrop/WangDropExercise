#include "structure.h"

Pair::Pair(int e, double m) :
edge_weight(m),
adacent_vertex(e) {
	// empty constructor
}

double Pair::weight()const {
	return edge_weight;
}
int Pair::vertex()const {
	return adacent_vertex;
}


Node::Node(Pair e, Node *n) :
element(e),
next_node(n) {
	// empty constructor
}

Pair Node::retrieve() const{
	return element;
}
Node *Node::next() const {
	return next_node;
}


List::List() :list_head(NULL) {
	// empty constructor
}

bool List::empty() const {
	if (list_head == NULL) {
		return true;
	}
	else {
		return false;
	}
}

Node *List::head() const {
	return list_head;

}

Pair List::front() const {

	if (empty()) {
		cout << "error! the list is empty";
	}
	return head()->retrieve();
}


void List::push_front(Pair e) {
	if (empty()) {
		list_head = new Node(e, NULL);
	}
	else {
		list_head = new Node(e, head());
	}

}

Pair List::pop_front() {
	if (empty()) {
		cout << "error! the list is empty";
	}
	Pair e = front();
	Node *ptr = list_head;
	list_head = list_head->next();
	delete ptr;
	return e;

}


void List::print() {
	if (empty()) {
		cout << "empty" << endl;
	}
	else {
		for (Node *ptr = head(); ptr != NULL; ptr = ptr->next())
		{
			cout << "<" << ptr->retrieve().vertex() << " " << ptr->retrieve().weight() << "> ";
		}
		cout << endl;
	}
}


Cell::Cell(bool v, double d, int p) :
visited(v),
distance(d),
parent(p) {
	// empty constructor
}

bool Cell::isvisited() const {
	return visited;
}

double Cell::get_distance()const {
	return distance;
}
int Cell::get_parent()const {
	return parent;
}



