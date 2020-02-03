#include "trendtracker.h"
#include <fstream>
#include <vector>
#include <sstream> 
#include <iostream>

using namespace std;
/* Creates a Trendtracker containing hashtags
	 found in the provided file.
	 The file is promised to have the following format:

	 hashtag, popularity
	 hashtag, popularity
	 ...
	 hashtag, popularity


	 Fill the vector E with pairs of hashtags and popularities:
	 <ht1, pop1>, <ht2, pop2>, <ht3, pop3>, <ht4, pop4>, ..., <htN, popN>
	 such that all pairs are in the increasing order of hashtags,
	 i.e., ht1 < ht2 < ... < htN

	 Must run in O(n^2) time.
	 */

Trendtracker::Trendtracker(string filename)
{
	ifstream cake;
	cake.open(filename);

	while(!cake.eof())
	{
		string idk;
		string sub1 , sub2;
		int split;
		

		getline(cake, idk);
		split = idk.find(",");
		sub1 = idk.substr(0, split);
		sub2 = idk.substr(split + 1);

		stringstream x(sub2);
		int why = 0;
		x >> why;
		
		Entry baby;
		baby.hashtag = sub1 ;
		baby.pop = why;

		E.push_back(baby);
	}

	for (unsigned int i = 0; i < E.size(); i++)
	{
		
		for (unsigned int j = i; j < E.size(); j++)
		{
			if (E[i].hashtag > E[j].hashtag)
			{
				Entry temp;
				temp.hashtag = E[i].hashtag;
				temp.pop = E[i].pop;
				E[i].hashtag = E[j].hashtag;
				E[i].pop = E[j].pop;
				E[j].hashtag = temp.hashtag;
				E[j].pop = temp.pop;
			}	
		}
	}
}

/*
 Inserts a hashtag of the popularity x into the Trendtracker.

 If the input hashtag ht exists in Trendtracker,
 add x to the pop value of this hashtag in vector E;

 Otherwise, create a new Entry type <ht ,x> and
 insert it into the right position of E.

 (You must keep all pais <ht,x> of E in order.)

 Must run in O(n) time.
 */

void Trendtracker::insert(string ht, int x)
{
	bool flag = false;

	for (unsigned int i = 0; i < E.size(); i++)
	{
		if (E[i].hashtag == ht)
		{
			E[i].pop = E[i].pop + x;
			flag = true;
		}
	}
	if (flag == false)
	{
		for (unsigned int i = 0; i < E.size(); i++)
		{
			if (E[i].hashtag > ht)
			{
				
					Entry baby;
					baby.hashtag = ht;
					baby.pop = x;

					E.insert(E.begin() + i, baby);
					break;
			}	
		}
	}

}

/* Return the number of hashtags in the Trendtracker.

 Must run in O(1) time.
 */

int Trendtracker::size()
{
	return E.size();
}

/* Adds 1 to the total number times a hashtag has been tweeted.
 If the hashtag does not exist in TrendTracker,
 does nothing.

 Must run in O(log n) time.
 Hint: doing binary search on E.
 */

void Trendtracker::tweeted(string ht)
{
	int l = 0;
	int r = E.size() - 1;
	while (l <= r)
	{
		int m = l + (r - l) / 2;
		if (ht == E[m].hashtag)
		{
			E[m].pop++;
			break;
		}
		if (ht > E[m].hashtag)
		{
			l = m + 1;
		}
		if (ht < E[m].hashtag)
		{
			r = m -1;
		}
	}
}

/*
 Fills the provided vector T with the k most-tweeted hashtags,
 in order from most-tweeted to least-tweeted.

 If there are fewer than k hashtags in E, then the vector is filled
 with all hashtags (in most-tweeted to least-tweeted order) and
 oupput "Warning: out of range, i.e., k is larger than the number of hashtags in database" on console.

 Must run in O(kn) time.
 */

void Trendtracker::top_k_trends(vector<string>& T, int k)
{
	//make sure that the vector is empty 
	while (!(T.empty)())
	{
		T.erase(T.begin());
	}
	// create a copy of the E vector
	vector<Entry> hold;
	hold = E;

	if (E.size() < k)
	{
		k = E.size();

		for (unsigned int i = 0; i < k; i++)
		{
			Entry baby;
			baby.hashtag = E[0].hashtag;
			baby.pop = E[0].pop;

			int c = 0;
			for (unsigned int i = 0; i < hold.size(); i++)
			{
				if (baby.pop < hold[i].pop)
				{
					baby.pop = hold[i].pop;
					baby.hashtag = hold[i].hashtag;
					c = i;
				}
			}

			T.push_back(baby.hashtag);
			hold.erase(hold.begin() + c);
		}

	}
	else
	{

		for (unsigned int i = 0; i < k; i++)
		{
			Entry baby;
			baby.hashtag = E[0].hashtag;
			baby.pop = E[0].pop;

			int c = 0;
			for (unsigned int i = 0; i < hold.size(); i++)
			{
				if (baby.pop < hold[i].pop)
				{
					baby.pop = hold[i].pop;
					baby.hashtag = hold[i].hashtag;
					c = i;
				}
			}

			T.push_back(baby.hashtag);
			hold.erase(hold.begin() + c);

		}


	}
}

/*
 Do binary search on E by the given hashtag ht;
 Returns the popularity of ht in E;
 If no such hashtag is found, returns -1.

 Must run in O(log n) time.
 */

int Trendtracker::popularity(string ht)
{

	int l = 0;
	int r = E.size() -1;
	while (l <= r)
	{
		int m = l + (r - l) / 2;
		
		if (E[m].hashtag == ht)
		{
			return E[m].pop;
		}
		if (E[m].hashtag < ht)
		{
			l = m + 1;
		}
		if (E[m].hashtag > ht)
		{
			r = m -1 ;
		}
	}
	return -1;
}