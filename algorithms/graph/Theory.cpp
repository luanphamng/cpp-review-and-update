
#include <iostream>
#include <vector>
using namespace std;

#define VISITED true
#define UNVISITED false

typedef pair<int, int> ii; // In this chapter, we will frequently use these
typedef vector<ii> vii;    // three data type shortcuts. They may look cryptic
typedef vector<int> vi;    // but they are useful in competitive programming

/*
    Depth First Search—abbreviated as DFS—is a simple algorithm for traversing a graph.
    Starting from a distinguished source vertex, DFS will traverse the graph ‘depth-first’.
    Every time DFS hits a branching point (a vertexwith more than one neighbors), DFS will choose
    one of the unvisited neighbor(s) and visit this neighbor vertex.
    DFS repeats this process and goes deeper until it reaches a vertex where it cannot go any deeper.
    When this happens, DFS will ‘backtrack’ and explore another unvisited neighbor(s), if any

    DFS runs in O(V + E), but the time complexity of backtracking is exponential.

    V vertices and E edges
*/
// The DFS code shown here is very similar to the recursive backtracking code shown earlie
// void backtrack(state)
// {
//     if (hit end state or invalid state) // we need terminating or
//         return;                         // pruning condition to avoid cycling and to speed up search
//     for each neighbor of this state // try all permutation
//         backtrack(neighbor);
// }

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

void dfs(int u)
{                     // DFS for normal usage: as graph traversal algorithm
    dfs_num[u] = VISITED; // important: we mark this vertex as visited
    for (int j = 0; j < (int)AdjList[u].size(); j++)
    {                                      // default DS: AdjList
        ii v = AdjList[u][j];              // v is a (neighbor, weight) pair
        if (dfs_num[v.first] == UNVISITED) // important check to avoid cycle
            dfs(v.first);                  // recursively visits unvisited neighbors of vertex u
    }
} // for simple graph traversal, we ignore the weight stored at v.second

/*
    \ return Single-Source Shortest Paths
    Breadth First Search—abbreviated as BFS—is another graph traversal algorithm. Starting
    from a distinguished source vertex, BFS will traverse the graph ‘breadth-first’. That is, BFS
    will visit vertices that are direct neighbors of the source vertex (first layer), neighbors of
    direct neighbors (second layer), and so on, layer by layer.
    BFS starts with the insertion of the source vertex s into a queue, then processes the queue
    as follows: Take out the front most vertex u from the queue, enqueue all unvisited neighbors
    of u (usually, the neighbors are ordered based on their vertex numbers), and mark them as
    visited. With the help of the queue, BFS will visit vertex s and all vertices in the connected
    component that contains s layer by layer. BFS algorithm also runs in O(V + E) and O(V 2)
*/

vii AdjList;

void bfs(int s) // s = srouce id
{
    vi d(V, INT_MAX);
    d[s] = 0;

    queue<int> q; q.push(s);

    while(!q.empty()) {
        int u = q.front(); q.pop();

        // Check all neighbor of current node
        for (int i = 0; i < AdjList[u].size(); i++) {
            ii v = AdjList[u][i];

            if (d[v.first] == INT_MAX) {
                d[v.first] = d[u] + 1;  // Increase distance by 1, this also marked current nei node as visited
                q.push(v.first);
            }
        }
    }
}

void dijktra() {
    vi dist(V, INT_MAX)
}