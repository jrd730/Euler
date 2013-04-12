
/**
 *
	By replacing the 1st digit of *3, it turns out that six of the nine 
	possible values: 13, 23, 43, 53, 73, and 83, are all prime.

	By replacing the 3rd and 4th digits of 56**3 with the same digit, 
	this 5-digit number is the first example having seven primes among
	 the ten generated numbers, yielding the family: 
	 	56003, 56113, 56333, 56443, 56663, 56773, and 56993. 
	 Consequently 56003, being the first member of this family, 
	 is the smallest prime with this property.

	Find the smallest prime which, by replacing part of the number 
	(not necessarily adjacent digits) with the same digit, is part 
	of an eight prime value family.
*/

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <list>
#include <sstream>
using namespace std;

int digitCount(int num){ return (int)ceil(log10(num+1));} // thanks to dre

const int pmax= 999999;
bool primeSieve [pmax];
list <int> primes;
list <int> :: iterator it;
void generatePrimes (int max){
    primes.push_back(2);
    for (int i=3; i < max; i += 2){
        int cap = sqrt(i);
        bool isPrime = true;
        for (int j=2; j <= cap; ++j){
            if (i%j == 0){
                isPrime = false;
                break;
            }
        }
        if (isPrime){
            primes.push_back(i);
        }
    }
}

void sieve (){
	primeSieve[0] = 0;
	primeSieve[1] = 0;
	for (it = primes.begin(); it != primes.end(); ++it){
		for (int i = *it+*it; i < pmax; i += *it ){
			primeSieve[i] = 0;
		}
	}
}

int replaceDigits (int num, int replacer, bool *replace)
{
	int newNum = 0, numCopy = num, j = 0, digit = 0, replacedDigit = -1;
	bool digitsAreSame = true;
	for (int i=1; i <= numCopy; i*=10){
		digit = (num%10);
		if (replace[j] == false){
			newNum += i*digit;
		}
		else{
			newNum += i*replacer;
			if (replacedDigit == -1){
				replacedDigit = digit;
			}
			else if (replacedDigit != digit){
				digitsAreSame = false;
				break;
			}
		}
		num /= 10;
		j++;
	}
	if ( (newNum <= numCopy) || (newNum >= pmax) || !digitsAreSame ) {return 0;}
	else {return newNum;}
}

int NPrimeFamily (int num)
{
	int N = 0, digits = digitCount(num);
	bool replace [digits];
	for ( int digitpos = 1; digitpos < digits; ++digitpos ){
		fill_n (replace, digits-digitpos, 0);
		fill_n (replace+(digits-digitpos), digitpos, 1);
		do{
			int nCount = 1;
			for (int replacer = 0; replacer <= 9; replacer++){
				int replacement = replaceDigits (num, replacer, replace);
				if ((replacement < pmax) && (primeSieve[replacement] == true)){
					//cout << replacement << " ";
					++nCount;
				}
			}
			if (nCount > N) {N = nCount;}
		}while (next_permutation (replace, replace+digits));
	}
	return N;
}

int main ()
{
	generatePrimes(sqrt(pmax));
	fill (primeSieve, primeSieve+pmax, 1);
	sieve ();
	int step = 1;
	for (int i = 0; i < pmax; ++i){
		if (primeSieve[i]){
			//cout << i << ": ";
			int N = NPrimeFamily(i);
			//cout << "\n";
			if (N > step){
				cout << i << " is the first prime that is part of a " << N << " prime family\n";
				step = N;
				if (N >= 8) break;
			}
		}
	}

	// cout << "Elements of prime used to generate sieve:";
	// for (it = primes.begin(); it != primes.end(); it++)
	// 	{ cout << *it << "\t";} cout << "\n";
	// cout << "\n\n";
	
	// cout << "Elements of sieve:";
	// for(int i= 2; i < pmax; ++i) 
	// 	{ if (primeSieve[i]) {cout << i << "\t";}}
	// cout << "\n\n";
	
	// primes.clear ();
	// generatePrimes(pmax);
	// cout << "Elements of prime:";
	// for (it = primes.begin(); it != primes.end(); it++)
	// 	{ cout << *it << "\t";} cout << "\n";
	// cout << "\n\n";

	return 0;
}