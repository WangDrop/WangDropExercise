package com.test.regexp;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class TestAll {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Pattern pattern1 = Pattern.compile("\\w.*?ab");
		Matcher matcher = pattern1.matcher("bbbbab aa isabc");
		if(matcher.matches()){
			System.out.println("ȫƥ��");
		}else{
			System.out.println("��ȫƥ��");
		}
		matcher.reset(); 
		while(matcher.find()){
			System.out.println(matcher.group());
			System.out.println("��ʼλ�ã�"+matcher.start()+"---"+"����λ�ã�"+matcher.end());//start()������ǰƥ��ĳ�ʼ����,end()�������ƥ���ַ�֮���ƫ����
		}
		matcher.reset();
		if(matcher.lookingAt()){
			System.out.println("ƥ��");
		}else{
			System.out.println("��ƥ��");
		}
		
		matcher.reset();
		System.out.println(matcher.replaceAll("�滻"));
		System.out.println(matcher.replaceFirst("�滻��һ��"));
	}
}
