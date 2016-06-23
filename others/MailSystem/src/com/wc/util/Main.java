package com.wc.util;

import java.io.UnsupportedEncodingException;

public class Main {
	public static void main(String [] args)throws UnsupportedEncodingException {
		MailInfo mailInfo = new MailInfo();
		mailInfo.setMailServerHost("smtp.163.com");
		//mailInfo.setMailServerHost("smtp.qq.com");
		mailInfo.setPort("25");
		mailInfo.setNeedValidate(true);
		mailInfo.setUserName("15520799603@163.com");
		mailInfo.setPassWord("133568ILOVEYOU");
		mailInfo.setFromAddress("15520799603@163.com");
		mailInfo.setToAddress("1208374893@qq.com");
		
//		mailInfo.setUserName("1208374893@qq.com");
//		mailInfo.setPassWord("133568ILOVEYOU");
//		mailInfo.setFromAddress("1208374893@qq.com");
//		mailInfo.setToAddress("15520799603@163.com");
		
		mailInfo.setSubject("使用java来发送邮件");
		mailInfo.setContent("It just a test");
		MailSender mailSender = new MailSender();
		//mailSender.sendAttachmentMail(mailInfo);
		//mailSender.sendHtmlMail(mailInfo);
		//mailSender.sendTextMail(mailInfo);
		if(mailSender.sendAttachmentMail(mailInfo)){
			System.out.println("Mail send success!\n");
		}
	}
}
