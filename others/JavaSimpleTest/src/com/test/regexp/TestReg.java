package com.test.regexp;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class TestReg {
	public static void main(String [] args) {
		Pattern pattern = Pattern.compile("wa.*ng");
		Matcher matcher = pattern.matcher("wangcheng");
		if(matcher.matches()){
			System.out.println("The Pattern match the result!");
		}
	}
}
