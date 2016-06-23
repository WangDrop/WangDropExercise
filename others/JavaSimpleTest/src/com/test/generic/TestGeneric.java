package com.test.generic;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;

import javax.sql.rowset.serial.SerialArray;

public class TestGeneric {
	public static void main(String [] args) {
		Map<String, Integer> grade = new HashMap<String, Integer>();
		grade.put("����",67);
		grade.put("��ѧ", 99);
		grade.put("Ӣ��", 79);
		Set<Map.Entry<String, Integer>> set = grade.entrySet();
		Iterator<Map.Entry<String, Integer>> iter = set.iterator();
		while(iter.hasNext()){
			Map.Entry<String, Integer> en = iter.next();
			System.out.println(en.getKey() + ", " + en.getValue());
		}
		
		//��ǿforѭ������
		for(Map.Entry<String, Integer> entry : grade.entrySet()){
			System.out.println(entry.getKey() + ":" + entry.getValue());
		}
		
	}
	
	//�Զ��巺�� 
	public <T> T a(T t){
		return t;
		
	}
}

class TestGen<T>{
	T name;
	T getName(){
		return name;
	}
	public void swap(T arr[], int pos1, int pos2){
		T tmp = arr[pos1];
		arr[pos1] = arr[pos2];
		arr[pos2] = tmp;
	}
}
