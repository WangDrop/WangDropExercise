#include <iostream>
using namespace std;
int bit_add(int a, int b){
	int carry = a & b;
	int noCarrySum = a ^ b;
	if (carry)        
		return bit_add(carry << 1, noCarrySum);
	else        
		return  noCarrySum;
}

int bit_multiply7(int a)
{    
	bit_add(a<<2, bit_add(a<<1, a));
}

int main() 
{    
	int a = 8;    
	cout << bit_multiply7(a) <<endl;    
	return 0;
}