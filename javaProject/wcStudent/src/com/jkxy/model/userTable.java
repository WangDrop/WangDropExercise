package com.jkxy.model;

public class userTable {
	//��Ա����Ҫ�����ݿ��һһ��Ӧ
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
	//�Լ������һ��һ���вεĹ��췽��������»���ȻӦ��ע��дһ���޲εĹ��췽��
	//������ΪjavaBeanһ��Ҫ��һ���޲εĹ��캯��
	//���磬��ϼ������������з�����ʱ��ͻᱨ����ΪjavaBeanû���ҵ�һ���޲εĹ��캯��
	public userTable(String username){
		this.username = username;
	}
	//���Լ���һ����ʾ�Ĺ��캯������������
	public userTable(){
		this.username = "";
	}
}
