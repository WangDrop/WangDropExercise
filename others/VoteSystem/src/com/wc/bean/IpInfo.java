package com.wc.bean;

public class IpInfo {
	private String ipAddress;
	private int port;
	private String location;
	private String anonymousType;
	private String type;
	private String confirmTime;
	private String getPostSupport;
	private String responseSpeed;
	
	public IpInfo(String ipAddress, int port, String location, String anonymousType, String type,
			String confirmTime, String getPostSupport, String responseSpeed) {
		this.ipAddress = ipAddress;
		this.port = port;
		this.location = location;
		this.anonymousType = anonymousType;
		this.type = type;
		this.confirmTime = confirmTime;
		this.getPostSupport = getPostSupport;
		this.responseSpeed = responseSpeed;
	}
	
	public IpInfo(String ipAddress, int port, String location, String anonymousType, String type,
			String confirmTime) {
		this(ipAddress, port, location, anonymousType, type, confirmTime, null, null);
	}
	
	@Override
	public boolean equals(Object object){
		if(this == object)
			return true; //指向同一个引用
		if(object == null || object.getClass() != getClass())
			return false;
		IpInfo info = (IpInfo)object;
		return this.ipAddress.equals(info.ipAddress) && 
				this.port == info.port &&
				this.location.equals(info.location) &&
				this.anonymousType.equals(info.anonymousType) && 
				this.type.equals(info.type) &&
				this.confirmTime.equals(info.confirmTime) &&
				this.getPostSupport.equals(info.getPostSupport) &&
				this.responseSpeed.equals(info.responseSpeed);
	}

	@Override
	public int hashCode(){
		int hash =  5;
		hash = 89 * hash + (this.ipAddress == null ? 0 : this.ipAddress.hashCode());
		hash = 89 * hash + this.port;
		hash = 89 * hash + (this.location == null ? 0 : this.location.hashCode());
		hash = 89 * hash + (this.anonymousType  == null ? 0 : this.anonymousType.hashCode());
		hash = 89 * hash + (this.confirmTime == null ? 0 : this.confirmTime.hashCode());
		hash = 89 * hash + (this.getPostSupport == null ? 0 : this.getPostSupport.hashCode());
		hash = 89 * hash + (this.responseSpeed == null ? 0 : this.responseSpeed.hashCode());
		return hash;
	}
	
	@Override
	public String toString(){
		return "ipAddress: " + this.ipAddress + ", port: " + this.port + ", location: " + this.location + 
				", anonymousType: " + this.anonymousType + ", type: " + this.type + ", confirmTime: " + 
				this.confirmTime + ", getPostSupport: " + this.getPostSupport + ", responseSpeed: " + this.responseSpeed;
	}
	
	public String getIpAddress() {
		return ipAddress;
	}
	public void setIpAddress(String ipAddress) {
		this.ipAddress = ipAddress;
	}
	public int getPort() {
		return port;
	}
	public void setPort(int port) {
		this.port = port;
	}
	public String getLocation() {
		return location;
	}
	public void setLocation(String location) {
		this.location = location;
	}
	public String getAnonymousType() {
		return anonymousType;
	}
	public void setAnonymousType(String anonymousType) {
		this.anonymousType = anonymousType;
	}
	public String getType() {
		return type;
	}
	public void setType(String type) {
		this.type = type;
	}
	public String getConfirmTime() {
		return confirmTime;
	}
	public void setConfirmTime(String confirmTime) {
		this.confirmTime = confirmTime;
	}
	public String getGetPostSupport() {
		return getPostSupport;
	}
	public void setGetPostSupport(String getPostSupport) {
		this.getPostSupport = getPostSupport;
	}
	public String getResponseSpeed() {
		return responseSpeed;
	}
	public void setResponseSpeed(String responseSpeed) {
		this.responseSpeed = responseSpeed;
	}

}
