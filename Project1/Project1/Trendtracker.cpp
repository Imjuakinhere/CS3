
#include "trendtracker.h"


using namespace std;




	// Creates a new Trendtracker tracking no hashtags.
	// 
	// Must run in O(1) time.
	Trendtracker::Trendtracker()
	{

	}


	// Inserts a hashtag of the popularity pop into the Trendtracker.
	// If pop is a non-negative integer and the hashtag already is in Trendtracker, 
			   //add pop to the popularity of this hashtag in Trendtracker; 
	// if pop is a non-negative integer but the hashtag does not exist, add  
	// otherwise, pop is a negative value and then do nothing but insert a hashtag of popularity zero if it is not in Trendtracker. 
	// 
	// Must run in O(n) time.
	void Trendtracker::insert(string ht, int pop)
	{
		if (E.size() == 0)
		{
			Entry baby;
			baby.hashtag = ht;
			baby.pop = pop;
			E.push_back(baby);
		}

		else
		{

			for (unsigned int i = 0; i < E.size(); i++)
			{

				if (ht == E[i].hashtag)
				{
					return;
				}
			}
			Entry baby;
			baby.hashtag = ht;
			if (pop > 0)
				baby.pop = pop;
			else
				baby.pop = 0;
			E.push_back(baby);
		}
		
	}

	// Return the number of hashtags in the Trendtracker.
	//
	// Must run in O(1) time.
	int Trendtracker::size()
	{
		return E.size();
	}

	// Adds 1 to the total number times a hashtag has been tweeted.
	// If the hashtag does not exist in TrendTracker, does nothing.
	//
	// Must run in O(n) time.
	void  Trendtracker::tweeted(string ht)
	{
		for (unsigned int i = 0; i < E.size(); i++)
		{
			if (ht == E[i].hashtag)
			{
				E[i].pop++;
			}
		}
	}

	// Returns the number of times a hashtag has been tweeted.
	// If the hashtag does not exist in Trendtracker, returns -1.
	// 
	// Must run in O(n) time.
	int  Trendtracker::popularity(string name)
	{
		for (unsigned int i = 0; i < E.size(); i++)
		{
			if (name == E[i].hashtag)
			{
				return E[i].pop;
			}
		}
		return -1;
	}

	// Returns the nubmer of hashtags of popularity equal to k. 
	// k must be a non-negative integer and if not, return -1.
	// If the Trendtracker has no hashtags with popularity k, returns 0.
	// 
	// Must run in O(n) time.
	int  Trendtracker::k_trend(int k)
	{
		int count = 0;
		if (k < 0)
		{
			return -1;
		}
		for (unsigned int i = 0; i < E.size(); ++i)
		{
			if (k == E[i].pop)
			{
				count++;
			}
		}
		if (count == 0)
		{
			return 0;
		}
		return count;


	}

	// Fills the provided vector with the 3 most-tweeted hashtags, 
	// in order from most-tweeted to least-tweeted.
	// 
	// If there are fewer than 3 hashtags, then the vector is filled
	// with all hashtags (in most-tweeted to least-tweeted order).
	//
	// Must run in O(n) time.
	void Trendtracker::top_three_trends(vector<string>& T)
	{
		// so first we must check if the vector is empty 
		// if is not then we clear it and we start from the begining 
		while (!(T.empty()))
		{
			T.erase(T.begin());
		}
		vector<Entry> copy;
		copy = E;
		if (E.size() < 3)
		{
			if (E.size() == 2)
			{
				if (E[0].pop > E[1].pop)
				{
					T.push_back(E[0].hashtag);
					T.push_back(E[1].hashtag);
				}
				else
				{
					T.push_back(E[1].hashtag);
					T.push_back(E[0].hashtag);
				}
			}
			else
			{
				T.push_back(E[0].hashtag);
			}
		}
		else
		{
			// top 1 fins the frist one

			Entry one;
			one.hashtag = copy[0].hashtag;
			one.pop = copy[0].pop;

			int c = 0;
			for (unsigned int i = 0; i < copy.size(); i++)
			{
				if (one.pop < copy[i].pop)
				{
					one.pop = copy[i].pop;
					one.hashtag = copy[i].hashtag;
					c = i;
				}
			}

			T.push_back(one.hashtag);
			copy.erase(copy.begin() + c);
			// top 2 fins the second one 
			Entry two;
			two.hashtag = copy[0].hashtag;
			two.pop = copy[0].pop;

			int c2 = 0;
			for (unsigned int i = 0; i < copy.size(); i++)
			{
				if (two.pop < copy[i].pop)
				{
					two.pop = copy[i].pop;
					two.hashtag = copy[i].hashtag;
					c2 = i;
				}
			}

			T.push_back(two.hashtag);
			copy.erase(copy.begin() + c2);
			// top 3 find the last one 

			Entry three;
			three.hashtag = copy[0].hashtag;
			three.pop = copy[0].pop;

			int c3 = 0;
			for (unsigned int i = 0; i < copy.size(); i++)
			{
				if (three.pop < copy[i].pop)
				{
					three.pop = copy[i].pop;
					three.hashtag = copy[i].hashtag;
					c3 = i;
				}
			}

			T.push_back(three.hashtag);
			copy.erase(copy.begin() + c3);


		}
		//smaller version
		/*if (!T.empty())
			while (T.empty())
				T.erase(T.begin());
		vector<Entry> e = E;

		if (e.size() < 3) {
			if (e.size() == 2) {
				if (e[0].pop > e[1].pop) {
					T.push_back(e[0].hashtag);
					T.push_back(e[1].hashtag);
				}
				else {
					T.push_back(e[1].hashtag);
					T.push_back(e[0].hashtag);
				}
			}


			else if (e.size() == 1)
				T.push_back(e[0].hashtag);
			else {}

		}
		else {
			for (int x = 0; x < 3; x++) {
				Entry top = e[0];
				int index = 0;
				for (unsigned i = 0; i < e.size(); i++) {
					if (top.pop < e[i].pop) {
						top = e[i];
						index = i;
					}
				}
				T.push_back(top.hashtag);
				e.erase(e.begin() + index);
			}

		}*/

	}


