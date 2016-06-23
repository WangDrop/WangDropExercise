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
		DocumentBuilderFactory documentBuilderFactory = DocumentBuilderFactory.newInstance(); //��̬����
		try{
			DocumentBuilder documentBuilder = documentBuilderFactory.newDocumentBuilder();
			File file = new File("C:\\test.xml");
			Document document = documentBuilder.parse(file);
			NodeList nl = document.getElementsByTagName("��");
			for(int i = 0; i < nl.getLength(); ++i){
				Element element = (Element)nl.item(i);
				Node elementAuthor =  (Node)element.getElementsByTagName("����").item(0);
				Node elementPrice = (Node) element.getElementsByTagName("�۸�").item(0);
				Node elementPublisher = (Node) element.getElementsByTagName("������").item(0);
				
				String author = elementAuthor.getFirstChild().getNodeValue();
				String price = elementPrice.getFirstChild().getNodeValue();
				String publisher = elementPublisher.getFirstChild().getNodeValue();
				
				System.out.println("�����Ϣ���£�---------------");
				System.out.println("����:" + author);
				System.out.println("�۸�:" + price);
				System.out.println("������: " + publisher);
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
