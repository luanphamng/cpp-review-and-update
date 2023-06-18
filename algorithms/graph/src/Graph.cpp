#include "Graph.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <limits.h>
#include <list>
#include <queue>

using namespace std;

#define VISITED     true
#define UNVISITED   false
#define LOG

// #define print //

Graph::Graph(const char* const & edgelist_csv_fn) {
    // init every variable
    initVar();

    // Read from file to format
    string _line;
    ifstream _csvFile;
    _csvFile.open(edgelist_csv_fn);

    while (getline(_csvFile, _line)) {
        // get from xls
        std::vector<std::string> v = split(_line.c_str(), ",");
        string _nodeLabel = v[0];
        string _neighborLabel = v[1];
        double _weight = atof(v[2].c_str());

        uint nodeId = 0;
        uint neighborId = 0;

        // Check if this is the new node
        if (m_label2Id.find(_nodeLabel) == m_label2Id.end()) {
            uint id = m_label2Id.size(); // increase index
#ifdef LOG
            cout << __FUNCTION__ << " - new node need to added: " << _nodeLabel << ", id: " << id << endl;
#endif
            m_label2Id.insert({_nodeLabel, id});
            m_id2label.insert({id, _nodeLabel});
            // Push empty edges to adj
            nodeId = id;
            vector<idbl> edges;
            m_adj.push_back(edges);
        } else {
            nodeId = m_label2Id[_nodeLabel];
        }

        if (m_label2Id.find(_neighborLabel) == m_label2Id.end()) {
            uint id = m_label2Id.size(); // increase index
#ifdef LOG
            cout << __FUNCTION__ << " - new neighbor need to added: " << _neighborLabel << ", id: " << id << endl;
#endif
            m_label2Id.insert({_neighborLabel, id});
            m_id2label.insert({id, _neighborLabel});
            // Push empty edges to adj
            vector<idbl> edges;
            neighborId = id;
            m_adj.push_back(edges);
        } else {
            neighborId = m_label2Id[_neighborLabel];
        }

        cout << __FUNCTION__ << "Size of adj: " << m_adj.size() << ", nodeId: " << nodeId << ", neighId: " << neighborId << endl;
        m_adj[nodeId].push_back(make_pair(neighborId, _weight));
        m_adj[neighborId].push_back(make_pair(nodeId, _weight));

        m_iNumEdges++;
    }

    m_iNumNodes = m_id2label.size();
#ifdef LOG
    cout << "Adj input: " << endl;
    for (uint i = 0; i < m_id2label.size(); i++) {
        cout << m_id2label[i] << " -> ";
        for (auto u : m_adj[i]) {
            cout << m_id2label[u.first];
        }
        cout << endl;
    }
#endif
}

Graph::~Graph() {
}

unsigned int Graph::num_nodes() {
    // TODO
    return m_id2label.size();
}

vector<string> Graph::nodes() {
    vector<string> vt;
    for (uint i = 0; i < m_id2label.size(); i++) {
        vt.push_back(m_id2label[i]);
    }

    return vt;
}

unsigned int Graph::num_edges() {
    return m_iNumEdges;
}

unsigned int Graph::num_neighbors(string const & node_label) {
    uint node_id = m_label2Id[node_label];
    return m_adj[node_id].size();
}

double Graph::edge_weight(string const & u_label, string const & v_label) {
    uint u_id = m_label2Id[u_label];
    uint v_id = m_label2Id[v_label];

    for (uint i = 0; i < m_adj[u_id].size(); i++) {
        if (v_id == m_adj[u_id][i].first)
            return m_adj[u_id][i].second;
    }
    return -1;
}

vector<string> Graph::neighbors(string const & node_label) {
    vector<string> rt;

    uint node_id = m_label2Id[node_label];
    for (uint i = 0; i < m_adj[node_id].size(); i++) {
        uint neighbor_id = m_adj[node_id][i].first;
        rt.push_back(m_id2label[neighbor_id]);
    }

    return rt;
}

vector<string> Graph::shortest_path_unweighted(string const & start_label, string const & end_label) {
    vector<string> path;
    if (BFS(m_adj, start_label, end_label, path)) {
        return path;
    }

    vector<string> _empty;
    return _empty;
}

bool Graph::BFS(vector<vector<idbl>> adj, string srcLabel, string destLabel, vector<string> &pathResult)
{
    // cout << "BFS - start" << endl;
    list<int> queue;
    bool visited[m_iNumNodes];

    for (uint i = 0; i < m_iNumNodes; i++) {
        visited[i] = false;
    }
 
    unsigned int firstNodeId = m_label2Id[srcLabel];
    unsigned int destId = m_label2Id[destLabel];

    queue.push_back(firstNodeId);
 
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop_front();
        if (visited[u] == false) {
            visited[u] = true;

            pathResult.push_back(m_id2label[u]);

            // Exception, src is dest => STOP
            if (firstNodeId == destId) {
                return true;
            }
            // add all neighbor of current point
            for (uint i = 0; i < adj[u].size(); i++) {
                uint newId = adj[u][i].first;
                if (!visited[newId])
                    queue.push_back(newId);

                // Stop BFS if destination found.
                if (newId == destId) {
                    string stringOfNewNode = m_id2label[newId];
                    pathResult.push_back(stringOfNewNode);
                    // cout << "BFS - end" << endl;
                    return true;
                }
            }
        }
    }

    return false; // After travesal all graph, not found any path to dest
}


vector<tuple<string,string,double>> Graph::shortest_path_weighted(string const & start_label, string const & end_label) {
    // TODO
    vector<tuple<string,string,double>> result;
    if (dijkstra(m_adj, start_label, end_label, result)) {
        return result;
    }

    vector<tuple<string,string,double>> _empty;
    _empty.push_back(make_tuple(start_label, end_label, -1));
    return _empty;
}

vector<vector<string>> Graph::connected_components(double const & threshold) {
    const uint numOfNodes = m_id2label.size();
    bool visited[numOfNodes];
    vvs result;

    // Mark all the vertices as not visited
    for (uint i = 0; i < numOfNodes; i++) {
        visited[i] = UNVISITED;
    }

    for (uint v = 0; v < numOfNodes; v++) {
        if (visited[v] == UNVISITED) {
#ifdef LOG
            cout << __func__ << " - Num of nodes: " << numOfNodes << endl;
            cout << __func__ << " - Unvisited at: " << v << endl;
#endif
            vs oneResult;
            // push start of DFS node to result as alway
            oneResult.push_back(m_id2label[v]);
            // get all reachable vertices from v
            dfs(v, visited, oneResult);
            // return from DFS, means new connection is detected
            result.push_back(oneResult);
        }
    }

    return result;
}

void Graph::setVisited(bool visited[], uint visitedSize, uint id)
{
#ifdef LOG
    cout << __func__ << " - setVisited at id: " << id << endl;
#endif
    if (id < visitedSize) {
        visited[id] = VISITED;
    }
#ifdef LOG
    cout << "visited : ";
    for (uint i = 0; i < visitedSize; i++) {cout << visited[i] << " ";}
    cout << endl;
#endif
}

void Graph::dfs(uint id, bool visited[], vs& result) {
    cout << __func__ << " - checking at id = : " << id << endl;
    // Add first point to result as alway

    uint numOfNei = m_adj[id].size();
    setVisited(visited, m_id2label.size(), id);

    // Check all neighbors
    if (numOfNei) {
        for (uint i = 0; i < numOfNei; i++) {
            // Get all neighbors of current nodeid
            uint neiNodeid = m_adj[id][i].first;
            if (visited[neiNodeid] == UNVISITED) {
                string neiNodeLabel = m_id2label[neiNodeid];
#ifdef LOG
                cout << __func__ << " - Num of nodes: " << numOfNei << endl;
                cout << __func__ << " - Unvisited at: " << neiNodeid << endl;
                cout << __func__ << " - push_back : " << neiNodeLabel << endl;
#endif
                result.push_back(neiNodeLabel);
                dfs(m_adj[id][i].first, visited, result);
            }
        }
    } else {
#ifdef LOG
        cout << "Go to end of connections" << endl;
#endif
        for (string str : result) {cout << str;}
            cout << endl;
        return;
    }
}

double Graph::smallest_connecting_threshold(string const & start_label, string const & end_label) {
    // TODO
}

vector<string> Graph::split(const char *phrase, string delimiter) {
    vector<string> _list;
    string s = string(phrase);
    size_t pos = 0;
    string token;

    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        _list.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    _list.push_back(s);
    return _list;
}

void Graph::initVar() {
    m_iNumNodes = 0;
    m_iNumEdges = 0;
    m_id2label.clear();
    m_label2Id.clear();
}

// A  function to find the vertex with minimum distance value, from the set of vertices not yet included in shortest path tree
int Graph::minDistance(double dist[], bool visited[])
{
    // Initialize min value
    int min = INT_MAX, min_index;
  
    for (uint v = 0; v < m_iNumNodes; v++)
        if (visited[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
  
    return min_index;
}

bool Graph::dijkstra(vector<vector<idbl>> adj, string srcLabel, string destLabel, vector<tuple<string, string, double>>& result)
{
    unsigned int srdId = m_label2Id[srcLabel];
    unsigned int destId = m_label2Id[destLabel];
    
    double distance[m_iNumNodes];
    for (uint i = 0; i < m_iNumNodes; i++)  distance[i] = INT_MAX;

    //start from src node
    srdId = m_label2Id[srcLabel];
    destId = m_label2Id[destLabel];

    priority_queue<dbli, vector<dbli>, greater<dbli>> pq;
    pq.push(dbli(0, srdId));

    while (!pq.empty()) {
        dbli front = pq.top();
        pq.pop();

        double d = front.first;
        uint uId = front.second;

        if (d > distance[uId]) {
            continue;
        }

    for (uint i = 0; i < adj[uId].size(); i++) {
        dbli nei = dbli(adj[uId][i].second, adj[uId][i].first); // dbli(weight - id)
        if (d + nei.first > distance[nei.second]) {
            distance[nei.second] = d + nei.first;
            pq.push(nei);
        }
    }



    }
    return false;
}

int minDistance(double dist[], bool sptSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;
    // for (uint v = 0; v < V; v++)
    //     if (sptSet[v] == false && dist[v] <= min)
    //         min = dist[v], min_index = v;
    return min_index;
}