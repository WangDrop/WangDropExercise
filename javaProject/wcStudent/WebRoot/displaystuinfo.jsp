<%@page import="com.jkxy.model.stuInfo"%>
<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>My JSP 'displaystuinfo.jsp' starting page</title>
    
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
   <%
    	List stus = (List)session.getAttribute("stus");
    	//if(stus != null)
	    //	out.print("The size of the query is " + stus.size());
     	Iterator iter = stus.iterator();
     %>
     <table>
     	<tr>
     		<td>id</td>
     		<td>昵称</td>
     		<td>真实姓名</td>
     		<td>性别</td>
     		<td>出生日期</td>
     		<td>所在专业</td>
     		<td>所选课程</td>
     		<td>兴趣</td>
     		<td>备注</td>
     	</tr>
     	<%
     		int i = 0;
     		while(iter.hasNext()){
     			stuInfo student = (stuInfo) iter.next();
     	 %>
     	 <tr <%if(i%2 == 0){%>bgcolor = "#F0F8FF" <%}%>>
     	 	<td><%=student.getId() %></td>
     	 	<td><%=student.getNiceName() %></td>
     	 	<td><%=student.getTrueName() %></td>
     	 	<td><%=student.getXb() %></td>
     	 	<td><%=student.getCsrq() %></td>
     	 	<td><%=student.getZy() %></td>
     	 	<td><%=student.getKcs() %></td>
     	 	<td><%=student.getXqs() %></td>
     	 	<td><%=student.getBz() %></td>
     	 
     	 </tr>
     	 <%
     	 		i++;
     	 	}
     	  %>
     </table>
  </body>
</html>
