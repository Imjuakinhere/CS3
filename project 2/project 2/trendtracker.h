
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

	Trendtracker(string filename);

	/*
	 Inserts a hashtag of the popularity x into the Trendtracker.

	 If the input hashtag ht exists in Trendtracker,
	 add x to the pop value of this hashtag in vector E;

	 Otherwise, create a new Entry type <ht ,x> and
	 insert it into the right position of E.

	 (You must keep all pais <ht,x> of E in order.)

	 Must run in O(n) time.
	 */

	void insert(string ht, int x);

	/* Return the number of hashtags in the Trendtracker.

	 Must run in O(1) time.
	 */

	int size();

	/* Adds 1 to the total number times a hashtag has been tweeted.
	 If the hashtag does not exist in TrendTracker,
	 does nothing.

	 Must run in O(log n) time.
	 Hint: doing binary search on E.
	 */

	void tweeted(string ht);

	/*
	 Fills the provided vector T with the k most-tweeted hashtags,
	 in order from most-tweeted to least-tweeted.

	 If there are fewer than k hashtags in E, then the vector is filled
	 with all hashtags (in most-tweeted to least-tweeted order) and
	 oupput "Warning: out of range, i.e., k is larger than the number of hashtags in database" on console.

	 Must run in O(kn) time.
	 */

	void top_k_trends(vector<string>& T, int k);

	/*
	 Do binary search on E by the given hashtag ht;
	 Returns the popularity of ht in E;
	 If no such hashtag is found, returns -1.

	 Must run in O(log n) time.
	 */

	int popularity(string ht);


private:
	// A struct representing a hashtag and
	// the number of times it has been tweeted.
	struct Entry
	{
	public:
		string hashtag;
		int pop =0; 
	};


	// Entries contains each hashtag and its popularity in the increasing order of hashtags.
	vector<Entry> E;

};

#endif

