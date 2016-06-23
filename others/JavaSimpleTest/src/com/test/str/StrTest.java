package com.test.str;

public class StrTest{
	public static void main(String [] args) {
		String st1 = "I am wangcheng";
		String st2 = "I am " + "wangcheng";
		String st3 = "I am ";
		st3 += "wangcheng";
		System.out.println(st1==st2);
		System.out.println(st1.equals(st2));
		System.out.println(st1==st3);
		System.out.println(st1.equals(st3));
	}
}
