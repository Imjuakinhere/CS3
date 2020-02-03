#ifndef MINPRIORITYQUEUE_H
#define MINPRIORITYQUEUE_H

// NOTE: You may not include any other libraries!
#include <unordered_map>
#include <vector>
#include <utility> // Has pair and swap

using namespace std;

template <typename T>
class MinPriorityQueue
{
	// For the mandatory running times below:
	//
	// n is the number of elements in the MinPriorityQueue.
	//
	// Assume that the operations of unordered_map are O(1) time 
	// (they are average case, but not worst-case).

public:
	// Creates an empty MinPriorityQueue
	MinPriorityQueue()
	{
	}
	// Returns the number of elements in the MinPriorityQueue.
	//
	// Must run in O(1) time.
	int size()
	{
		return H.size();		// just returning the size of the vector
	}

	// Pushes a new value x with priority p
	// into the MinPriorityQueue.
	//
	// Must run in O(log(n)) time.		 
	void push(T x, int p)
	{
		// first create a temp for the info that were receiving 
		pair <T, int> temp;
		temp.first = x;
		temp.second = p;
		H.push_back(temp);
		// since im going to be working with the current to move the object
		int cur = H.size() - 1;
		// this is for the unorder map
		I[x] = cur;
		// this while loop is to move up the loop till everything is meet
		bubbleup(cur, p);
	}

	// Returns the value at the front of the MinPriorityQueue.
	// Undefined behavior if the MinPriorityQueue is empty.
	// 
	// Must run in O(1) time.
	pair<T, int> front()
	{	// to return the first object in the vector
		pair<T, int> Temp;
		Temp.first = H[0].first;
		Temp.second = H[0].second;
		return Temp;
	}

	// Removes the value at the front of the MinPriorityQueue.
	// Undefined behavior if the MinPriorityQueue is empty.
	//
	// Must run in O(log(n)) time. 
	void pop()
	{
		// if empty then do nothing 
		if (H.empty())
		{
			return;
		}
		// then you have to remove the first thing in unoreder map 
		I.erase(H[0].first);
		H[0] = H[H.size() - 1];
		H.pop_back();

		int cur = 0;

		bubbledown(cur);
	}
	// If x is in the MinPriorityQueue 
	// with current priority at least new_p,  
	// then changes the priority of x to new_p.
	// Undefined behavior otherwise.
	//
	// Must run in O(log(n)) time. 
	bool decrease_key(T x, int new_p)
	{
		int cur = I[x];
		if (H[cur].second < new_p)
		{
			return false;
		}

		H[cur].second = new_p;

		bubbleup(cur, new_p);
		return true;
	}

private:
	// You don't need any other instance variables,
	// but you can add some if you want to.
	vector< pair<T, int> > H; // The heap.
	unordered_map<T, int> I;  // Maps values to their indices in H.


	void swapat(int x, int y)
	{
		pair<T, int> ok = H[x];
		// vector swap
		H[x] = H[y];
		H[y] = ok;
		// unorder map swap 
		I[H[x].first] = x;
		I[H[y].first] = y;
	}

	int parent(int x)
	{
		return (x - 1) / 2;
	}
	int leftchild(int x)
	{
		return x * 2 + 1;
	}
	int rightchild(int x)
	{
		return x * 2 + 2;
	}

	void bubbleup(int c, int p)
	{
		while (c != 0)
		{
			if (H[parent(c)].second > p)
			{
				swapat(c, parent(c));
				c = parent(c);
			}
			else
			{
				break;
			}
		}
	}
	void bubbledown(int c)
	{
		// this while loop is also the algorithem to move down the tree or in other wprds buubledown
		while (c < H.size())
		{
			int small = -1;
			if (leftchild(c) >= H.size() && rightchild(c) >= H.size())
			{
				break;
			}
			else
			{
				if (H[leftchild(c)].second < H[rightchild(c)].second)
				{
					small = leftchild(c);
				}
				else
				{
					small = rightchild(c);
				}
			}
			if (H[small].second < H[c].second)
			{
				swapat(c, small);
				c = small;
			}
			else
			{
				break;
			}
		}
	}
};


/* used to be part of pop

else if (leftchild(cur) >= H.size() && !(rightchild(cur) >= H.size()))
	{
		small = rightchild(cur);
	}
	else if (!(leftchild(cur) >= H.size()) && rightchild(cur) >= H.size())
	{
		small = leftchild(cur);
	}*/
#endif