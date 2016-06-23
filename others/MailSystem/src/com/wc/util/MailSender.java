package com.wc.util;

import java.util.Properties;
import java.io.File;
import java.io.IOException;
import java.io.OutputStream;
import java.io.UnsupportedEncodingException;

import javax.mail.Authenticator;

import java.util.Date;    
import java.util.Properties;   

import javax.activation.DataHandler;
import javax.activation.DataSource;
import javax.activation.FileDataSource;
import javax.mail.Address;   
import javax.mail.BodyPart;    
import javax.mail.Message;    
import javax.mail.MessagingException;    
import javax.mail.Multipart;    
import javax.mail.Session;    
import javax.mail.Transport;    
import javax.mail.internet.InternetAddress;    
import javax.mail.internet.MimeBodyPart;    
import javax.mail.internet.MimeMessage;    
import javax.mail.internet.MimeMultipart;    
import javax.mail.internet.MimeUtility;
import javax.naming.AuthenticationException;
import javax.xml.crypto.dsig.keyinfo.RetrievalMethod;

public class MailSender {
	/**
	 * ���ı�����ʽ�������ʼ�
	 * @param MailInfo : the information of the mail
	 */
	public boolean sendTextMail(MailInfo mailInfo){
		Authenticator mailAuthenticator = null;
		Properties properties = mailInfo.getProperties();
		if(mailInfo.isNeedValidate()){
			mailAuthenticator = new MailAuthenticator(mailInfo.getUserName(), mailInfo.getPassWord());
		}
		// �����ʼ��Ự���Ժ�������֤������һ�������ʼ���session
		Session sendMailSession = Session.getDefaultInstance(properties, mailAuthenticator);
		try{
			Message message = new MimeMessage(sendMailSession);
			Address from = new InternetAddress(mailInfo.getFromAddress());
			Address to = new InternetAddress(mailInfo.getToAddress());
			message.setFrom(from);
			message.setRecipient(Message.RecipientType.TO, to);
			message.setSubject(mailInfo.getSubject());
			message.setSentDate(new Date());
			message.setText(mailInfo.getContent());
			Transport.send(message);
			return true;
		}catch(MessagingException e){
			e.printStackTrace();
		}
		return false;
	}
	
	/**
	 * ��HTML����ʽ������mail
	 */
	public boolean sendHtmlMail(MailInfo mailInfo){
		Authenticator mailAuthenticator = null;
		Properties properties = mailInfo.getProperties();
		if(mailInfo.isNeedValidate()){
			mailAuthenticator = new MailAuthenticator(mailInfo.getUserName(), mailInfo.getPassWord());
		}
		Session sendMailSession = Session.getDefaultInstance(properties, mailAuthenticator);
		try{
			Message message = new MimeMessage(sendMailSession);
			Address from = new InternetAddress(mailInfo.getFromAddress());
			Address to = new InternetAddress(mailInfo.getToAddress());
			message.setFrom(from);
			message.setRecipient(Message.RecipientType.TO, to);
			message.setSubject(mailInfo.getSubject());
			message.setSentDate(new Date());
			Multipart multipart = new MimeMultipart();
			BodyPart html = new MimeBodyPart();
			html.setContent(mailInfo.getContent(), "text/html; charset=utf-8");
			multipart.addBodyPart(html);
			message.setContent(multipart);
			Transport.send(message);
			return true;
		}catch(MessagingException e){
			e.printStackTrace();
		}
		return false;
	}
	
	/**
	 * ʹ��html����ʽ�������ʼ�������������������
	 */
	public boolean sendAttachmentMail(MailInfo mailInfo) {
		Authenticator mailAuthenticator = null;
		Properties properties = mailInfo.getProperties();
		if(mailInfo.isNeedValidate()){
			mailAuthenticator =  new MailAuthenticator(mailInfo.getUserName(), mailInfo.getPassWord());
		}
		Session session = Session.getDefaultInstance(properties, mailAuthenticator);
		try{
			Message message = new MimeMessage(session);
			Address from = new InternetAddress(mailInfo.getFromAddress());
			Address to = new InternetAddress(mailInfo.getToAddress());
			message.setFrom(from);
			message.setRecipient(Message.RecipientType.TO, to);
			message.setSubject(mailInfo.getSubject());
			message.setSentDate(new Date());
			
			Multipart multipart = new MimeMultipart();
			MimeBodyPart mimeBodyPart = new MimeBodyPart();
			mimeBodyPart.setText(mailInfo.getContent());
			multipart.addBodyPart(mimeBodyPart);
			
			MimeBodyPart attrBodyPart = new MimeBodyPart();
			DataSource dataSource = new FileDataSource(new File("C:\\Users\\WC\\Desktop\\drvier_all.rar"));
			attrBodyPart.setDataHandler(new DataHandler(dataSource));
			
			//���ñ����ʽ��ʹ�ø�������������ʾ������
			attrBodyPart.setFileName(MimeUtility.encodeText("drvier_all.rar", "gbk", "B"));
			multipart.addBodyPart(attrBodyPart);
			
			message.setContent(multipart, "text/html;charset=gbk");
			Transport.send(message);
			return true;
		}catch(MessagingException e){
			e.printStackTrace();
		} catch (UnsupportedEncodingException e) {
			e.printStackTrace();
		}
		return false;
	}
}
