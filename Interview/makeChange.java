/**
 * ��Ǯ���⣬��1�飬�ֱ��кܶ�1�֣�2�֣�5�ֵ�Ӳ�ң�������ж������ҷ���
 * @author WC
 *
 */
public class makeChange {
	public int makeChange(int total, int change) {
		int nextChange = 0;
		switch (change) {
		case 5:
			nextChange = 2;
			break;
		case 2:
			nextChange = 1;
			break;
		default:
			return 1;
		}
		int ways = 0;
		for (int i = 0; i * change <= total; ++i)
			ways += makeChange(total - i * change, nextChange);
		return ways;
	}

	public static void main(String[] args) {
		makeChange changes = new makeChange();
		System.out.println(changes.makeChange(100, 5));
	}
}
