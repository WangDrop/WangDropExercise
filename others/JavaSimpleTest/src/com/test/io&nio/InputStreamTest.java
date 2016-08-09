package com.wc.IO;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.StringReader;

public class InputStreamTest {
	public static void main(String[] args) throws IOException {
		FileOutput();
	}

	static public void bufferedReaderTest() throws IOException {
		BufferedReader reader = new BufferedReader(new InputStreamReader(
				System.in));
		String words;
		while ((words = reader.readLine()) != null) {
			System.out.println(words);
		}
	}

	static public void stringReaderTest() throws IOException {
		StringReader reader = new StringReader(new String("12"));
		int i = 0;
		while ((i = reader.read()) != -1) { // 读出错的话会返回-1
			System.out.println((char) i);// 将int转换输出
		}
	}

	static public void FileOutput() throws IOException {
		File file = new File("InputStreamTest.java");
		File outFile = new File("src/out.dat");
		if (!file.exists())
			file.createNewFile();
		if (!outFile.exists())
			outFile.createNewFile();
		BufferedReader bufferedReader = new BufferedReader(
				new InputStreamReader(new FileInputStream(file)));
		BufferedWriter bufferedWriter = new BufferedWriter(
				new OutputStreamWriter(new FileOutputStream(outFile)));
		String curr = null;
		while ((curr = bufferedReader.readLine()) != null) {
			bufferedWriter.write(curr);
		}
		bufferedReader.close();
		bufferedWriter.close();
	}

	// 二进制文件的
	static public byte[] BinaryRead(File file) throws IOException {
		BufferedInputStream bufferedInputStream = new BufferedInputStream(
				new FileInputStream(file));
		byte[] arr = new byte[bufferedInputStream.available()];
		bufferedInputStream.read(arr);
		bufferedInputStream.close();
		return arr;
	}
}
