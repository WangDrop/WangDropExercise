package com.wc.netty20160710;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;

public class TimeClient {
	public static void main(String[] args) {
		int port = 8080;
		Socket socket = null;
		BufferedReader bufferedReader = null;
		PrintWriter printWriter = null;
		try {
			socket = new Socket("127.0.0.1", port);
			bufferedReader = new BufferedReader(new InputStreamReader(
					socket.getInputStream()));
			printWriter = new PrintWriter(new OutputStreamWriter(
					socket.getOutputStream()));
			printWriter.println("QUERY TIME ORDER");
			String resp = bufferedReader.readLine();
			System.out.println("Now is " + resp);
		} catch (Exception e) {
			if(bufferedReader != null){
				try {
					bufferedReader.close();
				} catch (IOException e1) {
					e1.printStackTrace();
				}
			}
			if(printWriter != null){
				try{
					printWriter.close();
				}catch(Exception e1){
					e1.printStackTrace();
				}
			}
			if(socket != null){
				try{
					socket.close();
				}catch(Exception e1){
					e1.printStackTrace();
				}
			}
		}
	}
}
