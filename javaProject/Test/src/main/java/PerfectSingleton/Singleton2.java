package PerfectSingleton;

import java.math.BigInteger;

/**
 * Created by 12083 on 2016/9/6.
 */
public class Singleton2 {

    private Singleton2(){

    }

    //JVM内部的机制能够保证当一个类被加载的时候，这个类的加载过程是线程互斥的。
    //所以说使用这种方式不用担心线程之间的访问问题
    private static class SingletonFactory{
        private static Singleton2 singleton = new Singleton2();
    }

    public static Singleton2 getInstance(){
        return SingletonFactory.singleton;
    }
}
