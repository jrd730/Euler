/*
	The number 145 is well known for the property that the sum of the factorial of its digits is equal to 145:

	1! + 4! + 5! = 1 + 24 + 120 = 145

	Perhaps less well known is 169, in that it produces the longest chain of numbers that link back to 169; 
	it turns out that there are only three such loops that exist:

	169 → 363601 → 1454 → 169
	871 → 45361 → 871
	872 → 45362 → 872

	It is not difficult to prove that EVERY starting number will eventually get stuck in a loop. For example,

	69 → 363600 → 1454 → 169 → 363601 (→ 1454)
	78 → 45360 → 871 → 45361 (→ 871)
	540 → 145 (→ 145)

	Starting with 69 produces a chain of five non-repeating terms, but the longest non-repeating chain with 
	a starting number below one million is sixty terms.

	How many chains, with a starting number below one million, contain exactly sixty non-repeating terms?

*/

#include <iostream>
#include <set>
using namespace std;

int factorials [] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};

unsigned sumDigitFactorials (unsigned n)
{
	int sum = 0;
	while (n){
		sum += factorials[n%10];
		n /= 10;
	}
	return sum;
}

int main ()
{
	unsigned N = 0;
	for (unsigned i=1; i < 1000000; i++){
		set <unsigned> chain;
		chain.insert (i);
		bool nonRepeating = true;
		unsigned next = sumDigitFactorials (i);
		//cout << i <<  ": -> ";
		while (nonRepeating){
			if (chain.find(next) == chain.end()){
				chain.insert(next);
				//cout << next << " -> ";
				next = sumDigitFactorials(next);
			}
			else{
				//cout << next;
				nonRepeating = false;
				if (chain.size() == 60){
					N++;
				}
			}
		}
		//cout << "\n\n";
	}
	cout << N << endl;
	return 0;
}