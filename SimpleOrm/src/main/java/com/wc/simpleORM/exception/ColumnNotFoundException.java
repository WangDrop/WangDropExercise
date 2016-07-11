package com.wc.simpleORM.exception;

public class ColumnNotFoundException extends RuntimeException {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public ColumnNotFoundException() {
		super();
	}

	public ColumnNotFoundException(String message) {
		super(message);
	}

	public ColumnNotFoundException(String message, Throwable cause) {
		super(message, cause);
	}

	public ColumnNotFoundException(Throwable cause) {
		super(cause);
	}

	protected ColumnNotFoundException(String message, Throwable cause,
			boolean enableSuppression, boolean writableStackTrace) {
		super(message, cause, enableSuppression, writableStackTrace);
	}

}
