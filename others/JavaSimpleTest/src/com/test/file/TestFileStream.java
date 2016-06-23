package com.test.file;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

public class TestFileStream {
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		FileInputStream filestream;
		int c;
		try {
			filestream = new FileInputStream("C:\\Users\\WC\\Workspaces\\MyEclipse 2015\\SimpleTest\\src\\com\\test\\file\\test.txt");
			InputStreamReader ir = new InputStreamReader(filestream);
			while((c = ir.read()) != -1)
				System.out.println((char)c);
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}