
#include <cassert>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include "trendtracker.h"

using namespace std;

inline void _test(const char* expression, const char* file, int line)
{
	cout << "test(" << expression << ") failed" << endl;
}

#define test(EXPRESSION) ((EXPRESSION) ? (void)0 : _test(#EXPRESSION, __FILE__, __LINE__))


int main()
{
	// Setup
	vector<string> R;
	string s, line;
	int numOfktrend;


	// Test size() and insert().
	Trendtracker T1;
	test(T1.size() == 0);
	test(T1.popularity("#algorithms") == 0);
	test(T1.popularity("#cs4all") == 0);
	test(T1.popularity("#programming") == 0);

	T1.insert("#cs4all", 0);
	test(T1.size() == 1);
	test(T1.popularity("#cs4all") == 0);

	T1.insert("#algorithms", 2);
	test(T1.size() == 2);
	test(T1.popularity("#algorithms") == 2);

	T1.insert("#programming", 1);
	test(T1.size() == 3);
	test(T1.popularity("#programming") == 1);

	T1.insert("#algorithms", -1);
	test(T1.size() == 3);
	test(T1.popularity("#algorithms") == 2);

	T1.tweeted("#programming");
	test(T1.popularity("#programming") == 2);

	T1.tweeted("#programming");
	test(T1.popularity("#programming") == 3);

	T1.tweeted("#programming");
	test(T1.popularity("#programming") == 4);

	T1.tweeted("#cs4all");
	test(T1.popularity("#cs4all") == 1);

	T1.tweeted("#algorithms");
	test(T1.popularity("#algorithms") == 3);

	T1.tweeted("#cs4all");
	test(T1.popularity("#cs4all") == 2);

	T1.tweeted("#datastructures");
	test(T1.popularity("#datastructures") == 0);

	T1.insert("#datastructures", 8);
	test(T1.popularity("#datastructures") == 8);

	T1.tweeted("#datastructures");
	test(T1.popularity("#datastructures") == 9);


	T1.insert("#C++", 3);
	T1.tweeted("#C++");
	test(T1.popularity("#C++") == 4);

	T1.insert("#3333", 2);
	T1.tweeted("#3333");
	test(T1.popularity("#3333") == 3);

	//return the numbers of hashtags of popularity equal to 3 and 2 respectively
	numOfktrend = T1.k_trend(3);
	cout << "The number of hashtags with popularity equal to 3 is " << numOfktrend << endl;
	numOfktrend = T1.k_trend(2);
	cout << "The number of hashtags with popularity equal to 2 is " << numOfktrend << endl;

	T1.top_three_trends(R);
	test(R.size() == 0);
	test(R[0] == "#datastructures");

	//////////////////////another instance//////////////////////////////////////////////
	Trendtracker T2;
	T2.insert("#dobermann", 1);
	T2.insert("#shihtzu", 9);
	T2.insert("#pomeranian", 9);
	T2.insert("#pembroke", 6);
	T2.insert("#havanese", 3);

	T2.tweeted("#shihtzu");
	T2.tweeted("#shihtzu");
	T2.tweeted("#pomeranian");
	T2.tweeted("#havanese");
	T2.tweeted("#pembroke");
	T2.tweeted("#pomeranian");

	test(T2.popularity("#shihtzu") == 11);
	test(T2.popularity("#pomeranian") == 11);
	test(T2.popularity("#havanese") == 4);
	test(T2.popularity("#pembroke") == 7);
	test(T2.popularity("#dobermann") == 1);

	///////////////////////////another instance///////////////////////////////////

	Trendtracker T3;

	ifstream f;
	f.open("common.txt");
	assert(f.is_open()); // If this fails, you're missing common.txt
	while (getline(f, line))
	{
		string str_num = line.substr(line.find(',') + 1, line.size() - 1);
		T3.insert(line.substr(0, line.find(',')), std::stoi(str_num, nullptr, 10));
	}
	f.close();

	test(T3.size() == 3597);
	test(T3.popularity("#finishing") == 1463179852);
	test(T3.popularity("#completely") == 571540977);
	test(T3.popularity("#us") == 1466256269);
	test(T3.popularity("#sometimes") == 685583454);
	test(T3.popularity("#quieting") == 1791728192);

	//test(T3.top_trend() == "#finishing");

	T3.top_three_trends(R);
	test(R[0] == "#finishing");
	test(R[1] == "#completely");
	test(R[2] == "#is");
	cout << "Assignment complete." << endl;
}



