#include "Graph.h"
#include <queue>

Graph::~Graph() {
    for (Edge* e : adj) while (e) { Edge* t = e; e = e->next; delete t; }
}

int Graph::idxOf(const std::string& isbn) const {
    for (size_t i = 0; i < isbns.size(); ++i) if (isbns[i] == isbn) return i;
    return -1;
}

int Graph::addVertex(const std::string& isbn) {
    int idx = idxOf(isbn);
    if (idx != -1) return idx;
    isbns.push_back(isbn); adj.push_back(nullptr);
    return isbns.size() - 1;
}

void Graph::addEdge(const std::string& u, const std::string& v) {
    int iu = addVertex(u), iv = addVertex(v);
    if (iu == iv) return;
    adj[iu] = new Edge(iv, adj[iu]);
    adj[iv] = new Edge(iu, adj[iv]);
}

std::vector<std::string> Graph::suggestBFS(const std::string& isbn, int limit) const {
    std::vector<std::string> res;
    int s = idxOf(isbn);
    if (s == -1) return res;
    std::vector<bool> vis(isbns.size(), false);
    std::queue<int> q; q.push(s); vis[s] = true;
    while (!q.empty() && (int)res.size() < limit) {
        int u = q.front(); q.pop();
        if (u != s) res.push_back(isbns[u]);
        for (Edge* e = adj[u]; e; e = e->next)
            if (!vis[e->to]) { vis[e->to] = true; q.push(e->to); }
    }
    return res;
}
