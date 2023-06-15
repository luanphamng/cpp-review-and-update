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
        // get from xls
        std::vector<std::string> v = split(_line.c_str(), ",");
        string _nodeLabel = v[0];
        string _neighborName = v[1];
        double _weight = atof(v[2].c_str());

        // Check if this is the new node
        if (m_label2Id.find(_nodeLabel) == m_label2Id.end()) {
            uint id = m_label2Id.size(); // add to last index
            m_label2Id.insert({_nodeLabel, id});
            m_id2label.insert({id, _nodeLabel});
        }

        if (m_label2Id.find(_neighborName) == m_label2Id.end()) {
            uint id = m_label2Id.size(); // add to last index
            m_label2Id.insert({_neighborName, id});
            m_id2label.insert({id, _neighborName});
        }

        m_adj[m_label2Id[_nodeLabel]].push_back(make_pair(m_label2Id[_neighborName], _weight));
        m_adj[m_label2Id[_neighborName]].push_back(make_pair(m_label2Id[_nodeLabel], _weight));
        m_iNumEdges++;
    }
}

Graph::~Graph() {
}

unsigned int Graph::num_nodes() {
    // TODO
    return m_iNumEdges;
}

vector<string> Graph::nodes() {
    vector<string> vt;
    for (auto i : m_id2label) {
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

    for (int i = 0; i < m_adj[u_id].size(); i++) {
        if (v_id == m_adj[u_id][i].first)
            return m_adj[u_id][i].second;
    }
    return -1;
}

vector<string> Graph::neighbors(string const & node_label) {
    vector<string> rt;

    uint node_id = m_label2Id[node_label];
    for (int i = 0; i < m_adj[node_id].size(); i++) {
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

bool Graph::BFS(vector<pair<int, double>> adj[], string srcLabel, string destLabel, vector<string> &pathResult)
{
    // cout << "BFS - start" << endl;
    list<int> queue;
    bool visited[m_iNumNodes];

    for (int i = 0; i < m_iNumNodes; i++) {
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
            for (int i = 0; i < adj[u].size(); i++) {
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
    m_id2label.clear();
    m_label2Id.clear();
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

bool Graph::dijkstra(vector<pair<int, double>> adj[], string srcLabel, string destLabel, vector<tuple<string, string, double>>& result)
{
    unsigned int srdId = m_label2Id[srcLabel];
    unsigned int destId = m_label2Id[destLabel];
    
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

        for (int i = 0; i < adj[u].size(); i++) {
            uint newId = adj[u][i].first;
            double nextDistance = adj[u][i].second;

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

int minDistance(double dist[], bool sptSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;
    // for (int v = 0; v < V; v++)
    //     if (sptSet[v] == false && dist[v] <= min)
    //         min = dist[v], min_index = v;
    return min_index;
}