
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

/*
    If the given graph is weighted, BFS does not work. This is because there can be ‘longer’
    path(s) (in terms of number of vertices and edges involved in the path) but has smaller total
    weight than the ‘shorter’ path found by BFS. For example, in Figure 4.17, the shortest path
    from source vertex 2 to vertex 3 is not via direct edge 2 → 3 with weight 7 that is normally
    found by BFS, but a ‘detour’ path: 2 → 1 → 3 with smaller total weight 2 + 3 = 5.
    To solve the SSSP problem on weighted graph, we use a greedy Edsger Wybe Dijkstra’s
    algorithm. There are several ways to implement this classic algorithm. In fact, Dijkstra’s
    original paper that describes this algorithm [10] does not describe a specific implementation.
    Many other Computer Scientists proposed implementation variants based on Dijkstra’s original work. Here we adopt one of the easiest implementation variant that uses built-in C++
    STL priority queue (or Java PriorityQueue). This is to keep the length of code minimal—a necessary feature in competitive programming.
    This Dijkstra’s variant maintains a priority queue called pq that stores pairs of vertex
    information. The first and the second item of the pair is the distance of the vertex from the
    source and the vertex number, respectively. This pq is sorted based on increasing distance
    from the source, and if tie, by vertex number. This is different from another Dijkstra’s
    implementation that uses binary heap feature that is not supported in built-in library8.
    This pq only contains one item initially: The base case (0, s) which is true for the source
    vertex. Then, this Dijkstra’s implementation variant repeats the following process until pq
    is empty: It greedily takes out vertex information pair (d, u) from the front of pq. If the
    distance to u from source recorded in d greater than dist[u], it ignores u; otherwise, it
    process u. The reason for this special check is shown below.
    When this algorithm process u, it tries to relax all neighbors v of u. Every time it
    relaxes an edge u → v, it will enqueue a pair (newer/shorter distance to v from source, v)
    into pq and leave the inferior pair (older/longer distance to v from source, v) inside pq. This
    is called ‘Lazy Deletion’ and it causes more than one copy of the same vertex in pq with
    different distances from source. That is why we have the check earlier to process only the
    first dequeued vertex information pair which has the correct/shorter distance (other copies
    will have the outdated/longer distance). The code is shown below and it looks very similar
    to BFS and Prim’s code shown in Section 4.2.2 and 4.3.3, respectively.
*/

void dijktra_priority_queue(uint id) {
    vi dist(V, INT_MAX);
    dist[id] = 0;

    priority_queue<ii, vector<ii>, greater<ii>> pq;
    pq.push(ii(0, s));

    while (!pq.empty())
    {
        ii front = pq.top();
        pq.pop();
        uint d = front.first;
        uint neiID = front.second;

        if (d > dist[neiID])  // IMPORTANT: if dist[neiID] already small then ignore checking process]
            continue;

        for (uint i = 0; i < adj[neiID].size(); i++) {
            ii v = adj[id][i];

            // Main algorithm
            if (dist[neiID] > dist[d] + v.second) {
                dist[neiID] = dist[d] + v.second;
                pq.push(ii(dist[neiId], neiId));
            }
        }
    }
    
}