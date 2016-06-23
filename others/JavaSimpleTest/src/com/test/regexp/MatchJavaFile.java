package com.test.regexp;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;

public class MatchJavaFile {
	static long comment = 0;
	static long emptyLine = 0;
	static long codeLine = 0;
	
	public static void main(String []args){
		MatchJavaFile.parses("C:\\test.java");
		System.out.println("Comment: " + comment);
		System.out.println("Empty: " + emptyLine);
		System.out.println("codeLine: " + codeLine);
	}
	
	public static void parses(String fileName){
		String line = "";
		boolean inComment = false;
		BufferedReader bufferedReader;
		try{
			bufferedReader = new BufferedReader(new InputStreamReader(new FileInputStream(fileName)));
			while((line = bufferedReader.readLine()) != null){
				line = line.trim();

				if(line.matches("^[\\s&&[^\\n]]*$"))
					emptyLine++;
				else if(line.startsWith("/*") && !line.endsWith("*/"))
					comment++;
				else if(line.startsWith("/*")){
					comment++;
					inComment=true;
				}else if(line.endsWith("*/")){
					inComment = false;
				}else if(inComment){
					comment++;
				}else{
					codeLine++;
				}
			}
		}catch(FileNotFoundException ex){
			ex.printStackTrace();
		}catch(IOException ex){
			ex.printStackTrace();
		}
	}
}
