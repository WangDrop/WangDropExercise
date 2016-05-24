package com.jkxy.service;

import java.sql.Connection;
import java.sql.ResultSet;

import com.jkxy.model.userTable;
import com.mysql.jdbc.PreparedStatement;

public class userService {
	private Connection conn;
	private PreparedStatement pstmt;
	public userService(){
		conn = new com.jkxy.conn.conn().getCon();
	}
	public boolean validUser(userTable user){
		try{
			pstmt = (PreparedStatement) conn.prepareStatement("select * from usertable where username = ? and passwd = ?");
			pstmt.setString(1, user.getUsername()); //ע��userTable�е�����Ӧ�ú����ݿ�����ж�Ӧ����������ͬ��
			pstmt.setString(2, user.getPasswd());
			ResultSet resultSet = pstmt.executeQuery();
			if(resultSet.next())
				return true;
			else {
				return false;
			}
		}catch(Exception e){
			e.printStackTrace();
			return false;
		}

	}
}
