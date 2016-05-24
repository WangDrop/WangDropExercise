<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>My JSP 'inputstuinfo.jsp.jsp' starting page</title>
    
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
    <center>
    	<form action="student/inputStuInfoServlet" method="post">
			<table bgColor="#c0c0c0">
				<tr>
					<td align="center" bgcolor=green colspan=2><font color=white>学生信息录入</font></td>
				</tr>
				<tr>
					<td>昵称：</td>
					<td><input type="text" size=20 name="niceName"></td>
				</tr>
				<tr>
					<td>真实姓名：</td>
					<td><input type="text" size=20 name="trueName"></td>
				</tr>
				<tr>
					<td>性别</td>
					<td><input type="radio" name="xb" checked value="1">男&nbsp;&nbsp;
						<input type="radio" name="xb" value="0">女</td>
				</tr>
				<tr>
					<td>出生日期：</td>
					<td><input type="text" name="csrq" size=20></td>
				</tr>
				<tr>
					<td>所学专业：</td>
					<td><select name="zy">
							<option>计算机科学与技术</option>
							<option selected>通信工程</option>
							<option>电气工程</option>
					</select></td>
				</tr>
				<tr>
					<td>所学课程：</td>
					<td><select name="kc" size=2 multiple="multiple">
							<option>计算机导论</option>
							<option>数据结构</option>
							<option>数据库原理</option>

							<option>操作系统</option>
							<option>计算机网络</option>
							<option>软件工程</option>
					</select></td>
				</tr>
				<tr>
					<td>兴趣</td>
					<td><input type="checkbox" value="music" name="xq">听音乐&nbsp;
						<input type="checkbox" value="book" name="xq">看小说&nbsp; <input
						type="checkbox" value="web" name="xq">上网&nbsp;</td>
				</tr>
				<tr valign="top">
					<td>"备注"</td>
					<td><textarea rows=3 cols=20 name="bz"></textarea></td>
				</tr>
				<tr ><td align="center" colspan="2" ><input type="submit"  value="提交">&nbsp;&nbsp; <input
				type="reset"  value="重置"></td></tr>
			</table>
		</form>
	</center>
  </body>
</html>
