/*
	In England the currency is made up of pound, £, and pence, p, and there are eight coins in general circulation:

	    1p, 2p, 5p, 10p, 20p, 50p, £1 (100p) and £2 (200p).

	It is possible to make £2 in the following way:

	    1×£1 + 1×50p + 2×20p + 1×5p + 1×2p + 3×1p

	How many different ways can £2 be made using any number of coins?
*/

#include <iostream>
using namespace std;

int coinAmounts [8] = {200, 100, 50, 20, 10, 5, 2, 1};

int countCoinSums (int amount, int startCoin=0)
{
	int count = 0;
	for (int i = startCoin; i < 8; i++){
		int difference = (amount - coinAmounts[i]);
		if (difference == 0){
			count++;
		}
		else if (difference > 0){
			count += countCoinSums (difference, i);
		}
	}
	return count;
}

int main ()
{
	cout << "There are " << countCoinSums(200) << " ways to make 2 pounds\n";
	return 0;
}