import java.util.Date;

import com.wc.annotation.Column;
import com.wc.annotation.Entity;
import com.wc.annotation.Id;

@Entity("books")
public class Book {
	@Id("book_id")
	private Integer id;

	@Column("book_isbn")
	private String isbn;

	@Column("book_name")
	private String name;

	@Column("book_author")
	private String author;

	@Column("book_publisher")
	private String publisher;

	@Column("book_date")
	private Date date;

	@Column("book_price")
	private double price;

	public Integer getId() {
		return id;
	}

	public void setId(Integer id) {
		this.id = id;
	}


	public String getIsbn() {
		return isbn;
	}

	public void setIsbn(String isbn) {
		this.isbn = isbn;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getAuthor() {
		return author;
	}

	public void setAuthor(String author) {
		this.author = author;
	}

	public String getPublisher() {
		return publisher;
	}

	public void setPublisher(String publisher) {
		this.publisher = publisher;
	}

	public Date getDate() {
		return date;
	}

	public void setDate(Date date) {
		this.date = date;
	}

	public double getPrice() {
		return price;
	}

	public void setPrice(double price) {
		this.price = price;
	}

	@Override
	public String toString() {
		return "Book [id=" + id + ", isbn=" + isbn + ", name=" + name
				+ ", author=" + author + ", publisher=" + publisher + ", date="
				+ date + ", price=" + price + "]";
	}

}
