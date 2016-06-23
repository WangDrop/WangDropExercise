package com.test.regexp;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class TestAll {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Pattern pattern1 = Pattern.compile("\\w.*?ab");
		Matcher matcher = pattern1.matcher("bbbbab aa isabc");
		if(matcher.matches()){
			System.out.println("全匹配");
		}else{
			System.out.println("非全匹配");
		}
		matcher.reset(); 
		while(matcher.find()){
			System.out.println(matcher.group());
			System.out.println("开始位置："+matcher.start()+"---"+"结束位置："+matcher.end());//start()返回以前匹配的初始索引,end()返回最后匹配字符之后的偏移量
		}
		matcher.reset();
		if(matcher.lookingAt()){
			System.out.println("匹配");
		}else{
			System.out.println("非匹配");
		}
		
		matcher.reset();
		System.out.println(matcher.replaceAll("替换"));
		System.out.println(matcher.replaceFirst("替换第一个"));
	}
}
