package com.test.socketTest;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;
import java.net.UnknownHostException;

public class ClientDemo {

	public static void main(String[] args) throws UnknownHostException, IOException {
		// TODO Auto-generated method stub
		Socket so = new Socket("127.0.0.1", 12001);
		BufferedReader bufferedReader = new BufferedReader(new FileReader("C:\\1.txt"));
		
		BufferedWriter bufferedWriter = new BufferedWriter(new OutputStreamWriter(so.getOutputStream()));
		
		String line;
		while((line = bufferedReader.readLine()) != null){
			bufferedWriter.write(line);
			bufferedWriter.flush();
		}
		so.shutdownOutput();
		
		BufferedReader readerSocket = new BufferedReader(new InputStreamReader(so.getInputStream()));
		line = readerSocket.readLine();
		System.out.println("read from socket: " + line);
		so.close();
		readerSocket.close();
	}

}
