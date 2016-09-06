package prodCons;

/**
 * Created by 12083 on 2016/9/5.
 */
public class ProducerConsumer {
    public static void main(String[] args) {
        Depot depot = new Depot(0, 500);
        new Producer(depot).produce(1000);
        new Consumer(depot).consume(500);
        new Producer(depot).produce(500);
        new Consumer(depot).consume(1000);
    }
}

class Consumer{
    Depot depot;
    public Consumer(Depot depot){
        this.depot = depot;
    }
    public void consume(final int no){
        new Thread(new Runnable() {
            public void run() {
                depot.consume(no);
            }
        }).start();
    }
}

class Producer{
    Depot depot;
    public Producer(Depot depot){
        this.depot = depot;
    }
    public void produce(final int no){
        new Thread(new Runnable() {
            public void run() {
                depot.produce(no);
            }
        }).start();
    }
}