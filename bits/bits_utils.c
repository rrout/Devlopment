#include <stdio.h>
#include <stdlib.h>

int countBits(unsigned int num)
{
	int count = 0;
	while(num)
	{
		count++;
		num = num & (num-1); // clear the bit
	}
	return count;
	/*
	for( , num; nun = num >> 1)
	{
		if (num & 0x01) //check the bit
		count++;
	}
	return count;
	*/
}

int printBinary(int num)
{
	int tmp = 0;
	if (num)
	{
		tmp = num%2;
		num = num >> 1;
		printBinary(num);
		printf("%d", tmp);
	} else {
		printf("\n");
	}
}

int rotateBits(unsigned int num)
{
	unsigned int tmp = 0;
	int i = 0, j =0;
	for (i = sizeof(num)*8; i, i--)
	{
		tmp = num & 0x01;
		temp = temp << 1;
		num = num >> 1;
	}

	return tmp;
}

/*
 * 001100
 * 111111
 * ------
 * 110011
 * num ^ 0 = num
 * num ^ num = 0
 * num ^ ~num =all but set
 */
int reverseBits(unsigned int num)
{
	unsigned int tmp = num ^ ~num; //this creates all FFF mask
	return (num ^ tmp);
}

int reverseBitFromPos(unsigned int num, int pos, int numBits)
{
	unsigned int tmp = (1 < pos+1) - 1;
	unsigned int mask = tmp << pos;
	unsigned int tmp3 = (~0  >> (pos + numBits)) << (pos + NumBits);
	unsigned int revMask = tmp3 | tmp;

	unsigned int num1 = num & revMask;
	unsigned int num3 = num & mask;
	num3 = num3 ^ mask;
	rturn (num1 | num3);
}
