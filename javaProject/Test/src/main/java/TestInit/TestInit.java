package TestInit;


class SuperClass {
    static {
        System.out.println("super");
    }

    public static int value = 123;

}

class SubClass extends SuperClass {
    static {
        System.out.println("sub");
    }

}

public class TestInit {
    public static void main(String[] args) {
        System.out.println(SubClass.value);
    }
}