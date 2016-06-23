package com.wc.entrance;
import java.util.Timer;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

import com.wc.bean.IpInfo;
import com.wc.thread.IpCollectTask;
import com.wc.thread.VoteThread;

public class Vote {
	private BlockingQueue<IpInfo> ipInfoQueue;
	private IpCollectTask ipCollectTask;
	private VoteThread voteThread;
	
	public Vote(){
		ipInfoQueue = new LinkedBlockingQueue<IpInfo>();
		ipCollectTask = new IpCollectTask(ipInfoQueue);
		voteThread = new VoteThread(ipInfoQueue);
	}
	
	public void vote() {
		Timer time = new Timer();
		long delay = 0;
		long period = 60 * 60 * 100; // one hour
		time.scheduleAtFixedRate(ipCollectTask, 0, period);
		
		voteThread.start();
	}
	
	public static void main(String [] args) {
		Vote vote = new Vote();
		vote.vote();
	}
}
