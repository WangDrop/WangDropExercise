package com.test.file;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.CharBuffer;
import java.nio.MappedByteBuffer;
import java.nio.channels.Channel;
import java.nio.channels.FileChannel;
import java.nio.charset.Charset;
import java.nio.charset.CharsetDecoder;

public class TestChannel {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		FileChannel inChannel = null;
		FileChannel outChannel = null;
		FileChannel randomChannel = null;
		File file = new File("C:\\Users\\WC\\Workspaces\\MyEclipse 2015\\SimpleTest\\src\\com\\test\\file\\test.txt");
		try{
			FileInputStream fileInputStream = new FileInputStream(file);
			inChannel = fileInputStream.getChannel();
			MappedByteBuffer buffer = inChannel.map(FileChannel.MapMode.READ_ONLY, 0, file.length());
			Charset charset= Charset.forName("UTF-8");
			outChannel = new FileOutputStream("C:\\out.txt").getChannel();
			outChannel.write(buffer);
			buffer.clear();
			
			CharsetDecoder decoder = charset.newDecoder();
			CharBuffer charBuffer = decoder.decode(buffer);
			System.out.println(charBuffer);
		}catch(FileNotFoundException e){
			e.printStackTrace();
		}catch (IOException e) {
			// TODO: handle exception
			e.printStackTrace();
		}
	}

}
