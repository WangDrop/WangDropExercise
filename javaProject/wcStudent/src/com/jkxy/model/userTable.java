package com.jkxy.model;

public class userTable {
	//成员变量要和数据库表一一对应
	private String username;
	private String passwd;
	public String getUsername() {
		return username;
	}
	public void setUsername(String username) {
		this.username = username;
	}
	public String getPasswd() {
		return passwd;
	}
	public void setPasswd(String passwd) {
		this.passwd = passwd;
	}
	//自己如果顶一个一个有参的构造方法的情况下还仍然应该注意写一个无参的构造方法
	//这是因为javaBean一定要有一个无参的构造函数
	//例如，乳瓜加上了下面这行方法的时候就会报错，因为javaBean没有找到一个无参的构造函数
	public userTable(String username){
		this.username = username;
	}
	//可以加上一个显示的构造函数解决这个问题
	public userTable(){
		this.username = "";
	}
}
