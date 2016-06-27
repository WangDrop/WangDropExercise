package com.wc.dp.filter;

public class Main {
	public static void main(String [] args){
		String msg = "��Һ�:), <script>, ���У� ������ �����İ�����";
		Request request = new Request();
		Response response = new Response();
		request.setRequetStr(msg);
		response.setResponseStr("response");
		
		FilterChain filterChain = new FilterChain();
		filterChain.addFilter(new HTMLFilter()).addFilter(new SensitiveFilter());
		FilterChain filterChain2 = new FilterChain();
		filterChain2.addFilter(new FaceFilter());
		filterChain.addFilter(filterChain2);
		
		filterChain.doFilter(request, response, filterChain);
		System.out.println(request.getRequetStr());
		System.out.println(response.getResponseStr());
	}
}
