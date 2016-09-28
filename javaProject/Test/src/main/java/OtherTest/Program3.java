package OtherTest;

/**
 * Created by 12083 on 2016/9/12.
 */

import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class Program3 {


    private static long blackString(String prefix, int n, Map<String, Long> m) {

        if (n == 0) {
            return 1;
        }

        String key = prefix + n;
        if (m.containsKey(key)) {
            return m.get(key);
        }

        long result = 0;
        if (prefix.length() <= 1) {
            result += blackString(prefix + "A", n - 1, m);
            result += blackString(prefix + "B", n - 1, m);
            result += blackString(prefix + "C", n - 1, m);
        } else {
            char c1 = prefix.charAt(0);
            char c2 = prefix.charAt(1);

            if (c1 == c2) {
                result += blackString(c2 + "A", n - 1, m);
                result += blackString(c2 + "B", n - 1, m);
                result += blackString(c2 + "C", n - 1, m);
            } else if ((c1 == 'A' && c2 == 'B') || (c1 == 'B' && c2 == 'A')) {
                result += blackString(c2 + "A", n - 1, m);
                result += blackString(c2 + "B", n - 1, m);
            } else if ((c1 == 'A' && c2 == 'C') || (c1 == 'C' && c2 == 'A')) {
                result += blackString(c2 + "A", n - 1, m);
                result += blackString(c2 + "C", n - 1, m);
            } else if ((c1 == 'B' && c2 == 'C') || (c1 == 'C' && c2 == 'B')) {
                result += blackString(c2 + "B", n - 1, m);
                result += blackString(c2 + "C", n - 1, m);
            }
        }
        m.put(key, result);
        return result;

    }


    public static void main(String[] args) {


        Scanner scanner = new Scanner(System.in);

        while (scanner.hasNextInt()) {
            int n = scanner.nextInt();
            Map<String, Long> m = new HashMap<String, Long>();
            System.out.println(blackString("", n, m));
        }
    }

}