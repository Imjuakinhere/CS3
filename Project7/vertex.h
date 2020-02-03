
// A helper class implementing a vertex in
// an adjacency-list-based graph.
//the vertex is only used to help me develop the map 
//while also take care of the weights and other aspects that are needed
class Vertex
{
public:

    Vertex(int r, int c, int index, int pn, int w)
    {
        row = r;
        col = c;
        visited = false;
        prior = nullptr;
        s = index;
        portalNum = pn; // -1 means empty space, others 0-9 is portal number
        weight = w;
    }
    // Corresponding row and column location in maze

    int row;
    int col;
    int s;
    int weight;
    int portalNum;
    bool visited;
    Vertex* prior;
    // List of neighboring vertices
    vector<Vertex*> neighs;
};
