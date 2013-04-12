
/**
	There are exactly ten ways of selecting three from five, 12345:
	123, 124, 125, 134, 135, 145, 234, 235, 245, and 345
	In combinatorics, we use the notation, 5C3 = 10.
	In general,
	nCr = n!/(r!(n−r)!)
		,where r ≤ n, n! = n×(n−1)×...×3×2×1, and 0! = 1.
	It is not until n = 23, that a value exceeds one-million: 23C10 = 1144066.
	How many, not necessarily distinct, values of  nCr, for 1 ≤ n ≤ 100, are greater than one-million?
*/


#include <iostream>
using namespace std;

unsigned long long nChooseK (int n, int k)
{
	// pick k to be the larger of k and (n-k)
	if (k < (n-k)){
		k = (n-k);
	}
	int top [n+1];
	int bottom [k+1];
	int i=0;
	for (i=0; i <= n; i++){
		top[i] = (i > k);
	}
	for (i=0; i <= k; i++){
		bottom[i] = (i <= (n-k));
	}
	for (i = k; i >= 2; i--){
		if (bottom[i] > 0){
			int multiple = i;
			for (; multiple <= n;){
				if (top[multiple] > 0){
					top[multiple/i]++;
					top[multiple]--;
					bottom[i]--;
					break;
				}
				multiple += i;
			}
		}
	}

	// for (i=2; i <= k; i++){
	// 	if (bottom[i] > 0) cout << i << "*" << bottom[i] << " + ";
	// }cout << endl;

	// for (i=2; i <= n; i++){
	// 	if (top[i] > 0)cout << i << "*" << top[i] << " + ";
	// } cout << endl;

	unsigned long long bottomProduct = 1;
	for (i=2; i <= k; i++){
		for (;bottom[i] > 0; bottom[i]--){
			bottomProduct *= i;
		}
	}

	unsigned long long topProduct = 1;
	for (i=2; i <= n; i++){
		for (;top[i] > 0; top[i]--){
			topProduct *= i;
		}
	}

	unsigned long long result = topProduct/bottomProduct;
	//cout << topProduct << "/" << bottomProduct << " = " << result << endl;
	return result;
}

int main  ()
{
	int maxN = 100;
	int overMillion = 0;
	for (int i = 1; i <= maxN; i++){
		for (int j = 1; j <= i; j++){
			//cout << i << " choose " << j << endl;
			if (nChooseK (i, j) > 1000000){
				if (i & 1){
					overMillion += 2*(i/2 - j) + 2;
				}
				else{
					overMillion += 2*(i/2 - j) + 1;
				}
				
				break;
			}

		}
	}
	cout << overMillion << " distinct values over 1,000,000\n";
	return 0;
}