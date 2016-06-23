package com.test.socketTest;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;

public class ServerDemo {

	public static void main(String[] args) throws UnknownHostException, IOException {
		ServerSocket serverSocket = new ServerSocket(12001);
		Socket ss = serverSocket.accept();
		
		BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(ss.getInputStream()));
		String line = null;
		
		BufferedWriter bufferedWriter = new BufferedWriter(new OutputStreamWriter(new FileOutputStream("C:\\2.txt")));
		while((line = bufferedReader.readLine()) != null){
			System.out.println("Server read from sockets!" + line);
			bufferedWriter.write(line);
			bufferedWriter.flush();
		}
		System.out.println("´«Êä³É¹¦£¡");
		serverSocket.close();
		ss.close();
		bufferedReader.close();
		bufferedWriter.close();
	}

}
