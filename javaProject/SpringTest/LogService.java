package SpringTest;

import org.aspectj.lang.annotation.After;
import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.annotation.Before;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;
import org.springframework.stereotype.Component;

/**
 * Created by 12083 on 2016/8/28.
 */

@Component
@Aspect
public class LogService {
    @Before("execution(public * SpringTest.TestClass.say())")
    public void beforeLog(){
        System.out.println("Before.. ");
    }

    @After("execution(public * SpringTest.TestClass.say())")
    public void afterLog(){
        System.out.println("After.. ");
    }

    public static void main(String[] args) {
        ApplicationContext ctx = new ClassPathXmlApplicationContext("classpath:spring.xml");
        TestClass testClass = ctx.getBean(TestClass.class);
        testClass.say();
    }
}
