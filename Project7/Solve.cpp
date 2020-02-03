#include <iostream>
#include <queue>
#include "solve.h"
#include "vertex.h"
using namespace std;
class Map {

public:

    //Constructs a map
    void createGraph(string maze) {

        Row = maze_Row(maze);
        Col = maze_Col(maze);
        //create Vertex for ' ' spaces
        int rows = 0, cols = 0;

        for (int i = 0; i < maze.size(); i++) {

            if (maze[i] == ' ')  // this will create and push back any thing that black space
            {

                Vertex* newV= new Vertex(rows, cols, i, -1, 1);

                if (i - Row <= 0 || maze[i - 1] == '\n' || maze[i + 1] == '\n' || i + Row >= maze.size()) {

                    if (start == nullptr)
                    {
                        start = newV;
                    }
                    else if (end == nullptr)
                    {
                        end = newV;
                    }

                }
                mazemap.push_back(newV);
            }

            else if (maze[i] >= '0' && maze[i] <= '9')   // this will create the same but for portals
            {

                Vertex* newV= new Vertex(rows, cols, i, maze[i] - 48, 1);

                if (i - Row <= 0 || maze[i - 1] == '\n' || maze[i + 1] == '\n' || i + Row >= maze.size()) {

                    if (start == nullptr)
                    {
                        start = newV;
                    }

                    else if (end == nullptr)
                    {
                        end = newV;
                    }
                }
                mazemap.push_back(newV);
            }
            cols++;
            if (maze[i] == '\n')
            {
                rows++;
                cols = 0;
            }
        }
        addNeighbors();
    }
    //find up down left right neighbors and add each other if there is one

    void addNeighbors() {

        //adding the neighbors

        int r = 0;
        int c = 0;
        Vertex* neigbor;
        for (int i = 0; i < mazemap.size(); i++) {

            r = mazemap[i]->row;
            c = mazemap[i]->col;
///////////////////////up///////////////////////////////////
            // r - 1 > 0 to check its not the top row
            if (r > 0) {

                neigbor = FindNeighbor(r - 1, c);

                if (neigbor != nullptr && !inNeighs(mazemap[i], neigbor)) {

                    mazemap[i]->neighs.push_back(neigbor);
                    neigbor->neighs.push_back(mazemap[i]);
                }
            }
/////////////////////// down//////////////////////////////

            if (r < Col - 1) 
            {
                neigbor = FindNeighbor(r + 1, c);
                if (neigbor != nullptr && !inNeighs(mazemap[i], neigbor)) {

                    mazemap[i]->neighs.push_back(neigbor);
                    neigbor->neighs.push_back(mazemap[i]);
                }
            }
 ////////////////////////////left////////////////////////////////
            if (c > 0) {

                neigbor = FindNeighbor(r, c - 1);
                if (neigbor != nullptr && !inNeighs(mazemap[i], neigbor)) {

                    mazemap[i]->neighs.push_back(neigbor);
                    neigbor->neighs.push_back(mazemap[i]);
                }
            }
/////////////////////////////right//////////////////////////////

            if (c < Row - 1) 
            {
                neigbor = FindNeighbor(r, c + 1);
                if (neigbor != nullptr && !inNeighs(mazemap[i], neigbor)) {

                    mazemap[i]->neighs.push_back(neigbor);
                    neigbor->neighs.push_back(mazemap[i]);
                }
            }
            //Check portal pairs and connects each portal
            if (mazemap[i]->portalNum >= 0) {
                neigbor = FindPortal(i);

                if (neigbor != nullptr && !inNeighs(mazemap[i], neigbor)) {

                    mazemap[i]->neighs.push_back(neigbor);
                    neigbor->neighs.push_back(mazemap[i]);
                }
            }
        }
    }
    //this one the most hard thing i had to incounter because 
    // it cost me a lot of problems so i decided to take a diffrent path 
    // in thinking about this i made everything simpler to understand
    void Djk() {

        MinPriorityQueue<Vertex*> PQ;
        unordered_map<Vertex*, int> D; //stores map of Vertex and distance
        // of course push everything into the PQ
        for (auto n : mazemap)
        {
            D[n] = INT_MAX;
            PQ.push(n, D[n]);
            n->prior = nullptr;
        }
        D[start] = 0;
        PQ.decrease_key(start, D[start]);
        while (PQ.size() > 0)
        {
            Vertex* current = PQ.front();

            PQ.pop();
            // the auto is just aslimper way to go thorugh the neigbors 
            for (auto n : current->neighs) // this will go through all the neigbors 
            {
                if ((current->row - 1 == n->row && current->col == n->col) || (current->row + 1 == n->row && current->col == n->col) || (current->row == n->row && current->col - 1 == n->col) || (current->row == n->row && current->col + 1 == n->col)) {

                    if (D[current] + n->weight < D[n]) {

                        D[n] = D[current] + n->weight;
                        PQ.decrease_key(n, D[n]);
                        n->prior = current;
                    }
                }
                else // this one for the portals and the one ontop is for the regular one
                {
                    if (D[current] + n->portalNum < D[n]) 
                    {
                        D[n] = D[current] + n->portalNum;
                        PQ.decrease_key(n, D[n]);
                        n->prior = current;
                    }
                }

            }

        }

    }
    void BFS() {

        //clear the visited to false
        reset();
        queue<Vertex*> Q;
        start->visited = true;
        Q.push(start);
        while (!Q.empty()) {

            Vertex* front = Q.front();
            Q.pop();
            for (int i = 0; i < front->neighs.size(); i++) 
            {
                if (front->neighs[i]->visited == false) {
                    front->neighs[i]->visited = true;
                    front->neighs[i]->prior = front;
                    Q.push(front->neighs[i]);
                }
            }
        }

    }
    //Modify the maze meaning to replace every thing
    // with o for the smalls path from end to start 
    // by using the 
    string shortestPath(string maze) {

        maze[end->s] = 'o';

        maze[start->s] = 'o';

        for (Vertex* tmp = end->prior; tmp->prior != nullptr; tmp = tmp->prior) {

            maze[tmp->s] = 'o';

        }
        return maze;

    }



private:

    Vertex* start = nullptr;
    Vertex* end = nullptr;

    int Row = 0;
    int Col = 0;

    vector<Vertex*> mazemap;
    //get maze Row
    int maze_Row(string maze) {

        for (int i = 0; i < maze.size(); i++) {
            if (maze[i] == '\n') {
                return i;
            }
        }
        return -1;
    }
    //get maze columns
    int maze_Col(string maze) {

        int h = 0;
        for (int i = 0; i < maze.size(); i++) {

            if (maze[i] == '\n') {
                h++;
            }
        }
        return h;
    }
    //Check that neighbor is not already added

    bool inNeighs(Vertex* current, Vertex* neighbor) {

        for (int i = 0; i < current->neighs.size(); i++) {

            if (current->neighs[i] == neighbor)
            {
                return true;
            }
        }
        return false;
    }
    //See if there is any neighbor

    Vertex* FindNeighbor(int neiRow, int neiCol) {
        for (int i = 0; i < mazemap.size(); i++) {

            if (mazemap[i]->row == neiRow && mazemap[i]->col == neiCol) {
                return mazemap[i];
            }
        }
        return nullptr;
    }
    //See if there is matching portal once it checks it will link them together

    Vertex* FindPortal(int index) {

        for (int i = index + 1; i < mazemap.size(); i++) {

            if (mazemap[index]->portalNum == mazemap[i]->portalNum) {

                return mazemap[i];
            }
        }
        return nullptr;
    }



    //Mark all the verticies as not visited

    void reset() {

        for (int i = 0; i < mazemap.size(); i++) {

            mazemap[i]->visited = false;
        }
    }
};
string solve(string maze) {
    // of cours this want my fist plan but after working on it on a diffrent perspetive 
    // this made it more easy to create everything took me a while 
    Map g;

    g.createGraph(maze); // this will set everything to use dijstracks
    g.Djk(); // after everything is set then we can use the algorith to set everything
    return g.shortestPath(maze); // once everything set we find the short path and set the maze
                                 // to finsh everything
}