package com.wc.model;

/**
 * Guashi entity. @author MyEclipse Persistence Tools
 */

public class Guashi implements java.io.Serializable {

	// Fields

	private Integer id;
	private Users users;

	// Constructors

	/** default constructor */
	public Guashi() {
	}

	/** full constructor */
	public Guashi(Users users) {
		this.users = users;
	}

	// Property accessors

	public Integer getId() {
		return this.id;
	}

	public void setId(Integer id) {
		this.id = id;
	}

	public Users getUsers() {
		return this.users;
	}

	public void setUsers(Users users) {
		this.users = users;
	}

}