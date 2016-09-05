package protostuffTest;

import cglibTest.Person;
import com.dyuproject.protostuff.LinkedBuffer;
import com.dyuproject.protostuff.ProtobufIOUtil;
import com.dyuproject.protostuff.ProtostuffIOUtil;
import com.dyuproject.protostuff.Schema;
import com.dyuproject.protostuff.runtime.RuntimeSchema;
import org.objenesis.Objenesis;
import org.objenesis.ObjenesisStd;

import java.io.*;


/**
 * Created by 12083 on 2016/8/27.
 */
public class Main {
    public static void main(String[] args) throws Exception {
        Person person = new Person();
        person.setHobby("basketbal");
        person.setAge(21);
        person.setName("WangCheng");

        Class<?> clazz = person.getClass();

        Schema schema = RuntimeSchema.createFrom(clazz);
        Objenesis objenesis = new ObjenesisStd(true);
        LinkedBuffer buffer = LinkedBuffer.allocate(LinkedBuffer.DEFAULT_BUFFER_SIZE);
        byte[] bytes = ProtobufIOUtil.toByteArray(person, schema, buffer);
        System.out.println("after protostuff serilize, size is: " + bytes.length);

        Object obj = objenesis.newInstance(clazz);
        ProtostuffIOUtil.mergeFrom(bytes, obj, schema);

        System.out.println(obj);


        //下面是java自带的序列化的大小
        File file = new File("test.txt");
        if (!file.exists()) {
            file.createNewFile();
        }
        ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(file));

        oos.writeObject(person);

        System.out.println("the jdk serilize file size is " + file.length() + "Bytes");

        oos.close();

        ObjectInputStream ois = new ObjectInputStream(new FileInputStream(file));

        Person newPerson = (Person) ois.readObject();

        System.out.println(newPerson);
    }
}
