
#ifndef TRENDTRACKER_H
#define TRENDTRACKER_H

#include <vector>
#include <string>


using namespace std;

class Trendtracker
{
	// For the mandatory running times below:

	// n is the number of hashtags in the Trendtracker.

	

public:
	// Creates a new Trendtracker tracking no hashtags.
	// 
	// Must run in O(1) time.
	Trendtracker();

	

	// Inserts a hashtag of the popularity pop into the Trendtracker.
	// If pop is a non-negative integer and the hashtag already is in Trendtracker, 
			   //add pop to the popularity of this hashtag in Trendtracker; 
	// if pop is a non-negative integer but the hashtag does not exist, add  
	// otherwise, pop is a negative value and then do nothing but insert a hashtag of popularity zero if it is not in Trendtracker. 
	// 
	// Must run in O(n) time.
	void insert(string ht, int pop);

	// Return the number of hashtags in the Trendtracker.
	//
	// Must run in O(1) time.
	int size();
	// Adds 1 to the total number times a hashtag has been tweeted.
	// If the hashtag does not exist in TrendTracker, does nothing.
	//
	// Must run in O(n) time.
	void tweeted(string ht);

	// Returns the number of times a hashtag has been tweeted.
	// If the hashtag does not exist in Trendtracker, returns -1.
	// 
	// Must run in O(n) time.
	int popularity(string name);

	// Returns the nubmer of hashtags of popularity equal to k. 
	// k must be a non-negative integer and if not, return -1.
	// If the Trendtracker has no hashtags with popularity k, returns 0.
	// 
	// Must run in O(n) time.
	int k_trend(int k);

	// Fills the provided vector with the 3 most-tweeted hashtags, 
	// in order from most-tweeted to least-tweeted.
	// 
	// If there are fewer than 3 hashtags, then the vector is filled
	// with all hashtags (in most-tweeted to least-tweeted order).
	//
	// Must run in O(n) time.
	void top_three_trends(vector<string>& T);

private:
	// A struct representing a hashtag and 
	// the number of times it has been tweeted.
	struct Entry
	{
	public:
		string hashtag;
		int pop =0;
	};


	// Entries containing each hashtag and its popularity.
	vector<Entry> E;
};

#endif 
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
