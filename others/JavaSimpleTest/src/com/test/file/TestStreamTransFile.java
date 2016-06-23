package com.test.file;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

public class TestStreamTransFile {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		FileInputStream filestream;
		FileOutputStream fileOutputStream;
		String tmpString;
		try {
			filestream = new FileInputStream("C:\\Users\\WC\\Workspaces\\MyEclipse 2015\\SimpleTest\\src\\com\\test\\file\\test.txt");
			BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(filestream));
			fileOutputStream = new FileOutputStream("C:\\outTest.txt");
			BufferedWriter bufferedWriter = new BufferedWriter(new OutputStreamWriter(fileOutputStream));
			while ((tmpString = bufferedReader.readLine()) != null) {
				bufferedWriter.append(tmpString);
				bufferedWriter.flush(); //注意使用BufferedWriter写入的时候应该flush，否则可能出现无法正常写入的问题
			}
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}catch (IOException e) {
			// TODO: handle exception
			e.printStackTrace();
		}
		
	}

}
