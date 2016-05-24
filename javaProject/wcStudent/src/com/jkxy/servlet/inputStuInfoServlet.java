package com.jkxy.servlet;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.Date;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.jkxy.model.stuInfo;
import com.jkxy.service.stuInfoService;

public class inputStuInfoServlet extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public inputStuInfoServlet() {
		super();
	}

	/**
	 * Destruction of the servlet. <br>
	 */
	public void destroy() {
		super.destroy(); // Just puts "destroy" string in log
		// Put your code here
	}

	/**
	 * The doGet method of the servlet. <br>
	 *
	 * This method is called when a form has its tag value method equals to get.
	 * 
	 * @param request the request send by the client to the server
	 * @param response the response send by the server to the client
	 * @throws ServletException if an error occurred
	 * @throws IOException if an error occurred
	 */
	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		doPost(request, response);
	}

	/**
	 * The doPost method of the servlet. <br>
	 *
	 * This method is called when a form has its tag value method equals to post.
	 * 
	 * @param request the request send by the client to the server
	 * @param response the response send by the server to the client
	 * @throws ServletException if an error occurred
	 * @throws IOException if an error occurred
	 */
	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		request.setCharacterEncoding("utf-8"); //注意servlet的编码应该设置好
		String niceName = request.getParameter("niceName");
		String trueName = request.getParameter("trueName");
		String xb = request.getParameter("xb");
		String csrq = request.getParameter("csrq");
		String zy = request.getParameter("zy");
		System.out.println(zy);
		String kc [] = request.getParameterValues("kc");
		String xq [] = request.getParameterValues("xq");
		String bz = request.getParameter("bz");
		stuInfo stu = new stuInfo();
		stu.setNiceName(niceName);
		stu.setTrueName(trueName);
		stu.setXb(xb);
		stu.setCsrq(csrq);
		if(csrq == "") //处理数据的有效性问题
			stu.setCsrq(null);
		stu.setZy(zy);
		if(kc != null)
			stu.setKc(kc);
		if(xq != null)
			stu.setXq(xq);
		stu.setBz(bz);
		if(new stuInfoService().addStu(stu)){
			response.sendRedirect("../input_info_success.jsp");
		}else{
			response.sendRedirect("../input_info_fail.jsp");
		}
	}

	/**
	 * Initialization of the servlet. <br>
	 *
	 * @throws ServletException if an error occurs
	 */
	public void init() throws ServletException {
		// Put your code here
	}

}
