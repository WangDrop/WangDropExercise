package com.test.Inherit;

public class TestClass {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Dog dog = new CockerSpaniel();
        dog.sayHello();
        Friendly fr = (Friendly) dog;
        fr.sayHello();
        fr = new Cat();
        fr.sayGoodBye();
	}

}
