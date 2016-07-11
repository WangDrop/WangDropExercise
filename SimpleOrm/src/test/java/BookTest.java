import java.util.Date;

import org.junit.Test;

import simpleORM.mysqlDao;
import simpleORM.mysqlDaoImpl;

public class BookTest {
	private mysqlDao<Book> bookDao = new mysqlDaoImpl<Book>();

	@Test
	public void testInsert() {
		Book book = new Book();
		book.setId(2);
		book.setAuthor("Jxiaolun");
		book.setDate(new Date());
		book.setIsbn("1002");
		book.setName("c++Premier");
		book.setPrice(100);
		book.setPublisher("UESTC");
		try {
			bookDao.add(book);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	@Test
	public void testDelete() {
		int id = 1;
		Book book = new Book();
		try {
			bookDao.delete(id, book.getClass());
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	@Test
	public void testUpdate() {
		Book book = new Book();
		book.setId(2);
		book.setAuthor("WC");
		book.setDate(new Date());
		book.setIsbn("1002");
		book.setName("c++Premier");
		book.setPublisher("华中科技大学出版社");
		book.setPrice(99.0);
		try {
			bookDao.update(book);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	@Test
	public void testSelect() {
		Book book = null;
		try {
			book = (Book) bookDao.select(2, Book.class);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		System.out.println(book);
	}
}
