
/*

	The cube, 41063625 (3453), can be permuted to produce two other cubes: 
	56623104 (3843) and 66430125 (4053). In fact, 41063625 is the smallest 
	cube which has exactly three permutations of its digits which are also cube.

	Find the smallest cube for which exactly five permutations of its digits are cube.

*/
#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <string>
using namespace std;
unsigned long long cubed (unsigned long long n){return n*n*n;}
int main ()
{
	map <string, stack<unsigned long long> > cubes;
	map <string, stack<unsigned long long> > :: iterator it;

	for (unsigned long long i=100; i < 20000; i++){
		unsigned long long c = cubed(i);
		stringstream ss;
		string s;
		ss  << c;
		s = ss.str();
		sort (s.begin(), s.end());
		it = cubes.find (s);
		if (it == cubes.end()){
			stack <unsigned long long> stk;
			stk.push (i);
			cubes[s] = stk;
		}
		else{
			it->second.push (i);
			if (it->second.size () == 5){
				cout << "Solution found " << endl;
				for (; it->second.size() > 0; it->second.pop()){
					cout << it->second.top() << "^3 = " << cubed(it->second.top() ) << endl;
				}
				break;
			}
		}
	}
	return 0;
}