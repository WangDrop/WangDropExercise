package CodeTest;

/**
 * Created by 12083 on 2016/9/5.
 */
public class jindongTest {
    /**
     *
     * @param str : str
     * @param len : len
     * @return the len of the new str
     */
    int FormatString(char str[], int len) {
        if (len <= 0)
            return 0;
        int p1 = 0, p2 = 0;
        if (str[0] == ' ') {
            while (p2 < len && str[p2] == ' ')
                ++p2;
            str[p1++] = str[p2++];
        }
        while(p2 < len){
            if(str[p2] != ' '){
                str[p1++] = str[p2++];
            }else{
                while(p2 < len && str[p2] == ' ')
                    ++p2;
                if(p2 == len)
                    break; //最后的空格已经去除了
                str[p1++] = ' ';
                str[p1++] = str[p2++];
            }
        }
        return p1;
    }

    public static void main(String[] args) {
        String s = "  i    am a      little boy.    ";
        char str[] = s.toCharArray();
        int len = new jindongTest().FormatString(str, str.length);
        for(int i = 0; i < len; ++i){
            System.out.print(str[i]);
        }
    }
}
