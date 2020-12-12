#include "Multiplication.h"

#include <iostream>
using namespace std;



int* Multiplication::RegularMultiplication(int* x, int* y, int x_size, int y_size) {
	int idx_x, idx_y, carry, sum;
	int resSize = x_size + y_size;
	int* res = new int[resSize];

	for (int i = 0; i < resSize; i++)
		res[i] = 0;

	idx_x = idx_y = 0;

	for (int i = x_size - 1; i >= 0; i--)
	{
		carry = 0;
		idx_y = 0;

		for (int j = y_size - 1; j >= 0; j--)
		{
			sum = 0;
			sum = x[i] * y[j] + carry + res[idx_x + idx_y];
			carry = sum / 10;
			res[idx_x + idx_y] = sum % 10;
			idx_y++;
		}

		res[idx_x + idx_y] += carry;
		idx_x++;
	}

	int* reversedRes = new int[resSize];
	for (int i = 0; i < resSize; i++)
		reversedRes[i] = res[resSize - 1 - i];

	delete[] res;
	return reversedRes;
}


void Multiplication::KaratsubaRecursive_tmp(int* x, int* y, long int size, int* res) {
	// x*y = (a*c)*10^n + (b*d)  + ((a+b)*(c+d)-a*c-b*d)* 10^(n/2) 

	//if (size <= 2)
	//{
	//	int * mul = RegularMultiplication(x, y, size, size);
	//	memcpy(res, mul, size * 2 * sizeof(int));
	//	delete[] mul;
	//	return;
	//}

	////if (size == 1) 
	////{	// res size = 2
	////	int mul = x[0] * y[0];
	////	res[1] = mul % 10;
	////	res[0] = mul / 10;
	////	return;
	////}
	////if (size == 2 && x[0] == 0 && y[0] == 0)
	////{	// res size = 4
	////	int mul = x[1] * y[1];
	////	res[3] = mul % 10;
	////	res[2] = mul / 10;
	////	return;
	////}
	//
	//int *a, *b, *c, *d, *ac, *bd;
	//long int aSize, bSize, cSize, dSize, acSize, bdSize;

	//aSize = cSize = size / 2;
	//bSize = dSize = size - (size / 2);
	//acSize = (size / 2) * 2;
	//bdSize = (size - (size / 2)) * 2;

	//a = x;
	//b = x + aSize;
	//c = y;
	//d = y + cSize;
	//ac = res;					
	//bd = res + (size / 2) * 2;	

	//KaratsubaRecursive(a, c, aSize, ac);	// aSize == cSize
	//KaratsubaRecursive(b, d, bSize, bd);	// bSize == dSize

	//long int s_aPlusb = 0, s_cPlusd = 0, s_prodOfSum = 0, s_sumOfProd = 0, s_middle = 0, s_sum1 = 0;

	//// (a+b)
	//int* aPlusb = adder(a, b, aSize, bSize , s_aPlusb);
	//// (c+d)
	//int* cPlusd = adder(c, d, cSize, dSize, s_cPlusd);	

	//if (aPlusb[0] == 0 && cPlusd[0] == 0) // s_aPlusb == s_cPlusd
	//	s_prodOfSum = (s_aPlusb - 1) * 2;
	//else
	//	s_prodOfSum = s_aPlusb * 2;

	//// (a+b)*(c+d)
	//int* prodOfSum = new int[s_prodOfSum]();
	//KaratsubaRecursive(aPlusb, cPlusd, s_aPlusb, prodOfSum);

	//// (a*c)+(b*d)
	//int* sumOfProd = adder(ac, bd, acSize, bdSize, s_sumOfProd);
	//
	//// (a+b)*(c+d) - (a*c)+(b*d)
	//int* middle = subtractor(prodOfSum, sumOfProd, s_prodOfSum, s_sumOfProd, s_middle);


	//// (a*c)*10^n + (b*d)  + ((a+b)*(c+d)-a*c-b*d)* 10^(n/2) 
	//int* sum1 = adder(res, middle, (size * 2) - ((size + 1) / 2), s_middle, s_sum1);
	//

	//for (int i = (size * 2) - ((size + 1) / 2) - 1, j = s_sum1 - 1; i >= 0 && j >= 0; i--, j--) {
	//	res[i] = sum1[j];
	//}

	//delete[] prodOfSum;
	//delete[] sumOfProd;
	//delete[] aPlusb;
	//delete[] cPlusd;
	//delete[] middle;
	//delete[] sum1;
	//return;
}

int* Multiplication::adder(int* x, int* y, long int x_size, long int y_size, long int& resSize)
{
	int *res, sum, carry, x_idx, y_idx, write;
	resSize = ((x_size > y_size) ? x_size : y_size) + 1; // max size + 1
	res = new int[resSize]();

	write = resSize -1;
	x_idx = x_size - 1;
	y_idx = y_size - 1;
	carry = 0;

	while (x_idx >= 0 && y_idx >= 0) {
		sum = carry + x[x_idx] + y[y_idx];
		res[write] = sum % 10;   
		carry = sum / 10;
		write--;
		x_idx--;
		y_idx--;
	}
	while (x_idx >= 0) {
		sum = carry + x[x_idx];
		res[write] = sum % 10;
		carry = sum / 10;
		write--;
		x_idx--;
	}
	while (y_idx >= 0) {
		sum = carry + y[y_idx];
		res[write] = sum % 10;
		carry = sum / 10;
		write--;
		y_idx--;
	}
	if (write >= 0)
		res[write] = carry;
	
	//if (carry)	//{	//	int* resWithCarry = new int[resSize + 1]();	//	memcpy(resWithCarry + 1, res, resSize * sizeof(int));	//	resWithCarry[0] = carry;	//	resSize++;	//	delete[] res;	//	return resWithCarry;	//}
	return res;
}


int* Multiplication::subtractor(int* x, int* y, long int x_size, long int y_size, long int& resSize)
{	//Assuming the x > y
	int *res, sum, carry = 0, x_idx, y_idx, write;
	resSize = ((x_size > y_size) ? x_size : y_size); // max size
	res = new int[resSize];

	write = resSize - 1;
	x_idx = x_size - 1;
	y_idx = y_size - 1;

	while (x_idx >= 0 && y_idx >= 0) {		
		sum = x[x_idx] - y[y_idx] + carry;
		res[write] = (10 + sum) % 10;  // ? sum % 10;
		carry = ((x[x_idx] - y[y_idx] + carry) < 0) ? -1 : 0;
		write--;
		x_idx--;
		y_idx--;
	}
	while (x_idx >= 0) { 
		sum = x[x_idx] + carry;
		res[write] = (10 + sum) % 10;  // ? sum % 10;
		carry = ((x[x_idx] + carry) < 0) ? -1 : 0;
		write--;
		x_idx--;
	}

	return res;
}


void Multiplication::KaratsubaIterative() {

}

void Multiplication::printIntArr(int * arr, int size) {
	int j = 0;
	//for (j = 0; (j < size - 1) && (arr[j] == 0); j++) { // skip all leading zero's
	//}
	for (int i = j; i < size; i++)
		cout << arr[i];
	cout << endl;
}