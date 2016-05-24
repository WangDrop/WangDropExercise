<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>My JSP 'main_left.jsp' starting page</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->

  </head>
  <jsp:include page = "isLogin.jsp"></jsp:include>
  <body>
    <a href = "inputstuinfo.jsp" target = "main_right">录入学生信息 </a> <br>
     <a href = "student/queryAllStuServlet?osid=query" target = "main_right"> 查看学生信息 </a> <br>
  	  <a href = "student/queryAllStuServlet?osid=modify" target = "main_right"> 修改学生信息 </a> <br>
  	   <a href = "student/queryAllStuServlet?osid=delete" target = "main_right"> 删除学生信息 </a> <br>
 		<a href = "user/exitServlet" target = "_top"> 退出 </a> <br>
  </body>
</html>
