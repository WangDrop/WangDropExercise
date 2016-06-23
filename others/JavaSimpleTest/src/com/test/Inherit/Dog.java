package com.test.Inherit;

public class Dog {
	private int wagDount = ((int)(Math.random() * 5.0)) + 1;
	
	public void sayHello() {
		System.out.println("Wang!");
	}
	
	@Override
	public String toString(){
		return "I'm a doge";
	}
}
