package com.test.regexp;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class TestGreedy {
	public static void main(String [] args) {
		Pattern pattern1 = Pattern.compile("\\w.*ab"); //greedy
		Pattern pattern2 = Pattern.compile("\\w.*?ab"); //not greedy
		Matcher matcher1 = pattern1.matcher("bbbbab aaab jjjj ssss");
		Matcher matcher2 = pattern2.matcher("bbbbab aaab jjjj ssss");
		while(matcher1.find()){
			System.out.println(matcher1.group());
		}
		System.out.println("---------------------------------");
		while(matcher2.find()){
			System.out.println(matcher2.group());
		}
	}
}
