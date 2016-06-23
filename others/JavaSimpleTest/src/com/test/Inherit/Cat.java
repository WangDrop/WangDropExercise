package com.test.Inherit;

public class Cat implements Friendly{
	public void eat() {
		System.out.println("cat is eating");
	}
	
	@Override
	public void sayHello(){
		System.out.println("miao miao miao ");
	}
	
	@Override
	public void sayGoodBye(){
		System.out.println("cat say goodBye ");
	}
	
	@Override
	protected void finalize(){
		System.out.println("miao miao miao finalize!");
	}
}
