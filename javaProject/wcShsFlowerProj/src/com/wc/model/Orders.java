package com.wc.model;

import java.util.Date;
import java.util.HashSet;
import java.util.Set;

/**
 * Orders entity. @author MyEclipse Persistence Tools
 */

public class Orders implements java.io.Serializable {

	// Fields

	private Integer orderid;
	private Users users;
	private Date orderdate;
	private Set orderitems = new HashSet(0); //一个orders对应于多个订单项

	// Constructors

	/** default constructor */
	public Orders() {
	}

	/** full constructor */
	public Orders(Users users, Date orderdate, Set orderitems) {
		this.users = users;
		this.orderdate = orderdate;
		this.orderitems = orderitems;
	}

	// Property accessors

	public Integer getOrderid() {
		return this.orderid;
	}

	public void setOrderid(Integer orderid) {
		this.orderid = orderid;
	}

	public Users getUsers() {
		return this.users;
	}

	public void setUsers(Users users) {
		this.users = users;
	}

	public Date getOrderdate() {
		return this.orderdate;
	}

	public void setOrderdate(Date orderdate) {
		this.orderdate = orderdate;
	}

	public Set getOrderitems() {
		return this.orderitems;
	}

	public void setOrderitems(Set orderitems) {
		this.orderitems = orderitems;
	}

}