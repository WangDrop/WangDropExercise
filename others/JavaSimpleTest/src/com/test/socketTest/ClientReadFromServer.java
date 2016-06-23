package com.test.socketTest;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;

public class ClientReadFromServer {
	public static void main(String [] args) throws UnknownHostException, IOException {
		Socket socket = new Socket("192.168.0.113", 8080);
		PrintWriter printWriter = new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));
		printWriter.println("GET /SocketWebTest/1.html HTTP/1.1");
		printWriter.println("Accept:*/*");
		printWriter.println("Host: 192.168.0.113:15342");
		printWriter.println("Connection: Keep-Alive");
		
		printWriter.println();
		BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
		String line;
		while((line = in.readLine()) != null){
			System.out.println(line);
		}
		socket.close();
		in.close();
	}
}
