package com.jkxy.servlet;

import java.io.IOException;

import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.jkxy.model.userTable;
import com.jkxy.service.userService;

public class loginServlet extends HttpServlet {
	public void doPost(HttpServletRequest request, HttpServletResponse response) {
		
		String userName = request.getParameter("username");
		String passWord = request.getParameter("passwd");
		userTable user = new userTable();
		user.setUsername(userName);
		user.setPasswd(passWord);
		try{
			if(new userService().validUser(user)){
				HttpSession session = request.getSession();
				session.setAttribute("user", user);
				response.sendRedirect("../main.jsp");
			}else{
				System.out.println("Reach here!");
				response.sendRedirect("../index.jsp");
			}
		}catch(IOException e){
			e.printStackTrace();
		}
	}
	
	public void doGet(HttpServletRequest request, HttpServletResponse response){
		doPost(request, response);
	}
}
