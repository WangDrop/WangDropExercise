int add(int a, int b)
{
	if (b == 0)
		return a;
	int sum = a ^ b;
	int carry = a & b;
	return add(sum, carry << 1);
}