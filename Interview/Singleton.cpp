class Singleton{
private:
	Singleton();
	static Singleton * instance;
public:
	static Singleton * getInstance();
};

Singleton* Singleton::instance = nullptr;
Singleton * Singleton::getInstance(){
	if (instance == nullptr)
		instance = new Singleton();
	return instance;
}

//下面是使用Qt实现的一个简单的锁
class SingleTon{
public:
    static SingleTon &getInstance(void)
    {
        //双重检测加锁
        if(!instance){
            QMutexLocker locker(&mutex);
            if(!instance)
                instance = new SingleTon;
        }
        return * instance;
    }
private:
    SingleTon();
    SingleTon(const SingleTon & );
    SingleTon & operator = (const SingleTon &);
    QReadWriteLock internalMutex;
    static QMutex mutex;
    static QAtomicPointer<SingleTon> instance;
};

//初始化静态变量
QMutex SingleTon::mutex;
QAtomicPointer<SingleTon> SingleTon::instance = 0;