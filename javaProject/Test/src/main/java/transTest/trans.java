package transTest;

/**
 * Created by 12083 on 2016/9/2.
 */
public class trans {
    public static void main(String[] args) {
        System.out.println(getStr(112233));
    }

    public static String getStr(int num){
        if(num == 0)
            return "";
        return getStr(num / 10) + num % 10;
    }
}
