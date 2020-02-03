
#include <cassert>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include "trendtracker.h"

using namespace std;

inline void _test(const char* expression, const char* file, int line)
{
	cout << "test(" << expression << ") failed in file " << endl; //<< file;
   // cerr << ", line " << line << "." << endl;
   // abort();
}

#define test(EXPRESSION) ((EXPRESSION) ? (void)0 : _test(#EXPRESSION, __FILE__, __LINE__))


int main()
{
	// Setup
	vector<string> R;
	string s, line;

	// Test constructor, size(), popularity(), tweeted()
	Trendtracker T1("small.txt");
	test(T1.size() == 4);
	test(T1.popularity("#algorithms") == 89);
	test(T1.popularity("#cs4all") == 19);
	test(T1.popularity("#datastructures") == -1);
	test(T1.popularity("#programming") == 1965);
	test(T1.popularity("#C++") == 3333);

	T1.tweeted("#programming");
	test(T1.popularity("#algorithms") == 89);
	test(T1.popularity("#cs4all") == 19);
	test(T1.popularity("#datastructures") == -1);
	test(T1.popularity("#programming") == 1966);
	test(T1.popularity("#C++") == 3333);

	T1.tweeted("#programming");
	test(T1.popularity("#algorithms") == 89);
	test(T1.popularity("#cs4all") == 19);
	test(T1.popularity("#datastructures") == -1);
	test(T1.popularity("#programming") == 1967);
	test(T1.popularity("#C++") == 3333);

	T1.tweeted("#programming");
	test(T1.popularity("#algorithms") == 89);
	test(T1.popularity("#cs4all") == 19);
	test(T1.popularity("#datastructures") == -1);
	test(T1.popularity("#programming") == 1968);
	test(T1.popularity("#C++") == 3333);

	T1.tweeted("#cs4all");
	test(T1.popularity("#algorithms") == 89);
	test(T1.popularity("#cs4all") == 20);
	test(T1.popularity("#programming") == 1968);
	test(T1.popularity("#C++") == 3333);

	T1.tweeted("#algorithms");
	test(T1.popularity("#algorithms") == 90);
	test(T1.popularity("#cs4all") == 20);
	test(T1.popularity("#datastructures") == -1);
	test(T1.popularity("#programming") == 1968);
	test(T1.popularity("#C++") == 3333);

	T1.tweeted("#cs4all");
	test(T1.popularity("#algorithms") == 90);
	test(T1.popularity("#cs4all") == 21);
	test(T1.popularity("#datastructures") == -1);
	test(T1.popularity("#programming") == 1968);
	test(T1.popularity("#C++") == 3333);

	T1.tweeted("#datastructures");
	test(T1.popularity("#algorithms") == 90);
	test(T1.popularity("#cs4all") == 21);
	test(T1.popularity("#datastructures") == -1);
	test(T1.popularity("#programming") == 1968);
	test(T1.popularity("#C++") == 3333);

	T1.insert("#Computers", 4048);
	T1.top_k_trends(R, 1);
	test(R[0] == "#Computers");

	//cout<<"Done with T1"<<endl;

	/* Test top_ten_trends().*/

	Trendtracker T3("medium.txt");
	T3.top_k_trends(R, 10);
	test(R.size() == 10);
	test(R[0] == "#linearsearch");

	T3.tweeted("#convexhull");
	T3.tweeted("#convexhull");
	T3.top_k_trends(R, 3);

	test(R[0] == "#convexhull");
	test(R[1] == "#linearsearch");
	test(R[2] == "#triangulation");


	for (int i = 0; i < 100; ++i)
		T3.tweeted("#dog");
	T3.top_k_trends(R, 1);
	test(R[0] == "#dog");

	cout << "Assignment complete." << endl;
}


