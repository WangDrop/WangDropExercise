int bitDivide(int a, int b)
{
	int r = 0, c = b;
	while (a > c)
		c <<= 1;
	while (c >= b){
		r <<= 1;
		if (a >= c){
			r++;
			a -= c;
		}
		c >>= 1;
	}
	return r;
}
