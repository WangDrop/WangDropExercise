package com.test.file;

import java.io.File;

public class SimpleFileTest {
	public static void main(String [] args) {
		File file = new File("C:\\Users\\WC\\Workspaces\\MyEclipse 2015\\SimpleTest\\src\\com\\test\\file\\test.txt");
		System.out.println(file.getAbsolutePath());
		System.out.println(file.getName());
		System.out.println(file.getParent());
		System.out.println(file.getName());
		System.out.println(file.length());
	}
}
