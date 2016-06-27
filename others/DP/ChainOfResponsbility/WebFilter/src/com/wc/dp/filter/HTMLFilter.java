package com.wc.dp.filter;

public class HTMLFilter implements Filter{

	@Override
	public void doFilter(Request request, Response response, FilterChain filterChain) {
		request.setRequetStr(request.getRequetStr().replace('<', '[').replace('>', ']'));
		filterChain.doFilter(request, response, filterChain);
		response.setResponseStr(response.getResponseStr() + "--HTML");
	}

}
