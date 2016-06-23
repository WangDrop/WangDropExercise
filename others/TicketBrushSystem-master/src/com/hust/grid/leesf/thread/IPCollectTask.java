package com.hust.grid.leesf.thread;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.TimerTask;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

import com.hust.grid.leesf.bean.IpInfo;

public class IPCollectTask extends TimerTask {
	private BlockingQueue<IpInfo> ipInfoQueue; // 杩炴帴鐢熶骇鑰呬笌娑堣垂鑰呯殑闃诲闃熷垪
	private List<IpInfo> historyIpLists; // 璁板綍宸茬粡鑾峰彇鐨刬p淇℃伅

	public IPCollectTask(BlockingQueue<IpInfo> ipInfoQueue) {
		this.ipInfoQueue = ipInfoQueue;
		this.historyIpLists = new ArrayList<IpInfo>();
	}

	/**
	 * 鑾峰彇www.xicidaili.com鐨刬p鍦板潃淇℃伅
	 */
	public void getXiCiDaiLiIpLists() {
		String url = "http://www.xicidaili.com/";
		String host = "www.xicidaili.com";
		Document doc = getDocumentByUrl(url, host);
		// 瑙ｆ瀽椤甸潰鐨刬p淇℃伅
		parseXiCiDaiLiIpLists(doc);
	}
	
	/**
	 * 瑙ｆ瀽椤甸潰鐨刬p淇℃伅 
	 * @param doc
	 */
	public void parseXiCiDaiLiIpLists(Document doc) {
		Elements eleLists = doc.getElementsByTag("tbody");
		Element tbody = eleLists.get(0); // 鑾峰彇tbody
		Elements trLists = tbody.children();
		Element ele = null;
		for (int i = 0; i < trLists.size(); i++) {
			if ((i % 22 == 0) || (i % 22 == 1)) { // 鍘绘帀涓嶇鍚堟潯浠剁殑椤�				continue;
			}
			ele = trLists.get(i);
			Elements childrenList = ele.children();
			String ipAddress = childrenList.get(1).text();
			int port = Integer.parseInt(childrenList.get(2).text());
			String location = childrenList.get(3).text();
			String anonymousType = childrenList.get(4).text();
			String type = childrenList.get(5).text();
			String confirmTime = childrenList.get(6).text();
			
			IpInfo ipInfo = new IpInfo(ipAddress, port, location,
					anonymousType, type, confirmTime);			
			putIpInfo(ipInfo);
			
		}
	}
	
	/**
	 * 灏唅p淇℃伅鏀惧叆闃熷垪鍜屽巻鍙茶褰曚腑
	 * @param ipInfo
	 */
	private void putIpInfo(IpInfo ipInfo) {
		if (!historyIpLists.contains(ipInfo)) { // 鑻ュ巻鍙茶褰曚腑涓嶅寘鍚玦p淇℃伅锛屽垯鍔犲叆闃熷垪涓�			// 鍔犲叆鍒伴樆濉為槦鍒椾腑锛岀敤浣滅敓浜ц�
			try {
				ipInfoQueue.put(ipInfo);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			// 鍔犲叆鍘嗗彶璁板綍涓�			historyIpLists.add(ipInfo);
		}
	}
	
	/**
	 * 鏍规嵁缃戦〉Document瑙ｆ瀽鍑篿p鍦板潃淇℃伅
	 * @param doc
	 */
	private void parseKuaiDaiLiIpLists(Document doc) {
		Elements eleLists = doc.getElementsByTag("tbody");
		Element tbody = eleLists.get(0); // 鑾峰彇tbody
		Elements trLists = tbody.children(); // 鑾峰彇鍗佹潯ip璁板綍
		for (Element tr : trLists) { // 閬嶅巻tr
			Elements tdElements = tr.children(); // tr涓殑td鍖呭惈浜嗗叿浣撶殑淇℃伅
			String ipAddress = tdElements.get(0).text();
			int port = Integer.parseInt(tdElements.get(1).text());
			String anonymousType = tdElements.get(2).text();
			String type = tdElements.get(3).text();
			String getPostSupport = tdElements.get(4).text();
			String location = tdElements.get(5).text();
			String responseSpeed = tdElements.get(6).text();
			String confirmTime = tdElements.get(7).text();
			
			IpInfo ipInfo = new IpInfo(ipAddress, port, location,
					anonymousType, type, confirmTime, getPostSupport,
					responseSpeed);
			
			putIpInfo(ipInfo);			
		}
	}
	
	/**
	 * 鏍规嵁鎻愪緵鐨剈rl鍜宧ost鏉ヨ幏鍙栭〉闈俊鎭�	 * @param url
	 * @param host
	 * @return
	 */
	private Document getDocumentByUrl(String url, String host) {
		Document doc = null;
		try {
			doc = Jsoup
					.connect(url)
					.header("User-Agent",
							"Mozilla/5.0 (Windows NT 6.1; WOW64; rv:43.0) Gecko/20100101 Firefox/43.0")
					.header("Host", host).timeout(5000).get();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		return doc;
	} 
	
	/**
	 * 鑾峰彇http://www.kuaidaili.com/free/鐨刬p
	 */
	private void getKuaiDaiLiFreeIpLists() {
		// 绗竴娆¤闂紝闇�В鏋愭�鍏卞灏戦〉
		String baseUrl = "http://www.kuaidaili.com/free/inha/";
		String host = "www.kuaidaili.com";
		Document doc = getDocumentByUrl(baseUrl, host);
		// 瑙ｆ瀽ip淇℃伅
		parseKuaiDaiLiIpLists(doc);
		Element listNav = doc.getElementById("listnav");
		// 鑾峰彇listnav涓嬬殑li鍒楄〃
		Elements liLists = listNav.children().get(0).children();
		// 鑾峰彇鍚湁澶氬皯椤电殑瀛愬厓绱�		
		Element pageNumberEle = liLists.get(liLists.size() - 2);
		// 瑙ｆ瀽鏈夊灏戦〉
		int pageNumber = Integer.parseInt(pageNumberEle.text());
		// 鎷兼帴鎴愬叾浠栭〉鐨勮闂湴鍧�		
		for (int index = 1; index <= pageNumber; index++) {			
			baseUrl = baseUrl + index;
			doc = getDocumentByUrl(baseUrl, host);
			parseKuaiDaiLiIpLists(doc);
			// 浼戠湢涓�
			fallSleep(1);
		}
	}
	
	/**
	 * 鑾峰彇www.kuaidaili.com/proxylist/鐨刬p
	 */
	private void getKuaiDaiLiIpLists() {
		int start = 1;
		String baseUrl = "http://www.kuaidaili.com/proxylist/";
		String host = "www.kuaidaili.com";
		while (start <= 10) { // 鐖彇10椤�			
			String url = baseUrl + start + "/";
			Document doc = getDocumentByUrl(url, host);
			// 瑙ｆ瀽ip淇℃伅
			parseKuaiDaiLiIpLists(doc);
			start++;
			// 浼戠湢涓�
			fallSleep(1);
		}		
	}
	
	/**
	 * 杩涜浼戠湢
	 */
	private void fallSleep(long seconds) {
		try {
			Thread.sleep(seconds * 1000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
	
	@Override
	public void run() {
		//getKuaiDaiLiFreeIpLists();
		System.out.println("IPCollect task is running");
		getKuaiDaiLiIpLists();
		getXiCiDaiLiIpLists();
	}
	
	public BlockingQueue<IpInfo> getIpInfoQueue() {
		return ipInfoQueue;
	}

	public static void main(String[] args) {
		BlockingQueue<IpInfo> queue = new LinkedBlockingQueue<IpInfo>();
		IPCollectTask task = new IPCollectTask(queue);
		Thread thread = new Thread(task);
		thread.start();
		try {
			Thread.sleep(30 * 1000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}		
		System.out.println("queue size is " + queue.size());
		try {
			while (!queue.isEmpty()) {
				System.out.println(queue.take());
			}	
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		
		System.out.println("historyList size is " + task.historyIpLists.size());
	}
}
