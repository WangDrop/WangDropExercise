package com.test.socketTest;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;

public class SocketReadHttp {
	public static void main(String [] args) throws IOException{

		ServerSocket serverSocket = new ServerSocket(12001);
		Socket client = serverSocket.accept();
		BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(client.getInputStream()));
		String line;
		while((line  = bufferedReader.readLine()) != null){
			System.out.println(line);
		}
		serverSocket.close();
		client.close();
		bufferedReader.close();
	}
}
