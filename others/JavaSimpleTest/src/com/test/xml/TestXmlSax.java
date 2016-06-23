package com.test.xml;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import javax.swing.text.html.HTMLDocument.HTMLReader.SpecialAction;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.XMLReader;
import org.xml.sax.helpers.DefaultHandler;

class Book{
	private String name;
	private String publisher;
	private String price;
	private String author;
	
	
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public String getPublisher() {
		return publisher;
	}
	public void setPublisher(String publisher) {
		this.publisher = publisher;
	}
	public String getPrice() {
		return price;
	}
	public void setPrice(String price) {
		this.price = price;
	}
	public String getAuthor() {
		return author;
	}
	public void setAuthor(String author) {
		this.author = author;
	}
	
}

public class TestXmlSax extends DefaultHandler {
	private List list = new ArrayList();
	private String currTag;
	private Book book;
	
	@Override
	public void startElement(String url, String localName, String name, Attributes attributes)throws SAXException{
		currTag = name;
		if("书".equals(currTag)){
			book = new Book();
		}
	}
	
	@Override
	public void characters(char[] ch, int start, int length)throws SAXException{
		if("出版社".equals(currTag)){
			String publisher = new String (ch, start, length);
			book.setPublisher(publisher);
		}else if("价格".equals(currTag)){
			String price = new String(ch, start, length);
			book.setPrice(price);
		}else if("作者".equals(currTag)){
			String author = new String(ch, start, length);
			book.setAuthor(author);
		}
	}
	
	@Override
	public void endElement(String url, String localName, String name) throws SAXException{
		if("书".equals(name)){
			list.add(book);
			book = null;
		}
		currTag = null;
	}
	
	public List getBooks() {
		return list;
	}
	
	
	
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		SAXParserFactory saxParserFactorysFactory = SAXParserFactory.newInstance();
		SAXParser saxParser;
		try {
			saxParser = saxParserFactorysFactory.newSAXParser();
			XMLReader xmlReader = saxParser.getXMLReader();
			File file = new File("test.xml");
			TestXmlSax testSimpleXML = new TestXmlSax();
			saxParser.parse(file, testSimpleXML);
			List <Book> list = testSimpleXML.getBooks();
			for(Book book : list)
				System.out.println("book publisher: " + book.getPublisher() + " book price: " + book.getPrice() + "book author: "+ book.getAuthor());
		} catch (ParserConfigurationException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		} catch (SAXException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		
		
	}

}
