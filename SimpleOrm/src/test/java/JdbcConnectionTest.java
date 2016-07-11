import java.sql.Connection;
import java.sql.SQLException;

import org.junit.Test;

import simpleORM.JdbcUtils;

public class JdbcConnectionTest {
	@Test
	public void testConn() {
		Connection connection = JdbcUtils.getConnection();
		System.out.println(connection);
		if (connection != null)
			try {
				connection.close();
			} catch (SQLException e) {
				e.printStackTrace();
			}
	}
}
