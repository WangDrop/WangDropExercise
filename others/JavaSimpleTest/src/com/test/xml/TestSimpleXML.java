package com.test.xml;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

public class TestSimpleXML {
	public static void main(String []args) {
		DocumentBuilderFactory documentBuilderFactory = DocumentBuilderFactory.newInstance(); //静态工厂
		try{
			DocumentBuilder documentBuilder = documentBuilderFactory.newDocumentBuilder();
			File file = new File("C:\\test.xml");
			Document document = documentBuilder.parse(file);
			NodeList nl = document.getElementsByTagName("书");
			for(int i = 0; i < nl.getLength(); ++i){
				Element element = (Element)nl.item(i);
				Node elementAuthor =  (Node)element.getElementsByTagName("作者").item(0);
				Node elementPrice = (Node) element.getElementsByTagName("价格").item(0);
				Node elementPublisher = (Node) element.getElementsByTagName("出版社").item(0);
				
				String author = elementAuthor.getFirstChild().getNodeValue();
				String price = elementPrice.getFirstChild().getNodeValue();
				String publisher = elementPublisher.getFirstChild().getNodeValue();
				
				System.out.println("书记信息如下：---------------");
				System.out.println("作者:" + author);
				System.out.println("价格:" + price);
				System.out.println("出版商: " + publisher);
			}
			
		}catch(FileNotFoundException ex){
			ex.printStackTrace();
		}catch (IOException e) {
			// TODO: handle exception
			e.printStackTrace();
		} catch (ParserConfigurationException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (SAXException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
