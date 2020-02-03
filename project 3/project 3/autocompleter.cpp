



#include "autocompleter.h"
#include<sstream>
using namespace std;



	// For the mandatory running times below:
	// n is the number of strings in the dictionary.
	// Assume that the length of every string is O(1).

	// Creates a dictionary of strings and associated frequencies,
	// using the file as a source. The file is promised to have
	// the following format:
	//
	// string1 freq1
	// string2 freq2
	// ...
	// stringN freqN
	//
	// where string1 < string2 < ... < stringN
	//
	// Must run in O(n) time.
	Autocompleter::Autocompleter(string filename)
	{
		vector<Entry> v;
		ifstream file;
		file.open(filename);
		while (!file.eof())
		{
			string word;
			int num;

			file >> word;
			file >> num;

			Entry baby;
			baby.s = word;
			baby.freq = num;
		

			v.push_back(baby);
		}

		root = construct_recurse(v, 0, (v.size()-1));
	}

	// Returns the number of strings in the dictionary
	// of possible completions.
	//
	// Must run in O(n) time.
	int Autocompleter::size()
	{
		return size_recurse(root);
	}

	// Fills the vector T with the three most-frequent completions of x.
	// If x has less than three completions,
	// then T is filled with all completions of x.
	// The completions appear in T from most- to least-frequent.
	//
	// Must run in O(log(n) + k) time,
	// where k is the number of completions of x in the dictionary.
	void Autocompleter::completions(string x, vector<string>& T)
	{
		while(T.empty() == false)
		{
			T.pop_back();
		}
		vector<Entry>y;
		completions_recurse(x, root, y);
		for (int i = 0; i < y.size(); i++)
		{
			T.push_back(y[i].s);
		}
	}
	// Optional helper methods (you'll probably want them).

	// Returns the root of a BST containing the elements
	// of the portion of a sorted vector E from index l to r.
	//
	// Should run in O(r-l) time.
	Autocompleter::Node* Autocompleter::construct_recurse(vector<Entry>& E, int l, int r)
	{
		if (l > r)
		{
			return nullptr;
		}
		else

		{
			int M = l + (r - l) / 2;
			Node* baby = new Node(E[M]);
			baby->left = construct_recurse(E, l, M - 1);
			baby->right = construct_recurse(E, M + 1, r);
			return baby;
		}
	}

	// Returns the size of the binary tree rooted at root.
	//
	// Should run in O(n) time.
	int Autocompleter::size_recurse(Node* root)
	{
		if (root == nullptr)
		{
			return 0;
		}
		else
		{
			return (size_recurse(root->left) + 1 + size_recurse(root->right));
		}
	}

	// Fills T with the three most-frequent completions of x
	// that are either:
	// -In the BST rooted at root.
	// -Already in T.
	//
	// Should run in O(log(n) + k), where
	// -n is the size of the BST rooted at root.
	// -k is the number of Entrys in the BST rooted at root
	//  whose strings start with x.
	void Autocompleter::completions_recurse(string x,Node * root, vector<Entry>& T)
	{
		int n = x.length();

		if (root == nullptr)
		{
			return;
		}
		else
		{
			if (x > root->e.s.substr(0, n))
			{
				if (root->right != nullptr)
				{
					completions_recurse(x, root->right, T);
				}
			}
			else if (x < root->e.s.substr(0, n))
			{
				if (root->left != nullptr)
				{
					completions_recurse(x, root->left, T);
				}
			}
			else
			{
				if (T.empty() == true)
				{
					T.push_back(root->e);
				}
				else
				{
					for (int i = 0; i < T.size(); i++)
					{
						if (T[i].freq < root->e.freq)
						{
							T.insert(T.begin()+i, root->e);
							if (T.size() == 4)
							{
								T.pop_back();
							}
							break;
						}
						else if (i == T.size() - 1 && T.size() < 3)
						{
							T.push_back(root->e);
							break;
						}
					}
				}
				if (root->left == nullptr && root->right == nullptr)
					return;
				else if (root->right == nullptr)
					completions_recurse(x, root->left, T);
				else if (root->left == nullptr)
					completions_recurse(x, root->right, T);
				else
				{
					completions_recurse(x, root->left, T);
					completions_recurse(x, root->right, T);
				}
			}
		}
	}


  
   
  


