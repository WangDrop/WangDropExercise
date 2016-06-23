package com.test.database;

import java.net.ConnectException;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;

import com.mysql.jdbc.Connection;
import com.mysql.jdbc.Statement;

public class CreateDB {
	public static void main(String [] args) {
		String url = "jdbc:mysql://localhost:3306";
		String user = "root";
		String password = "1316";
		String driverClass = "com.mysql.jdbc.Driver";
		try{
			Class.forName(driverClass);//这里就加载了jdbc驱动，类加载器会执行类的静态代码块注册驱动
			Connection conn = (Connection)DriverManager.getConnection(url, user, password);
			Statement stmt = (Statement) conn.createStatement();
			stmt.execute("use information_schema");
			int i = 0;
			ResultSet rSet = stmt.executeQuery("select * from information_schema.schemata where shema_name = 'student'");
			while(rSet.next()){
				i++;
			}
			if(i == 0){
				stmt.executeUpdate("create database student");
			}
			stmt.executeUpdate("use student");
			
			int j = 0;
			ResultSet rSet2 = stmt.executeQuery("select * from information_schema.tables where table_schema = 'student' and table_name = 'info'");
			while(rSet2.next())
				j++;
			if(j == 0){
				stmt.executeUpdate("create table stuinfo (sno INT not null primary key, name varchar(50) not null, age int, sex varchar(50))");
			}
			stmt.addBatch("insert into stuinfo values(001, 'wangcheng', '23', '男')");
			stmt.executeBatch();
			stmt.close();
			stmt=null;
			conn.close();
			conn=null;
		}catch(SQLException ex){
			ex.printStackTrace();
		}catch(ClassNotFoundException ex){
			ex.printStackTrace();
		}
	}
}
