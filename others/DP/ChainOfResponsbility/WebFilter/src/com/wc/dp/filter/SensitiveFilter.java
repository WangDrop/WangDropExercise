package com.wc.dp.filter;

public class SensitiveFilter implements Filter{

	@Override
	public void doFilter(Request request, Response response, FilterChain filterChain) {
		request.setRequetStr(request.getRequetStr().replace("¿ª³µ", "drive"));
		filterChain.doFilter(request, response, filterChain);
		response.setResponseStr(response.getResponseStr() + "--SENDSITIVE");
	}
	
}
