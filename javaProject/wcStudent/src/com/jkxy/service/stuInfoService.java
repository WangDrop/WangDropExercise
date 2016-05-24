package com.jkxy.service;

import java.util.List;
import java.sql.Connection;



import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;


import com.jkxy.model.stuInfo;
import com.mysql.jdbc.PreparedStatement;


public class stuInfoService {
	private Connection conn;
	private PreparedStatement pstmt;
	public stuInfoService(){
		conn = new com.jkxy.conn.conn().getCon();
	}
	public boolean addStu(stuInfo stu){
		try{
			pstmt = (PreparedStatement) conn.prepareStatement("insert into stuinfo"
					+ "(niceName, trueName, xb, csrq, zy, kc, xq, bz)"
					+ "values(?, ?, ?, ?, ?, ?, ?, ?)");
			pstmt.setString(1, stu.getNiceName()); //注意userTable中的名称应该和数据库表中列对应的名称是相同的
			pstmt.setString(2, stu.getTrueName());
			pstmt.setString(3, stu.getXb());
			pstmt.setString(4, stu.getCsrq());
			pstmt.setString(5, stu.getZy());
			pstmt.setString(6, stu.getKcs());
			pstmt.setString(7, stu.getXqs());
			pstmt.setString(8, stu.getBz());
			
			pstmt.executeUpdate();
			return true;
		}catch(Exception e){
			e.printStackTrace();
			return false;
		}
	}
	
	public List queryAllStu(){
		List <stuInfo> stus = new ArrayList<stuInfo>();
		try{
			pstmt = (PreparedStatement) conn.prepareStatement("select * from stuinfo");
			ResultSet rSet = pstmt.executeQuery();
			while(rSet.next()){
				stuInfo stu = new stuInfo();
				stu.setId(rSet.getInt(1));
				stu.setNiceName(rSet.getString(2));
				stu.setTrueName(rSet.getString(3));
				stu.setXb(rSet.getString(4));
				if(rSet.getDate(5) != null)
					stu.setCsrq(rSet.getDate(5).toString());
				stu.setZy(rSet.getString(6));
				if(rSet.getString(7) != null){
					stu.setKc(rSet.getString(7).split("&"));
				}
				if(rSet.getString(8) != null){
					stu.setXq(rSet.getString(8).split("&"));
				}
				stu.setBz(rSet.getString(9));
				stus.add(stu);
			}
			return stus;
		}catch(SQLException e){
			e.printStackTrace();
			return null;
		}
		
	}
	
	public stuInfo queryStuByID(int id){
		try{
			pstmt = (PreparedStatement) conn.prepareStatement("select * from stuinfo where id = ?");
			pstmt.setInt(1, id);
			ResultSet rSet = pstmt.executeQuery();
			if(rSet.next()){
				stuInfo stu = new stuInfo();
				stu.setId(rSet.getInt(1));
				stu.setNiceName(rSet.getString(2));
				stu.setTrueName(rSet.getString(3));
				stu.setXb(rSet.getString(4));
				if(rSet.getDate(5) != null)
					stu.setCsrq(rSet.getDate(5).toString());
				stu.setZy(rSet.getString(6));
				if(rSet.getString(7) != null){
					stu.setKc(rSet.getString(7).split("&"));
				}
				if(rSet.getString(8) != null){
					stu.setXq(rSet.getString(8).split("&"));
				}
				stu.setBz(rSet.getString(9));
				return stu;
			}
			return null;
		}catch(SQLException e){
			e.printStackTrace();
			return null;
		}
	}
	
	public boolean updateStu(stuInfo info) {
		try{
			pstmt = (PreparedStatement)conn.prepareStatement("update stuinfo set niceName = ?, trueName = ?, xb = ?, csrq = ?, zy = ?, kc = ?, xq = ?, bz = ? where id = ?");
			pstmt.setString(1, info.getNiceName());
			pstmt.setString(2, info.getTrueName());
			pstmt.setString(3, info.getXb());
			pstmt.setString(4, info.getCsrq());
			pstmt.setString(5, info.getZy());
			pstmt.setString(6, info.getKcs());
			pstmt.setString(7, info.getXqs());
			pstmt.setString(8, info.getBz());
			pstmt.setInt(9, info.getId());
			pstmt.executeUpdate();
			return true;
		}catch(SQLException e){
			e.printStackTrace();
			return false;
		}
	}
	
	public boolean deleteStu(int id){
		try{
			pstmt = (PreparedStatement)conn.prepareStatement("delete from stuinfo where id = ?");
			pstmt.setInt(1, id);
			pstmt.executeUpdate();
			return true;
		}catch(SQLException e){
			e.printStackTrace();
			return false;
		}
	}
}
