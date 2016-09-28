package PerfectSingleton;

/**
 * Created by 12083 on 2016/9/6.
 */

//Lazy mode
public class Singleton {
    private static Singleton instance;

    private Singleton(){}

    public static Singleton getInstance(){
        if(instance == null){
            synchronized (instance){
                if(instance == null)
                    instance = new Singleton();
            }
        }
        return instance;
    }
}


