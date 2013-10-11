/*
The proper divisors of a number are all the divisors excluding the number 
itself. For example, the proper divisors of 28 are 1, 2, 4, 7, and 14. As the 
sum of these divisors is equal to 28, we call it a perfect number.

Interestingly the sum of the proper divisors of 220 is 284 and the sum of the
proper divisors of 284 is 220, forming a chain of two numbers. For this reason,
220 and 284 are called an amicable pair.

Perhaps less well known are longer chains. For example, starting with 12496, we 
form a chain of five numbers:

12496 → 14288 → 15472 → 14536 → 14264 (→ 12496 → ...)

Since this chain returns to its starting point, it is called an amicable chain.

Find the smallest member of the longest amicable chain with no element exceeding
one million.
*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

const unsigned N = 1000000;
unsigned next[N];

void divisorsOf (unsigned n, vector <unsigned>& divisors){
  divisors.push_back (1);
  unsigned max = ceil (sqrt (n));
  if (max*max == n && max != 1) divisors.push_back (max);
  for (unsigned i=2; i < max; ++i){
    if (n%i == 0){
      divisors.push_back (i);
      divisors.push_back (n/i);
    }
  }
}

unsigned sumVec (vector <unsigned>& v){
  unsigned sum = 0;
  for (unsigned i = 0; i < v.size(); ++i){
    sum += v[i];
  }
  return sum;
}

void sumDivisorChain (unsigned n, vector <unsigned>& chain, unsigned max)
{
  set <unsigned> visited;
  visited.insert(n);
  chain.push_back (n);
  unsigned sum = n;
  bool chaining = true;
  do{
    if (next[sum] == 0){
      vector <unsigned> div;
      divisorsOf (sum, div);
      unsigned nextSum = sumVec (div);
      next[sum] = nextSum;
      sum = nextSum;
    }
    else {
      sum = next[sum];
    }
    
    if ( (visited.find (sum) != visited.end()) || sum > max){
      chain.push_back (sum);
      chaining = false;
    }else{
      chain.push_back (sum);
      visited.insert (sum);
    }
  }while (chaining);
}

int main ()
{
  fill (next, next+N, 0);
  unsigned longestChain = 0, smallest_member = 9999999;
  for (unsigned i = 2; i <= N; ++i){
    vector <unsigned> chain;
    sumDivisorChain (i, chain, 1000000);
    if (chain[0] == chain[chain.size()-1]){
      if (longestChain < chain.size()){
        smallest_member = 9999999;
        cout << "Chain size: " << chain.size() << endl;
        cout << chain[0];
        for (unsigned i = 1; i < chain.size(); ++i){
          cout << " -> " << chain [i];
        }cout << "\n";
        longestChain = chain.size();
        smallest_member = 
          min (smallest_member, *min_element (chain.begin (), chain.end()));
      }
      else if (longestChain == chain.size()){
        cout << "Chain size: " << chain.size() << endl;
        cout << chain[0];
        for (unsigned i = 1; i < chain.size(); ++i){
          cout << " -> " << chain [i];
        }cout << "\n";
        smallest_member = 
          min (smallest_member, *min_element (chain.begin (), chain.end()));
      }
    }
  }
  cout << smallest_member << endl;
  return 0;
}
