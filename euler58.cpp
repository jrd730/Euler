
/**
	Starting with 1 and spiralling anticlockwise in the following way, 
	a square spiral with side length 7 is formed.

	37 36 35 34 33 32 31
	38 17 16 15 14 13 30
	39 18  5  4  3 12 29
	40 19  6  1  2 11 28
	41 20  7  8  9 10 27
	42 21 22 23 24 25 26
	43 44 45 46 47 48 49

	It is interesting to note that the odd squares lie along the bottom right diagonal, 
	but what is more interesting is that 8 out of the 13 numbers lying along both 
	diagonals are prime; that is, a ratio of 8/13 ≈ 62%.

	If one complete new layer is wrapped around the spiral above, a square spiral with 
	side length 9 will be formed. If this process is continued, what is the side length 
	of the square spiral for which the ratio of primes along both diagonals first falls below 10%?

*/


#include <cstdlib>
#include <cmath>
#include <iostream>
#include <list>
#include <string>
using namespace std;

bool isPrime (unsigned long long num)
{
	if (num%2 == 0) return false;
	unsigned long long max = sqrt(num);
    for (unsigned int j=3; j <= max; j += 2){
        if (num%j == 0){
            return false;
        }
    }
    return true;
}

int main (int arc, char** arv)
{ 	
	int r = 0, diagonals = 1, primes = 0;
	unsigned long long dl=0, ul=0, ur=0;
	long double primeRatio = 0, range = 0;
	if (arc > 1) range = atof(arv[1]);
	else range = .1;
	//
	// This method finds the diagonals based on the current spiral ring.
	// The down right diagonal is ignored since it will never be prime.
	//
	do{
		r++;
		diagonals += 4;
		ur = (4*r*r)-(2*r)+1; // up-right diagonal
		ul = (4*r*r)+1;       // up-left diagonal 
		dl = (4*r*r)+(2*r)+1; // down-left diagonal
		if (isPrime(ur)) primes++;
		if (isPrime(ul)) primes++;
		if (isPrime(dl)) primes++;
		primeRatio = (long double)primes/(long double)diagonals;
		//cout << "Ring: " << r << " Side Length: " << (2*r+1) << endl
		//	 << primes << " primes / " << diagonals << " diagonals = " << primeRatio << endl;
	}while ( primeRatio > range );
	cout << "Ring: " << r << " Side Length: " << (2*r+1) << endl
		 << primes << " primes / " << diagonals << " diagonals = " << primeRatio << endl;
	
	int sl = 2; 
	primes = 0;
	int start = 3;
	//
	// This method for finding diagonals starts on the first corner (3) 
	// and increments by the distance to the next corner (2) three times.
	// For each ring of the spiral, the distance to next corner increases
	// by two.
	//
	do{
		for (int i=0; i<3; i++){
			if (isPrime (start)){
				primes++;
			}
			start += sl;
		}
		sl += 2;
		start += sl;
		primeRatio = (double)primes / (double)((2*sl)+1);
		//cout  << "Primes: " << primes << " Side length: " << sl << endl;
	}while (primeRatio > range);
	cout << "Primes: " << primes << " Side Length: " << sl+1 << endl;
 return 0;
}