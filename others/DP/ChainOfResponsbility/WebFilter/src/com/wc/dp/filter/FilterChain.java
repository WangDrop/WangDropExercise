package com.wc.dp.filter;

import java.util.List;
import java.util.ArrayList;

public class FilterChain implements Filter{
	List<Filter> filters = new ArrayList<>();
	int index = 0;
	public FilterChain addFilter(Filter filter){
		filters.add(filter);
		return this;
	}
	public void doFilter(Request request, Response response, FilterChain filterChain){
		if(index == filters.size())
			return;
		Filter filter = filters.get(index);
		index++;
		filter.doFilter(request, response, filterChain);
	}
}
