package com.wc.netty20160710;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class ProcessThread implements Runnable {
	Socket socket;

	public ProcessThread(Socket socket) {
		this.socket = socket;
	}

	@Override
	public void run() {
		BufferedReader in = null;
		PrintWriter out = null;
		try{
			in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
			out = new PrintWriter(socket.getOutputStream(), true);
			String currentTime = null;
			String body = null;
			while(true){
				body = in.readLine();
				if(body == null)
					break;
				System.out.println("The server receive order: " + body);
				currentTime = "QUERY TIME ORDER".equalsIgnoreCase(body) ? 
						new java.util.Date().toString() :"BAD ORDER";
				out.println(currentTime);
			}
		}catch(Exception e){
			if(in != null){
				try {
					in.close();
					in = null;
				} catch (Exception e2) {
					e2.printStackTrace();
				}
			}
			if(out != null){
				try{
					out.close();
					out = null;
				}catch(Exception e3){
					e3.printStackTrace();
				}
			}
			if(this.socket != null){
				try {
					socket.close();
					socket = null;
				} catch (IOException e1) {
					e1.printStackTrace();
				}
			}
		}
	}
}
