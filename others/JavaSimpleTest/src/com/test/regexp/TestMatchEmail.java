package com.test.regexp;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class TestMatchEmail {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		BufferedReader bufferedReader = null;
		try{
			bufferedReader = new BufferedReader(new InputStreamReader(new FileInputStream("C:\\mails.txt")));
			String line = "";
			while((line = bufferedReader.readLine()) != null){
				parse(line);
			}
			
		}catch(FileNotFoundException ex){
			ex.printStackTrace();
		}catch(IOException ex){
			ex.printStackTrace();
		}finally{
			if(bufferedReader != null){
				try {
					bufferedReader.close();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				bufferedReader = null;
			}
		}
	}
	
	private static void parse(String email){
		Pattern pattern  = Pattern.compile("\\w{3,20}+@\\w+\\.(com|cn|org|net|gov)");
		Matcher matcher = pattern.matcher(email);
		while(matcher.find()){
			System.out.println(matcher.group());
		}
	}

}
