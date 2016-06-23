package com.wc.TestJUnit;

import junit.framework.Assert;

import org.junit.After;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

public class TestPerson {
	Person person;
	@Before
	public void before(){ //before以及after主要用于资源的创建和销毁
		person = new Person();
	}
	@Test
	public void testRun(){
		person = new Person();
		Assert.assertEquals(person.run(), "run");
		Assert.assertNotNull(person);
	}
	
	@Test
	public void testEat(){
		person = new Person();
		Assert.assertEquals(person.eat(), "eat");
	}
	
	@After
	public void after(){
		person = null;
	}
}
