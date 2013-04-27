/*
	By counting carefully it can be seen that a rectangular grid measuring 3 by 2 
	contains eighteen rectangles:

	Although there exists no rectangular grid that contains exactly two million 
	rectangles, find the area of the grid with the nearest solution.
*/
#include <cmath>
#include <iostream>
using namespace std;

int countRectangles (int w, int h)
{
	int l = 0;
	if (w%2==0){ l = (w+1)*(w/2);}
	else{ l = (w+1)*(w/2)+(w/2+1);}
	int m = 0;
	if (h%2==0){ m = (h+1)*(h/2);}
	else{ m = (h+1)*(h/2)+(h/2+1);}
	return l*m;
}

int main ()
{
	int minDiff = 999999;
	for (int i=1; i<2013; ++i){
		for (int j=1; j<2013; ++j){
			int r = countRectangles(i, j);
			int diff = abs(2000000-r);
			if (diff < minDiff){ 
				minDiff = diff;
				cout << i << " X " << j << " = " << i*j << " contains " << r << " rectangles\n";
			}
		}
	}
	return 0;
}