package com.wc.prodCons;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.Lock;

public class Depot {
	private int size;
	private int capacity;
	private Lock lock;
	private Condition fullCondition;
	private Condition emptyCondition;
	
	public Depot(int capacity) {
		this.capacity = capacity;
		lock = new ReentrantLock();
		fullCondition = lock.newCondition();
		emptyCondition = lock.newCondition();
	}
	
	public void produce(int no) {
		lock.lock();
		int left = no;
		try{
			while(left > 0){
				while(size >= capacity){
					System.out.println("CurrentThread : " + Thread.currentThread() + "before await!");
					fullCondition.await();
					System.out.println("CurrentThread : " + Thread.currentThread() + "after await!");
				}
				int inc = (capacity - size) >= left ? left : capacity - size;
				left -= inc;
				size += inc;
				System.out.println("CurrentThread : " + Thread.currentThread() + " produced " + inc);
				emptyCondition.signal();
			}
		}catch(InterruptedException e){
			e.printStackTrace();
		}finally{
			lock.unlock();
		}
	}
	
	public void consume(int no) {
		lock.lock();
		int left = no;
		try{
			while(left > 0){
				while(size <= 0){
					System.out.println("CurrentThread : " + Thread.currentThread() + "before consumer await!");
					emptyCondition.await();
					System.out.println("CurrentThread : " + Thread.currentThread() + "after consumer await!");
				}
				int dec = size < left ? size : left;
				left -= dec;
				size -= dec;
				System.out.println("CurrentThread : " + Thread.currentThread() + " consume " + dec);
				fullCondition.signal();
			}
		}catch(InterruptedException e){
			e.printStackTrace();
		}finally{
			lock.unlock();
		}
	}
}
