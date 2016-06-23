package com.test.Thread;

public class RunnableTest implements Runnable{

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Thread t1 = new Thread(new RunnableTest());
		Thread t2 = new Thread(new RunnableTest());
		t1.start();
		t2.start();
	}
	
	public void run() {
		for(int i = 1; i < 10; ++i){
			System.out.println("Thread : " + Thread.currentThread() + i);
		}
	}

}
