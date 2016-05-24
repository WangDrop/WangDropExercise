package com.jkxy.model;


public class stuInfo {
	private int id; //id数据库中没有，因为在数据库中这一项是自增的
	private String niceName;
	private String trueName;
	private String xb;
	private String csrq;
	private String zy;
	private String [] kc = {""}; //课程实际上是一个String的数组，因为当时提交的时候是多选项，所以用数组存储
	private String kcs = ""; //将课程的字符串数组串成一个的字符串然后传入到数据库中进行处理，下同
	private String [] xq = {""};
	private String xqs = "";
	private String bz; //备注
	public int getId() {
		return id;
	}
	public void setId(int id) {
		this.id = id;
	}
	public String getNiceName() {
		return niceName;
	}
	public void setNiceName(String niceName) {
		this.niceName = niceName;
	}
	public String getTrueName() {
		return trueName;
	}
	public void setTrueName(String trueName) {
		this.trueName = trueName;
	}
	public String getXb() {
		return xb;
	}
	public void setXb(String xb) {
		this.xb = xb;
	}
	public String getCsrq() {
		return csrq;
	}
	public void setCsrq(String csrq) {
		this.csrq = csrq;
	}
	public String getZy() {
		return zy;
	}
	public void setZy(String zy) {
		this.zy = zy;
	}
	public String[] getKc() {
		return kc;
	}
	public void setKc(String[] kc) {
		this.kc = kc;
	}
	public String getKcs() {
		kcs = "";
		if(kc != null){
			for(int i = 0; i < kc.length; ++i)
				kcs += kc[i] + "&";
		}
		kcs = kcs.substring(0, kcs.length() - 1); //这里为了将最后一个"&"分隔符去掉，方便后续的程序处理
		return kcs;
	}
	public void setKcs(String kcs) {
		this.kcs = kcs;
	}
	public String[] getXq() {
		return xq;
	}
	public void setXq(String[] xq) {
		this.xq = xq;
	}
	public String getXqs() {
		xqs = "";
		if(xq != null){
			for(int i = 0; i < xq.length; ++i){
				xqs += xq[i] + "&";
			}
			xqs = xqs.substring(0, xqs.length() - 1);
		}
		return xqs;
	}
	public void setXqs(String xqs) {
		this.xqs = xqs;
	}
	public String getBz() {
		return bz;
	}
	public void setBz(String bz) {
		this.bz = bz;
	}
}
