/*
    Depth First Search—abbreviated as DFS—is a simple algorithm for traversing a graph.
    Starting from a distinguished source vertex, DFS will traverse the graph ‘depth-first’.
    Every time DFS hits a branching point (a vertexwith more than one neighbors), DFS will choose
    one of the unvisited neighbor(s) and visit this neighbor vertex.
    DFS repeats this process and goes deeper until it reaches a vertex where it cannot go any deeper.
    When this happens, DFS will ‘backtrack’ and explore another unvisited neighbor(s), if any

    V vertices and E edges
*/

#include <iostream>
#include <vector>
using namespace std;

#define VISITED     true
#define UNVISITED   false

typedef pair<int, int> ii; // In this chapter, we will frequently use these
typedef vector<ii> vii;    // three data type shortcuts. They may look cryptic
typedef vector<int> vi;    // but they are useful in competitive programming

vi dfs_num;                // global variable, initially all values are set to UNVISITED
vector<vii> AdjList;

// The DFS code shown here is very similar to the recursive backtracking code shown earlie
void dfs(int u)
{                         // DFS for normal usage: as graph traversal algorithm
    dfs_num[u] = VISITED; // important: we mark this vertex as visited
    for (int j = 0; j < (int)AdjList[u].size(); j++)
    {                                      // default DS: AdjList
        ii v = AdjList[u][j];              // v is a (neighbor, weight) pair
        if (dfs_num[v.first] == UNVISITED) // important check to avoid cycle
            dfs(v.first);                  // recursively visits unvisited neighbors of vertex u
    }
} // for simple graph traversal, we ignore the weight stored at v.second