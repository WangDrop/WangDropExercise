package com.wc.thread;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.TimerTask;
import java.util.concurrent.BlockingDeque;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingDeque;

import javax.print.DocFlavor.STRING;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

import com.wc.bean.IpInfo;

public class IpCollectTask extends TimerTask {
	private BlockingQueue<IpInfo> ipInfoQueue;
	private List<IpInfo> historyIpList;
	
	public IpCollectTask(BlockingQueue<IpInfo> ipInfoQueue){
		this.ipInfoQueue = ipInfoQueue;
		this.historyIpList = new ArrayList<IpInfo>();
	}
	
	public void getXiCiDaiLiIpList() {
		String url = "http://www.xicidaili.com/";
		String host = "www.xicidaili.com";
		Document document = getDocumentByUrl(url, host);
		ParseXiCiDaiLiIpLists(document);
	}
	
	/**
	 * 解析页面ip的信息
	 * @param doc
	 * @return void
	 */
	public void ParseXiCiDaiLiIpLists(Document doc){
		Elements elementLists = doc.getElementsByTag("tbody"); //有表格，所以要用tbody来抓取
		Element tbody = elementLists.get(0);//
		//System.out.println("" + tbody);
		Elements eleChildLists = tbody.children();
		Element ele = null;
		for(int i = 0; i < eleChildLists.size(); ++i){
			if((i % 22 == 0) || (i % 22 == 1)) //这里是为什么
				continue;
			ele = eleChildLists.get(i);
			Elements childrenList = ele.children();
			String ipAddress = childrenList.get(1).text();
			int port = Integer.parseInt(childrenList.get(2).text());
			String location = childrenList.get(3).text();
			String anonymousType = childrenList.get(4).text();
			String type = childrenList.get(5).text();
			String confirmTime = childrenList.get(7).text();
			System.out.println("the info is: " + ipAddress + port + location + anonymousType + type + confirmTime);
			IpInfo ipInfo = new IpInfo(ipAddress, port, location, anonymousType, type, confirmTime);
			putIpInfo(ipInfo);
		}
	}
	
	/**
	 * 将ip信息放到队列以及历史记录中
	 * @ ipInfo : ip地址信息
	 */
	private void putIpInfo(IpInfo ipInfo) {
		if(!historyIpList.contains(ipInfo)){//你是记录中不包括ip信息的话，就加到里面去
			//加入BlockQueue中
			try{
				ipInfoQueue.put(ipInfo);
			}catch(InterruptedException e){
				e.printStackTrace();
			}
			//随后加入历史记录中
			historyIpList.add(ipInfo);
		}
	}
	
	/**
	 * 解析快代理页面上的ip信息
	 * @param doc
	 */
	private void parseKuaiDaiLiIpLists(Document document){
		Elements eleListsElements = document.getElementsByTag("tbody");
		Element tbody = eleListsElements.get(0); //得到tbody
		Elements trListsElements = tbody.children(); //获取页面山的十条记录
		for(Element trElement : trListsElements){
			Elements tdElements = trElement.children();
			String ipAddress = tdElements.get(0).text();
			int port = Integer.parseInt(tdElements.get(1).text());
			String anonymousType = tdElements.get(2).text();
			String type = tdElements.get(3).text();
			String getPostSupport = tdElements.get(4).text();
			String location = tdElements.get(5).text();
			String responseSpeed = tdElements.get(6).text();
			String confirmTime = tdElements.get(7).text();
			
			IpInfo ipInfo = new IpInfo(ipAddress, port, anonymousType, type, getPostSupport, location, responseSpeed, confirmTime);
			
			putIpInfo(ipInfo);
		}
	}
	
	/**
	 * 得到快代理所有页面上的Ip地址
	 */
	private void getKuaiDaiLiList(){
		String baseUrl = "http://www.kuaidaili.com/proxylist/";
		String targetUrl = "";
		String host = "www.kuaidaili.com";
		Document doc = null;

		for(int i = 1; i <= 10; ++i){	
			doc = getDocumentByUrl(baseUrl + i + "/", host);
			parseKuaiDaiLiIpLists(doc);
			fallSleep(1);
		}
	}
	
	/**
	 * 分页面解析kuaidaili的free页面上的ip
	 */
	private void getKuaiDaiLiFreeLists(){
		String baseUrl = "http://www.kuaidaili.com/free/inha/";
		String targetUrl = "";
        String host = "www.kuaidaili.com";
        Document doc = getDocumentByUrl(baseUrl, host);
        //解析IP信息
        parseKuaiDaiLiIpLists(doc);
        //通过listnav来解析表下面的页面选择，以及页面总数
        Element listNav =  doc.getElementById("listnav");
        //获取listNav下面的list表
        Elements listNavElement = listNav.children().get(0).children();
        //获取含有多少页子元素
        Element pageNumElement = listNavElement.get(listNavElement.size() - 2);
        //解析页数
        int pageNumber = Integer.parseInt(pageNumElement.text());
        //经过地址拼接得到其他页面的访问地址
        System.out.println("Hello world!!");
        for(int index = 1; index <= pageNumber; ++index){
        	targetUrl = baseUrl + index;
        	System.out.println("targetUrl : " + targetUrl);
        	//doc = getDocumentByUrl(targetUrl, host);
        	//parseKuaiDaiLiIpLists(doc);
        	//休眠一秒
        	fallSleep(1);
        }
	}
	

	/**
	 * 根据url以及host来获取页面信息
	 * @param url
	 * @param host
	 * @return Document
	 */
	private Document getDocumentByUrl(String url, String host){
		Document document = null;
		try{
			document = Jsoup.connect(url).header("User-Agent", "360 Chrome").header("Host", host).timeout(5000).get();
		}catch(IOException e){
			e.printStackTrace();
		}
		return document;
	}
	
	/**
	 * 休眠1秒
	 */
	private void fallSleep(long seconds){
		try{
			Thread.sleep(1000 * seconds);
		}catch(InterruptedException e){
			e.printStackTrace();
		}
	}
	
	@Override
	public void run(){
		System.out.print("Ip Collecting process is now runnig!");
		//getKuaiDaiLiFreeLists();
		//getKuaiDaiLiList();
		getXiCiDaiLiIpList();
	}
	
	
	/**
	 * 
	 * @return the blocking queue of the ip info
	 */
	public BlockingDeque<IpInfo> getIpInfoQueue(){
		return (BlockingDeque<IpInfo>) ipInfoQueue;
	}

	public static void main(String [] args) {
		BlockingDeque<IpInfo> queue = new LinkedBlockingDeque<IpInfo>();
		IpCollectTask task = new IpCollectTask(queue);
		Thread thread = new Thread(task);
		thread.start();
		try{
			Thread.sleep(30 * 1000);
		}catch(InterruptedException e){ 
			e.printStackTrace();
		}
		System.out.println("queue size is " + queue.size());
		try{
			while (!queue.isEmpty()) {
				System.out.println(queue.take());
			}
		}catch(InterruptedException e){
			e.printStackTrace();
		}
		System.out.println("History Ip List size is " + task.historyIpList.size());
	}
}
