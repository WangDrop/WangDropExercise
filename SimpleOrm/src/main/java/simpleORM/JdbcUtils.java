package simpleORM;

import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Properties;

/*
 * jdbc�����࣬��Ҫ���ڴ������Լ�����PreparedStatement
 * 
 */
public class JdbcUtils {
	private static Connection connection = null;
	private static Properties properties = null;
	static {
		properties = new Properties();
		InputStream inputStream = JdbcUtils.class
				.getResourceAsStream("db.properties");
		try {
			properties.load(inputStream);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	/**
	 * ������ݿ�����
	 * 
	 * @return
	 */
	public static Connection getConnection() {
		try {
			if (connection == null) {
				// ����jdbc����
				Class.forName(properties.getProperty("driverClass"));
				try {
					connection = DriverManager.getConnection(
							properties.getProperty("jdbcUrl"),
							properties.getProperty("username"),
							properties.getProperty("password"));
				} catch (SQLException e) {
					e.printStackTrace();
				}
			}
		} catch (ClassNotFoundException exception) {
			exception.printStackTrace();
		}

		return connection;

	}

	/*
	 * �ͷ���Դ
	 */
	public static void releaseResource(PreparedStatement pstmt, ResultSet rset) {
		if (connection != null) {
			try {
				connection.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		if (pstmt != null) {
			try {
				pstmt.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		if (rset != null) {
			try {
				rset.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
}
