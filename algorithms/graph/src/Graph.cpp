#include "Graph.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <limits.h>
#include <list>

using namespace std;

Graph::Graph(const char* const & edgelist_csv_fn) {
    // init every variable
    initVar();

    // Read from file to format
    string _line;
    ifstream _csvFile;
    _csvFile.open(edgelist_csv_fn);

    while (getline(_csvFile, _line)) {
        // cout << _line << endl;
        std::vector<std::string> v = split(_line.c_str(), ",");
        
        // Make graph
        string _nodeLabel = v[0];
        string _neighborName = v[1];
        double _weight = atof(v[2].c_str());

        m_iNumEdges++;
        // cout << "m_iNumEdges++ = " << m_iNumEdges << endl;
        appendNodes(m_adj, _nodeLabel, _neighborName, _weight);

    }

    m_iNumEdges = m_adj.size();

}

Graph::~Graph() {
}

unsigned int Graph::num_nodes() {
    // TODO
    return m_iNumEdges;
}

vector<string> Graph::nodes() {
    vector<string> vt;
    for (auto i : m_adj) {
        vt.push_back(i.nodeLabel);
    }

    return vt;
}

unsigned int Graph::num_edges() {
    return m_iNumEdges;
}

unsigned int Graph::num_neighbors(string const & node_label) {
    unsigned int nodeId = getNodeIdByLabel(m_adj, node_label);
    return m_adj[nodeId].neighbors.size();
}

double Graph::edge_weight(string const & u_label, string const & v_label) {
    unsigned int u_id = getNodeIdByLabel(m_adj, u_label);
    for (int i = 0; i < m_adj[u_id].neighbors.size(); i++) {
        if (v_label == m_adj[u_id].neighbors[i].first)
            return m_adj[u_id].neighbors[i].second;
    }
}

vector<string> Graph::neighbors(string const & node_label) {
    vector<string> rt;

    unsigned int u_id = getNodeIdByLabel(m_adj, node_label);
    for (int i = 0; i < m_adj[u_id].neighbors.size(); i++) {
        rt.push_back(m_adj[u_id].neighbors[i].first);
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
    // remove connection larger than threshold
    vector<Node> adj = m_adj;
    int iNumNode = m_iNumNodes;
    // for (int i = 0 ; i < iNumNode; i++) {
    //     for (auto it = adj[i].neighbors.begin(); it != adj[i].neighbors.end(); ++it) {
    //         if (it->second > threshold) {
    //             adj[i].neighbors.erase(it);
    //             i--;
    //             iNumNode--;
    //         }
    //     }
    // }

    unsigned int newAdjSize = adj.size();
    vector<vector<string>> result;
    // Mark all the vertices as not visited
    bool* visited = new bool[newAdjSize];
    for (int v = 0; v < newAdjSize; v++)
        visited[v] = false;
 
    for (int v = 0; v < newAdjSize; v++) {
        vector<string> oneResult;
        if (visited[v] == false) {
            // get all reachable vertices from v
            DFSUtil(adj, threshold, adj[v].nodeLabel, visited, oneResult);
            result.push_back(oneResult);
        }
    }
    delete[] visited;

    return result;
}

void Graph::DFSUtil(vector<Node> adj, double threhold ,string srcLabel, bool visited[], vector<string>& result)
{
    // Mark the current node as visited and print it
    uint srcId = getNodeIdByLabel(adj, srcLabel);
    visited[srcId] = true;
    // cout << "DFSUtil - pushback to result: " << srcLabel << endl;
    result.push_back(srcLabel);

    // cout << srcId << endl;
    // Recur for all the vertices adjacent to this vertex
    for (auto i = adj[srcId].neighbors.begin(); i != adj[srcId].neighbors.end(); ++i) {
        string currentNodeLabel = i->first;
        double distance = i->second;
        uint currentNodeId = getNodeIdByLabel(adj, currentNodeLabel);
        if (distance <= threhold) {
            if (!visited[currentNodeId]) {
                DFSUtil(adj, threhold, currentNodeLabel, visited, result);
            }
        } else {
            visited[currentNodeId] = true;
        }
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
}

int Graph::getNodeIdByLabel(vector<Node> adj, string nodeLabel)
{
    for (int i = 0; i < adj.size(); i++) {
        if (adj[i].nodeLabel == nodeLabel)
            return i;
    }
    // if not found
    return -1; // addNewNode(m_adj, nodeLabel);
}

void Graph::appendNodes(vector<Node> adj, string label, string neiLabel, double weight)
{
    // cout << "appendNodes - start " << endl;
    int nodeID = getNodeIdByLabel(adj, label);
    int nodeNeiID = getNodeIdByLabel(adj, neiLabel);
    // cout << "appendNodes - nodeId: " << nodeID << ", nodeNeiId: " << nodeNeiID << endl;

    if (nodeID < 0)
        nodeID = addNewNode(m_adj, label);

    if (nodeNeiID < 0) 
        nodeNeiID = addNewNode(m_adj, neiLabel);

    // cout << "appendNodes - addNewNode - nodeId: " << nodeID << ", nodeNeiId: " << nodeNeiID << endl;
    m_adj[nodeID].neighbors.push_back(make_pair(neiLabel, weight));
    m_adj[nodeNeiID].neighbors.push_back(make_pair(label, weight));
    // cout << "appendNodes - end" << endl;
}

unsigned int Graph::addNewNode(vector<Node>& adj, string label)
{
    adj.push_back(Node(label));
    return adj.size() - 1;
}

bool Graph::BFS(vector<Node> adj, string srcLabel, string destLabel, vector<string> &pathResult)
{
    // cout << "BFS - start" << endl;
    list<int> queue;
    bool visited[m_iNumNodes];

    for (int i = 0; i < m_iNumNodes; i++) {
        visited[i] = false;
    }
 
    unsigned int firstNodeId = getNodeIdByLabel(m_adj, srcLabel);
    unsigned int destId = getNodeIdByLabel(adj, destLabel);

    queue.push_back(firstNodeId);
 
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop_front();
        if (visited[u] == false) {
            visited[u] = true;

            pathResult.push_back(adj[u].nodeLabel);

            // Exception, src is dest => STOP
            if (firstNodeId == destId) {
                return true;
            }
            // add all neighbor of current point
            for (int i = 0; i < adj[u].neighbors.size(); i++) {
                string newAddLabel = adj[u].neighbors[i].first;
                unsigned int newId = getNodeIdByLabel(adj, newAddLabel);
                if (!visited[newId])
                    queue.push_back(newId);

                // Stop BFS if destination found.
                if (newId == destId) {

                    pathResult.push_back(newAddLabel);
                    // cout << "BFS - end" << endl;
                    return true;
                }
            }
        }
    }

    return false; // After travesal all graph, not found any path to dest
}

// A  function to find the vertex with minimum distance value, from the set of vertices not yet included in shortest path tree
int Graph::minDistance(double dist[], bool visited[])
{
    // Initialize min value
    int min = INT_MAX, min_index;
  
    for (int v = 0; v < m_iNumNodes; v++)
        if (visited[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
  
    return min_index;
}

bool Graph::dijkstra(vector<Node> adj, string srcLabel, string destLabel, vector<tuple<string,string,double>>& result)
{
    unsigned int srdId = getNodeIdByLabel(adj, srcLabel);
    unsigned int destId = getNodeIdByLabel(adj, destLabel);
    
    list<int> queue;
    double dist[m_iNumNodes];
    bool visited[m_iNumNodes];
    vector<int> selectedNode;
    selectedNode.push_back(srdId);

    dist[srdId] = 0;
    for (int i = 0; i < m_iNumNodes; i++) {
        visited[i] = false;
        if (i != srdId) {
            dist[i] = INT_MAX;
        }
    }

    queue.push_back(srdId);
 
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop_front();

        for (int i = 0; i < adj[u].neighbors.size(); i++) {
            string newAddLabel = adj[u].neighbors[i].first;
            unsigned int newId = getNodeIdByLabel(adj, newAddLabel);
            double nextDistance = adj[u].neighbors[i].second;

            if (!visited[newId]) {
                queue.push_back(newId);
                double alt = dist[u] + nextDistance;
                if (alt < dist[newId]) {
                    dist[newId] = alt;
                }
            }

            // Stop if destination found.
            if (newId == destId) {
                cout << dist[newId] << endl;
                // pathResult.push_back(newAddLabel);
                return true;
            }
        }

        // choose min node to mark visited
        int min_id = minDistance(dist, visited);
        visited[min_id] = true;
    }

    return false;
}

int minDistance(int dist[], bool sptSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;
    // for (int v = 0; v < V; v++)
    //     if (sptSet[v] == false && dist[v] <= min)
    //         min = dist[v], min_index = v;
    return min_index;
}