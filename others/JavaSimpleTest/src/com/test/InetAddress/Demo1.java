package com.test.InetAddress;

import java.net.InetAddress;
import java.net.UnknownHostException;

public class Demo1 {
	public static void main(String [] args){
		InetAddress inet;
		try{
			inet = InetAddress.getLocalHost();
			System.out.println("Host address is : " + inet.getHostAddress());
			System.out.println("Host name is " + inet.getHostName());
			System.out.print("Address: " + inet.getAddress());
			System.out.println("Address: "+inet.getLocalHost());
		}catch(UnknownHostException e){
			e.printStackTrace();
		}
		
		InetAddress inet1;
		try {
			inet1 = InetAddress.getByName("192.168.1.119");
			System.out.println(inet1);
		} catch (UnknownHostException e) {
			// TODO: handle exception
			e.printStackTrace();
		}
		
		InetAddress [] ina2;
		try{
			ina2 = InetAddress.getAllByName("www.microsoft.com");
			for(int i = 0; i < ina2.length; ++i){
				System.out.println(ina2[i]);
			}
		}catch(UnknownHostException e){
			e.printStackTrace();
		}
	}
}
