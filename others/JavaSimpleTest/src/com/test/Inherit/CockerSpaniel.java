package com.test.Inherit;

public class CockerSpaniel extends Dog implements Friendly{
	private int woofCount = ((int) (Math.random() * 4.0)) + 1;
    private int wimperCount = ((int) (Math.random() * 3.0)) + 1;
    
    @Override
    public void sayHello() {
		super.sayHello();
		System.out.println("The cockerSpaniel wangwang");
    }
    
    @Override
    public void sayGoodBye(){
    	System.out.println("Wimper");
    	System.out.print("CockerSpaniel say goodBye	");
    }
    
}
