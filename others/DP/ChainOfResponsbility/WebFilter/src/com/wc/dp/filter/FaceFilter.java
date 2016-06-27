package com.wc.dp.filter;

public class FaceFilter implements Filter {

	@Override
	public void doFilter(Request request, Response response, FilterChain filterChain) {
		request.setRequetStr(request.getRequetStr().replace(":)", "-_-"));
		filterChain.doFilter(request, response, filterChain);
		response.setResponseStr(response.getResponseStr() + "--FACE");
	}
	
}
