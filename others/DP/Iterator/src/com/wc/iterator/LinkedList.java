package com.wc.iterator;

public class LinkedList implements Collection{
	class Node{
		private Object object;
		private Node next;
		public Object getObject() {
			return object;
		}
		public void setObject(Object object) {
			this.object = object;
		}
		public Node getNext() {
			return next;
		}
		public void setNext(Node next) {
			this.next = next;
		}
	}
	Node head = null;
	Node tail = null;
	int size = 0;
	public void add(Object o){
		Node node = new Node();
		node.setObject(o);
		if(tail == null)
			head = tail = node;
		else{
			tail.next = node;
		}
		size++;
	}
	public int size(){
		return size;
	}
	
	public Iterator iterator() {
		return null;
	}
	
	class LinkedListIterator implements Iterator{
		Node currNode = head;
		@Override
		public Object next() {
			Object object = currNode.object;
			currNode = currNode.next;
			return object;
		}

		@Override
		public boolean hasNext() {
			return currNode.next == null;
		}
		
	}
}
