package com.test.Thread;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class ThreadPollTest {
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		TestThread testThread = new TestThread();
		Thread t1 = new Thread(testThread);
		Thread t2 = new Thread(testThread);
		ExecutorService pool = Executors.newFixedThreadPool(10); //静态方法，产生一个大小为10的线程池子
		pool.submit(t1);
		pool.submit(t2);
		
	}

}

class TestThread implements Runnable{
	public void run() {
		for(int i = 0; i < 50; ++i){
			System.out.println("Thread: " + Thread.currentThread() + ":" + i);
		}
	}
}