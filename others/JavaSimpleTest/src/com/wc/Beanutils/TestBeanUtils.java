package com.wc.Beanutils;

import java.lang.reflect.InvocationTargetException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;

import org.apache.commons.beanutils.BeanUtils;
import org.apache.commons.beanutils.ConversionException;
import org.apache.commons.beanutils.ConvertUtils;
import org.apache.commons.beanutils.Converter;
import org.apache.commons.beanutils.locale.converters.DateLocaleConverter;
import org.junit.Test;

public class TestBeanUtils {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
	}
	
	@Test
	public void test() throws IllegalAccessException, InvocationTargetException{
		String name = "wangcheng";
		String age = "22";
		String gender = "ÄÐ";
		String birth = "1993-06-08";

		ConvertUtils.register(new DateLocaleConverter(), Date.class);
		
	
		Person person = new Person();
		BeanUtils.setProperty(person, "name", name);
		BeanUtils.setProperty(person, "age", age);
		BeanUtils.setProperty(person, "gender", gender);
		BeanUtils.setProperty(person, "birthDate", birth);

		System.out.println(person.getName());
		System.out.println(person.getAge());
		System.out.println(person.getGender());
		System.out.println(person.getBirthDate());
		
		Map<String, String> propertyMap = new HashMap<String, String>();
		propertyMap.put("name", "wang");
		propertyMap.put("age", "23");
		propertyMap.put("gender", "ÄÐ");
		propertyMap.put("birthDate", "1993-07-08");
		
		ConvertUtils.register(new DateLocaleConverter(), Date.class);
		
		BeanUtils.populate(person, propertyMap);
		System.out.println(person.getName());
		System.out.println(person.getAge());
		System.out.println(person.getGender());
		System.out.println(person.getBirthDate());
	}
}
