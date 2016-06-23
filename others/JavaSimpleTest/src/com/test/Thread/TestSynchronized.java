package com.test.Thread;

public class TestSynchronized {
	private final static SynObj synObj = new SynObj();
	public static void main(String [] args) {
		final TestSynchronized testSynchronized = new TestSynchronized();
		Thread t1 = new Thread(new Runnable() {
			@Override
			public void run() {
				// TODO Auto-generated method stub
				synchronized (testSynchronized) {
					for(int i = 0; i < 10000; ++i)
						testSynchronized.add();
				}
			}
		});
		
		Thread t2 = new Thread(new Runnable() {
			@Override
			public void run() {
				// TODO Auto-generated method stub
				synchronized (testSynchronized) {
					for(int i = 0; i < 10000; ++i){
						testSynchronized.add();
					}

				}
			}
		});
		t1.start();
		t2.start();
		try {
			Thread.currentThread().sleep(1000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		System.out.println("The total is " + testSynchronized.getCount());
	}
	
	public int getCount() {
		return synObj.getCount();
	}
	
	public void add() {
			synObj.setCount(synObj.getCount() + 1);
	}
}


class SynObj{
	private int count = 0;

	public int getCount() {
		return count;
	}

	public void setCount(int count) {
		this.count = count;
	}
	
}