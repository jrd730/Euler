/*
	The primes 3, 7, 109, and 673, are quite remarkable. By taking any two 
	primes and concatenating them in any order the result will always be 
	prime. For example, taking 7 and 109, both 7109 and 1097 are prime. 
	The sum of these four primes, 792, represents the lowest sum for a 
	set of four primes with this property.

	Find the lowest sum for a set of five primes for which any two primes 
	concatenate to produce another prime.
*/

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

const unsigned pmax= 99999999;
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
		for (int i = (*it)*(*it); i < pmax; i += *it ){
			primeSieve[i] = 0;
		}
	}
}

unsigned concatenate (unsigned first, unsigned second){
	unsigned n = second;
	while (n){
		first *= 10;
		n /= 10;
	}
	return (first+second);
}

bool catPrimes (unsigned p1, unsigned p2){
	int p12 = concatenate (p1, p2);
	int p21 = concatenate (p2, p1);
	if  (primeSieve[p12] && primeSieve[p21]){
		return true;
	}
	return false;
}

int main (){
	int m = (int)ceil(sqrt (pmax));
	generatePrimes(m);
	fill (primeSieve, primeSieve+pmax, 1);	
	sieve ();
	
	vector <unsigned> primeList;
	for (unsigned i=0; i < m; ++i){ if (primeSieve[i]){ primeList.push_back (i); } }

	unsigned minSum = 9999999;
	for (unsigned i = 1; i < primeList.size(); ++i){	
		for (unsigned j = i+1; j < primeList.size(); ++j){
			if (!catPrimes (primeList[i] , primeList[j])) {continue;}
			for (unsigned k = j+1; k < primeList.size(); ++k){
				if (!catPrimes (primeList[i] , primeList[k])) {continue;}
				if (!catPrimes (primeList[j] , primeList[k])) {continue;}
				for (unsigned l = k+1; l < primeList.size(); ++l){
					if (!catPrimes (primeList[i] , primeList[l])) {continue;}
					if (!catPrimes (primeList[j] , primeList[l])) {continue;}
					if (!catPrimes (primeList[k] , primeList[l])) {continue;}
					for (unsigned m = l+1; m < primeList.size(); ++m){
						if (!catPrimes (primeList[i] , primeList[m])) {continue;}
						if (!catPrimes (primeList[j] , primeList[m])) {continue;}
						if (!catPrimes (primeList[k] , primeList[m])) {continue;}
						if (!catPrimes (primeList[l] , primeList[m])) {continue;}
						int pSum = (primeList[i]+primeList[j]+primeList[k]+primeList[l]+primeList[m]);
						if (pSum < minSum){
							minSum = pSum;
							cout << primeList[i] << " " << primeList[j] << " " << primeList[k] << " " 
									 << primeList[l] << " " << primeList[m] << endl;
							cout << pSum << endl; 
						}
					}	
				}
			}
		}	
	}
	return 0;
}