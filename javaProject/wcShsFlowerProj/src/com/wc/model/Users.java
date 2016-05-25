package com.wc.model;

import java.util.HashSet;
import java.util.Set;

/**
 * Users entity. @author MyEclipse Persistence Tools
 */

public class Users implements java.io.Serializable {

	// Fields

	private Integer userid;
	private String username;
	private String password;
	private String role;
	//private Set guashis = new HashSet(0);
	private Guashi guashi;
	private Userdetial userdetial;
	private Set orderses = new HashSet(0);

	// Constructors

	/** default constructor */
	public Users() {
	}

	/** full constructor */
	public Users(String username, String password, String role, Guashi guashi,
			Userdetial userdetial, Set orderses) {
		this.username = username;
		this.password = password;
		this.role = role;
		this.guashi = guashi;
		this.userdetial = userdetial;
		this.orderses = orderses;
	}

	// Property accessors

	public Integer getUserid() {
		return this.userid;
	}

	public void setUserid(Integer userid) {
		this.userid = userid;
	}

	public String getUsername() {
		return this.username;
	}

	public void setUsername(String username) {
		this.username = username;
	}

	public String getPassword() {
		return this.password;
	}

	public void setPassword(String password) {
		this.password = password;
	}

	public String getRole() {
		return this.role;
	}

	public void setRole(String role) {
		this.role = role;
	}

	public Guashi getGuashis() {
		return this.guashi;
	}

	public void setGuashis(Guashi guashi) {
		this.guashi = guashi;
	}

	public Userdetial getUserdetial() {
		return this.userdetial;
	}

	public void setUserdetial(Userdetial userdetial) {
		this.userdetial = userdetial;
	}

	public Set getOrderses() {
		return this.orderses;
	}

	public void setOrderses(Set orderses) {
		this.orderses = orderses;
	}

}