package com.wc.thread;
import com.wc.bean.IpInfo;

import java.io.IOException;
import java.util.concurrent.BlockingQueue;

import javax.xml.transform.Templates;

import org.apache.http.HttpEntity;
import org.apache.http.HttpHost;
import org.apache.http.HttpResponse;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.client.params.HttpClientParams;
import org.apache.http.conn.params.ConnRoutePNames;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.params.HttpConnectionParams;
import org.apache.http.params.HttpParams;
import org.apache.http.util.EntityUtils;



public class VoteThread extends Thread{
	private BlockingQueue<IpInfo> ipInfoQueue;
	public VoteThread(BlockingQueue<IpInfo> ipInfoQueue){
		this.ipInfoQueue = ipInfoQueue;
	}
	
	@Override
	public void run(){
		HttpClient client = new DefaultHttpClient();
		HttpParams params = client.getParams();
		HttpConnectionParams.setConnectionTimeout(params, 10000); //设置连接的超时时间
		HttpConnectionParams.setSoTimeout(params, 5000);//设置socket的超时时间
		HttpResponse response = null;
		HttpGet get = null;
		HttpEntity entity = null;
		HttpHost proxy = null;
		while(true){
			IpInfo ipInfo = null;
			try{
				ipInfo = ipInfoQueue.take();
			}catch(InterruptedException e){
				e.printStackTrace();
			}
			
			proxy = new HttpHost(ipInfo.getIpAddress(), ipInfo.getPort());

			client.getParams().setParameter(ConnRoutePNames.DEFAULT_PROXY, proxy);
			get = new HttpGet("http://www.hnxdf.com/vote/iRadio_vote.asp?VoTeid=186");
			System.out.println("hello!");
			get.addHeader("Host", "www.hnxdf.com");
			get.addHeader("User-Agent", "360-Chrome");
			try{
				response = client.execute(get);
				entity = response.getEntity();
				byte [] bytes = EntityUtils.toByteArray(entity);
				String tmp = new String(bytes, "gbk");
				byte [] contentData = tmp.getBytes("utf-8");
				System.out.println(new String(contentData));
				System.out.println("----------------------");
			}catch(ClientProtocolException e){
				e.printStackTrace();
			}catch(IOException e){
				e.printStackTrace();
			}
		}
			
	}
}
