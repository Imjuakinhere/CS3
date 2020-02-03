#include "autocompleter.h"

using namespace std;

Autocompleter:: Autocompleter()
{
	root = new Node();
	count = 0;
}

void Autocompleter::insert(string x, int freq)
{
	//first i created a node to hold the initial position
	Node* lenght = root;
	//created the temp to store the string and the freq
	Entry temp;
	temp.s = x;
	temp.freq = freq;
	// this for loop will go throught every single letter in the word
	for (int i = 0; i <= x.length(); i++)
	{	//this loop will push things into the top 3
		for (int i = 0; i <= lenght->top.size(); i++)
		{	// if the t vector empty then you push it in 
			if (i == lenght->top.size())
			{
				lenght->top.push_back(temp);
				break;
			}
			//if theres more than one thing vector top then you push in only
			// if the freq of the word u pushing in is grater
			else if (temp.freq > lenght->top.at(i).freq)
			{
				lenght->top.insert(lenght->top.begin() + i, temp);
				break;
			}
		}
		// this will delete anything from vector if passes 3
		if (lenght->top.size() > 3)
		{
			lenght->top.pop_back();
		}
		// once we finish the word we exit 
		if (i == x.length())
		{
			break;
		}
		//if the character of the word dosent have a node it creates it 
		if (lenght->children[x[i]] == nullptr)
		{
			lenght->children[x[i]] = new Node();
		}
		// then it move to that node 
		lenght = lenght->children[x[i]];
	}
	// then word finishes then mark true
	lenght->marked = true;
	// increment the number of words;
	++count;
}


int Autocompleter::size()
{
	//return the number of marked words from the insert
	return count;
}


void Autocompleter::completions(string x, vector<string>& T)
{
	//first empty the vector
	while(!(T.empty()))
	{
		T.erase(T.begin());
	}
	//create a temp node to root
	Node* temp = root;
	//move down the tree loop
	for (int i = 0; i < x.length(); i++)
	{
		
		temp = temp->children[x[i]];

		if (temp == nullptr)
		{
			return;
		}
	}
	//then insert the top 3 of the given prefix 
	for (int i = 0; i < temp->top.size(); i++)
	{
		T.push_back(temp->top.at(i).s);
	}
}


int Autocompleter::number_completions(string x)
{
	//create a temp to move down the prefix word
	Node* temp = root;
	for (int i = 0; i < x.length(); i++)
	{
		if (temp->children[x[i]] == nullptr)
		{
			return 0;
		}
		temp = temp->children[x[i]];
	}
	// then call size to give the amount of words withing the given prefix
	return size(temp);
}


int Autocompleter::size(Node* p)
{
	// creat a counter
	int num = 0;
	//if hit nullptr dont do anything
	if (p == nullptr)
	{
		return 0;
	}
	if (p->marked == true)
	{
		++num;
	}
	for (int i = 0; i < 256; ++i)
	{
		num += size(p->children[i]);
	}
	return num;
}