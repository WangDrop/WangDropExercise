package prodCons;

import org.springframework.aop.ThrowsAdvice;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

/**
 * Created by 12083 on 2016/9/5.
 */
public class Depot {
    private int size;
    private int capacity;
    private Lock lock;
    private Condition fullCondition;
    private Condition emptyCondition;

    public Depot(int size, int capacity) {
        this.size = size;
        this.capacity = capacity;
        this.lock = new ReentrantLock();
        this.fullCondition = this.lock.newCondition();
        this.emptyCondition = this.lock.newCondition();
    }

    public void produce(int left) {
        lock.lock();
        try {
            while (left > 0) {
                if (size >= capacity) {
                    fullCondition.await();
                }
                int inc = capacity - size;
                inc = left > inc ? inc : left;
                size += inc;
                left -= inc;
                System.out.println("Thread " + Thread.currentThread().getName() + " produce " + inc);
                emptyCondition.signalAll();
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            lock.unlock();
        }
    }

    public void consume(int left) {
        lock.lock();
        try {
            while (left > 0) {
                if (size <= 0) {
                    emptyCondition.await();
                }
                int dec = size > left ? left : size;
                size -= dec;
                left -= dec;
                System.out.println("Thread " + Thread.currentThread().getName() + " consume " + dec);
                fullCondition.signalAll();
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            lock.unlock();
        }
    }
}
