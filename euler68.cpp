/*
	Consider the following "magic" 3-gon ring, filled with the numbers 1 to 6, and each line adding to nine.

	Working clockwise, and starting from the group of three with the numerically lowest external node
	(4,3,2 in this example), each solution can be described uniquely. For example, the above solution 
	can be described by the set: 4,3,2; 6,2,1; 5,1,3.

	It is possible to complete the ring with four different totals: 9, 10, 11, and 12. There are eight 
	solutions in total.
	
	Total	Solution Set
	9	4,2,3; 5,3,1; 6,1,2
	9	4,3,2; 6,2,1; 5,1,3
	10	2,3,5; 4,5,1; 6,1,3
	10	2,5,3; 6,3,1; 4,1,5
	11	1,4,6; 3,6,2; 5,2,4
	11	1,6,4; 5,4,2; 3,2,6
	12	1,5,6; 2,6,4; 3,4,5
	12	1,6,5; 3,5,4; 2,4,6

	By concatenating each group it is possible to form 9-digit strings; the maximum string for a 3-gon 
	ring is 432621513.

	Using the numbers 1 to 10, and depending on arrangements, it is possible to form 16- and 17-digit 
	strings. What is the maximum 16-digit string for a "magic" 5-gon ring?
*/
#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
using namespace std;

int N = 5;
int nodeCount = 2*N;

bool verify (int* nGon, int& sum)
{
	sum = nGon[N] + nGon[0] + nGon[1];
	for (int i = N+1; i < nodeCount; i++){
		if (nGon[i] + nGon[i-N] + nGon[(i-N+1)%N] == sum) continue;
		else return false;
	}
	return true;
}

string nGonToStr (int* nGon)
{
	int minExtern = 999999;
	int minExternIndex = 0;
	for (int i = N; i < nodeCount; i++){
		if (nGon[i] < minExtern){
			minExtern = nGon[i];
			minExternIndex = i;
		}
	}
	stringstream ss;
	for (int i = 0; i < N; i++){
		int cur = ((minExternIndex+i)%N) + N;
		ss << nGon[cur] << nGon[cur-N] << nGon[(cur-N+1)%N];		
	}
	return ss.str();
}

int main ()
{
	int nGon [nodeCount];
	for (int i=1; i <= nodeCount; i++){ nGon[i-1] = i;}
	set <string> solutions;
	do{
		int sum = 0;
		if (verify (nGon, sum)){
			string solution = nGonToStr (nGon);
			if (solutions.find (solution) == solutions.end()){
				cout << sum << "\t" << solution << endl;
				solutions.insert (solution);
			}
		}
	}while (next_permutation (nGon, nGon+nodeCount));
	return 0;
}