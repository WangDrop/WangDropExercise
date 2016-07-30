package com.wc.netty20160710;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class TimerServer {
	@SuppressWarnings("resource")
	public static void main(String[] args) {
		int port = 8080;
		ServerSocket server = null;
		System.out.println("Server started in port : " + port + "!");
		Socket socket = null;
		try {
			server = new ServerSocket(port);
		} catch (IOException e) {
			e.printStackTrace();
		}
		while(true){
			try {
				socket = server.accept();
			} catch (IOException e) {
				e.printStackTrace();
			}
			new Thread(new ProcessThread(socket)).start();;
		}
	}
}
