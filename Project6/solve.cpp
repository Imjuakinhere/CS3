#include "solve.h"
#include "vertex.h"
#include <iostream>
using namespace std;

unordered_map<int, pair<Vertex*, int>> portals;
unordered_map<Vertex*, Vertex*> breadcrumbs;

void dimensions(string maze,int & R,int & C);
void FN(Vertex* my, Vertex*** map, int x, int y, int R, int C);
string newmaze(string maze);
void findS(string MZ, Vertex*** map, Vertex*& S, int R, int C);
void findE(string MZ, Vertex*** map, Vertex*& S, Vertex* & E, int R, int C);
string shortestPath(Vertex*** map, string maze, Vertex* S, Vertex* E, int R, int C);

string solve(string maze) 
{
	
	portals.clear();

	Vertex* start = nullptr;
	Vertex* me =nullptr;

	int mazerow=0;
	int mazecol=0;
	///////////find how many Row and columns////////////////
	dimensions(maze, mazerow, mazecol);
	////////// then intialasis everything to null ///////////
	Vertex*** vertexMap;
	vertexMap = new Vertex **[mazerow];
	for (int i = 0; i <= mazerow; ++i) {

		vertexMap[i] = new Vertex * [mazecol];
	}
	for (int i = 0; i <= mazerow; ++i) {
		for (int j = 0; j <= mazecol; ++j) {

			vertexMap[i][j] = nullptr;
		}
	}
	//////////un null the part of the maze///////////////////
	int x = 0;
	int y = 0;

	for (unsigned int i = 0; i < maze.size(); ++i) {

		if (maze.at(i) == '#') {

		}
		else if (maze.at(i) == ' ') {

			Vertex* temp = new Vertex(x, y);
			cout << x << " " << y << endl;
			vertexMap[x][y] = temp;

			FN(temp, vertexMap, x, y, mazerow, mazecol);
		}
		else if (maze.at(i) != '#' && maze.at(i) != ' ' && maze.at(i) != '\n') {

			Vertex* current = new Vertex(x, y);
			vertexMap[x][y] = current;

			char num = maze.at(i);
			string port = "";
			port += num;
			int portalNumber = stoi(port);

			pair<Vertex*, int> tempPortalMapEntry(current, portalNumber);


			if (portals.find(portalNumber) == portals.end()) {

				portals[portalNumber] = tempPortalMapEntry;
				FN(current, vertexMap, x, y, mazerow, mazecol);
			}
			else {

				pair<Vertex*, int> firstPortal = portals[portalNumber];

				Vertex* tempFirst = firstPortal.first;

				current->neighs.push_back(firstPortal);
				firstPortal.first->neighs.push_back(tempPortalMapEntry);

				FN(current, vertexMap, x, y, mazerow, mazecol);
			}
		}

		++y;

		if (maze.at(i) == '\n') {

			++x;
			y = 0;
		}
	}
	////////////////////find startand end/////////////////
	findS(maze, vertexMap, start, mazerow, mazecol);
	findE(maze, vertexMap, start, me, mazerow, mazecol);

	cout << start->row << start->col << endl;
	cout << me->row << me->col << endl;
	string solution = shortestPath(vertexMap, maze, start, me, mazerow, mazecol);
	return solution;
	
	//return "";
}

void dimensions(string maze, int& R, int& C)
{


	for (unsigned int i = 0; i < maze.size(); ++i)
	{
		if (maze[i] == '\n')
		{
			C = i - 1;
			break;
		}
	}
	for (unsigned int i = 0; i < maze.size(); ++i)
	{
		if (maze[i] == '\n')
		{
			R++;
		}
	}
	R -= 1;
}

void FN(Vertex* my, Vertex*** map, int x, int y, int R, int C)
{
	////////////////////////////  up/////////////////////////////
	if (x - 1 >= 0) {

		if (map[x - 1][y] != nullptr) {

			pair<Vertex*, int> Entry(map[x][y], 1);
			pair<Vertex*, int> up(map[x - 1][y], 1);

			if (my->ney.find(map[x - 1][y]) == my->ney.end()) {

				my->neighs.push_back(up);
				my->ney.insert(map[x - 1][y]);
			}

			if (map[x - 1][y]->ney.find(my) == map[x - 1][y]->ney.end()) {

				map[x - 1][y]->neighs.push_back(Entry);
				map[x - 1][y]->ney.insert(my);
			}
		}
	}
	////////////////////////// dow////////////////////////////
	if (x + 1 <= R) {

		if (map[x + 1][y] != nullptr) {

			pair<Vertex*, int> Entry(map[x][y], 1);
			pair<Vertex*, int> down(map[x + 1][y], 1);

			if (my->ney.find(map[x + 1][y]) == my->ney.end()) {

				my->neighs.push_back(down);
				my->ney.insert(map[x + 1][y]);
			}

			if (map[x + 1][y]->ney.find(my) == map[x + 1][y]->ney.end()) {

				map[x + 1][y]->neighs.push_back(Entry);
				map[x + 1][y]->ney.insert(my);
			}
		}
	}
	///////////////////////////// left ////////////////////////////////
	if (y - 1 >= 0) {
		if (map[x][y - 1] != nullptr) {

			pair<Vertex*, int> Entry(map[x][y], 1);
			pair<Vertex*, int> left(map[x][y - 1], 1);

			if (my->ney.find(map[x][y - 1]) == my->ney.end()) {

				my->neighs.push_back(left);
				my->ney.insert(map[x][y - 1]);
			}

			if (map[x][y - 1]->ney.find(my) == map[x][y - 1]->ney.end()) {

				map[x][y - 1]->neighs.push_back(Entry);
				map[x][y - 1]->ney.insert(my);
			}
		}
	}

	//////////////////////// right///////////////////////////
	if (y + 1 <= C)
	{

		if (map[x][y + 1] != nullptr) {

			pair<Vertex*, int> Entry(map[x][y], 1);
			pair<Vertex*, int> right(map[x][y + 1], 1);

			if (my->ney.find(map[x][y + 1]) == my->ney.end()) {

				my->neighs.push_back(right);
				my->ney.insert(map[x][y + 1]);
			}

			if (map[x][y + 1]->ney.find(my) == map[x][y + 1]->ney.end()) {

				map[x][y + 1]->neighs.push_back(Entry);
				map[x][y + 1]->ney.insert(my);
			}
		}
	}
}

string newmaze(string maze)
{

	for (unsigned int i = 0; i < maze.length(); ++i) {

		if (maze.at(i) == '\n') {
			maze.erase(i, 1);
		}
	}

	return maze;
}

void findS(string MZ, Vertex*** map, Vertex*& S, int R, int C)
{
	////////////////////////////start////////////////////////////// 
	for (int i = 1; i <= C - 1; i++)
	{
		if (map[0][i] != nullptr && S == nullptr)
		{
			S = map[0][i];
			break;
		}

	}
	if (S == nullptr)
	{
		for (int i = 1; i <= C - 1; i++)
		{
			if (map[R][i] != nullptr && S == nullptr)
			{
				S = map[R][i];
				break;
			}
		}
	}
	else if (S == nullptr)
	{
	
		for (int i = 1; i <= R - 1; i++)
		{
			if (map[i][0] != nullptr && S == nullptr)
			{
				S = map[i][0];
				break;
			}
			if (map[i][C] != nullptr && S == nullptr)
			{
				S = map[i][C];
				break;
			}
		}
	}
	else if (S == nullptr)
	{

		for (int i = 1; i <= R - 1; i++)
		{
			if (map[i][C] != nullptr && S == nullptr)
			{
				S = map[i][C];
				break;
			}
		}
	}

}




void findE(string MZ, Vertex*** map, Vertex*& S, Vertex* & E, int R, int C)
{
	//////////////////////////end/////////////////////////////////
	for (int i = 1; i <= C - 1; i++)
	{
		if (map[0][i] != nullptr && S != map[0][i])
		{

			E = map[0][i];
			break;
		}
	}
	if (E == nullptr)
	{
		for (int i = 1; i <= C - 1; i++)
		{

			if (map[R][i] != nullptr && S != map[R][i])
			{
				E = map[R][i];
				break;
			}
		}
		
	}
	else if (E == nullptr)
	{

		for (int i = 1; i <= R - 1; i++)
		{
			if (map[i][0] != nullptr && S != map[i][0])
			{
				E = map[i][0];
				break;
			}
		}
	}
	else if (E == nullptr)
	{

		for (int i = 1; i <= R - 1; i++)
		{
		
			if (map[i][C] != nullptr && S != map[i][C])
			{
				E = map[i][C];
				break;
			}
		}
	}
}

string shortestPath(Vertex*** map, string maze, Vertex* S, Vertex* E, int R, int C)
{
	MinPriorityQueue<Vertex*> Q;
	unordered_set<Vertex*>vis;

	for (unsigned int i = 0; i <= R; ++i) {
		for (unsigned int j = 0; j <= C; ++j) {

			if (map[i][j] != nullptr) {

				if (map[i][j] == S) {

					Q.push(S, 0);
				}
				else {

					Q.push(map[i][j], 5000);
				}
			}
		}
	}
	

	while (Q.size() != 0)
	{
		pair<Vertex*, int> item = Q.front();
		vis.insert(item.first);

		Q.pop();

		for (unsigned int i = 0; i < item.first->neighs.size(); i++)
		{
			Vertex* location = item.first->neighs[i].first;
			int num = item.first->neighs[i].second;
			bool createbread = false;
			cout << item.first->row << item.first->col << item.second<<  " ";
			cout << location->row << location->col << num << endl;
			if (vis.find(location) == vis.end())
			{
				createbread = Q.decrease_key(location, item.second + num);
			}

			if (createbread)
			{
				breadcrumbs[location = item.first];
			}
		}
	}



	return maze;
}


