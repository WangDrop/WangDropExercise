package com.test.file;

import java.nio.CharBuffer;

public class BufferTest {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		CharBuffer charBuffer = CharBuffer.allocate(8);
		charBuffer.put('a').put('b').put('c');
		System.out.println(charBuffer.capacity());
		System.out.println(charBuffer.limit());
		System.out.println(charBuffer.position());
		CharBuffer sharedBuffer = charBuffer.slice(); //ʹ��sharedBuffer��charBuffer����һƬ�ڴ�ռ䣬����capicity�ĺ;���8�����Կ���ӡ���
		System.out.println(sharedBuffer.capacity());
		System.out.println(sharedBuffer.limit());
		System.out.println(sharedBuffer.position());
	}

}
