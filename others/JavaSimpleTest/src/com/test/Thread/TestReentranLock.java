package com.test.Thread;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

import org.omg.CORBA.portable.ValueBase;

public class TestReentranLock {
	private int value;
	private Lock lock;
	public TestReentranLock() {
		// TODO Auto-generated constructor stub
		value = 0;
		lock = new ReentrantLock();
	}
	
	public void add() {
		try {
			lock.lock();
			this.value = this.value + 1;
		} catch (Exception e) {
			// TODO: handle exception
			e.printStackTrace();
		}finally{
			lock.unlock();
		}
		
	}
	
	public int getValue() {
		return value;
	}
	
	
	public static void main(String[] args) throws Exception{
		// TODO Auto-generated method stub
		final TestReentranLock testReentranLock = new TestReentranLock();
		Thread t1 = new Thread(new Runnable() {
			
			@Override
			public void run() {
				// TODO Auto-generated method stub
				for(int i = 0; i < 10000; ++i)
					testReentranLock.add();
			}
		});
		
		Thread t2 = new Thread(new Runnable() {
			
			@Override
			public void run() {
				// TODO Auto-generated method stub
				for(int i = 0; i < 10000; ++i)
					testReentranLock.add();
			}
		});
		t1.start();
		t2.start();
//		Thread.currentThread().sleep(1000);
		t1.join();
		t2.join();
		System.out.println("The value now is : " + testReentranLock.getValue());
	}
	
}
