package com.wc.prodCons;

public class ProdCons {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Depot depot = new Depot(1000);
		new Producer(depot).produce(1000);
		new Producer(depot).produce(500);
		new Consumer(depot).consume(1000);
		new Consumer(depot).consume(500);
	}

}


class Consumer{
	private Depot depot;
	public Consumer(Depot depot){
		this.depot = depot;
	}
	public void consume(final int no) { //注意这里如果想要使得内部类可以访问到，那么需要讲这个参数设置为final的
		new Thread(new Runnable() {
			@Override
			public void run() {
				depot.consume(no);
			}
		}, no + "consume thread").start();
	}
}

class Producer{
	private Depot depot;
	public Producer(Depot depot){
		this.depot = depot;
	}
	
	public void produce(final int no) {
		new Thread(new Runnable() {
			@Override
			public void run() {
				depot.produce(no);
			}
		}).start();
	}
}