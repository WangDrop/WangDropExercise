package cglibTest;

import net.sf.cglib.reflect.FastClass;
import net.sf.cglib.reflect.FastMethod;

/**
 * Created by 12083 on 2016/8/27.
 */
public class Main {
    public static void main(String[] args) throws Exception {
        Person person = new Person();
        person.setAge(21);
        person.setName("wangcheng");
        person.setHobby("basketball");
        FastClass fastClass = FastClass.create(Person.class);
        FastMethod fastMethod = fastClass.getMethod("getAge", new Class<?>[]{});
        System.out.println(fastMethod.invoke(person, new Object[]{}));
    }
}
