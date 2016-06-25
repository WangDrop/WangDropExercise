package com.wc.iterator;

public class ArrayList implements Collection{
	Object [] objects = new Object[10];
	int index = 0;
	public void add(Object o) {
		if(index == objects.length){
			Object [] newObjects = new Object[2 * objects.length];
			System.arraycopy(objects, 0, newObjects, 0, objects.length);
			objects = newObjects;
		}
		objects[index++] = o;
	}
	public int size(){
		return index;
	}
	
	class ArrayListIterator implements Iterator{
		private int currIndex = 0;
		@Override
		public Object next() {
			return objects[currIndex++];
		}

		@Override
		public boolean hasNext() {
			return objects[currIndex] != null;
		}
		
	}
	
	public Iterator iterator() {
		return new ArrayListIterator();
	}
}
