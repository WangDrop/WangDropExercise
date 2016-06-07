package com.wc.model;

import java.util.Date;

/**
 * Userdetial entity. @author MyEclipse Persistence Tools
 */

public class Userdetial implements java.io.Serializable {

	// Fields

	private Integer userid;
	private Users users;
	private Byte xb;
	private String truename;
	private Date csrq;
	private String phone;
	private String email;
	private String address;

	// Constructors

	/** default constructor */
	public Userdetial() {
	}

	/** minimal constructor */
	public Userdetial(Users users) {
		this.users = users;
	}

	/** full constructor */
	public Userdetial(Users users, Byte xb, String truename, Date csrq,
			String phone, String email, String address) {
		this.users = users;
		this.xb = xb;
		this.truename = truename;
		this.csrq = csrq;
		this.phone = phone;
		this.email = email;
		this.address = address;
	}

	// Property accessors

	public Integer getUserid() {
		return this.userid;
	}

	public void setUserid(Integer userid) {
		this.userid = userid;
	}

	public Users getUsers() {
		return this.users;
	}

	public void setUsers(Users users) {
		this.users = users;
	}

	public Byte getXb() {
		return this.xb;
	}

	public void setXb(Byte xb) {
		this.xb = xb;
	}

	public String getTruename() {
		return this.truename;
	}

	public void setTruename(String truename) {
		this.truename = truename;
	}

	public Date getCsrq() {
		return this.csrq;
	}

	public void setCsrq(Date csrq) {
		this.csrq = csrq;
	}

	public String getPhone() {
		return this.phone;
	}

	public void setPhone(String phone) {
		this.phone = phone;
	}

	public String getEmail() {
		return this.email;
	}

	public void setEmail(String email) {
		this.email = email;
	}

	public String getAddress() {
		return this.address;
	}

	public void setAddress(String address) {
		this.address = address;
	}

}