#ifndef GRAPH_H
#define GRAPH_H

#include <fstream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Graph {
public:
  class Vertex;
  class Edge;

private:
  vector<string> vertexNames;
  unordered_map<string, int> indexMap;
  vector<vector<string>> edgeMatrix;

  // Splits a tab-delimited line.
  vector<string> splitTab(string line) {
    vector<string> parts;
    string part;
    stringstream ss(line);

    while (getline(ss, part, '\t')) {
      if (part.size() > 0 && part[part.size() - 1] == '\r') {
        part = part.substr(0, part.size() - 1);
      }
      parts.push_back(part);
    }
    return parts;
  }

  // Returns true if an edge label already exists.
  bool hasEdge(int a, int b) {
    return a >= 0 && b >= 0 && a < (int)edgeMatrix.size() &&
           b < (int)edgeMatrix.size() && edgeMatrix[a][b] != "";
  }

  // Rebuilds the name to index map after a vertex erase.
  void rebuildIndexMap() {
    indexMap.clear();
    for (int i = 0; i < (int)vertexNames.size(); i++) {
      indexMap[vertexNames[i]] = i;
    }
  }

public:
  class Vertex {
  private:
    Graph *graph;
    int index;
    friend class Graph;

  public:
    Vertex(Graph *g = nullptr, int i = -1) {
      graph = g;
      index = i;
    }

    string operator*() { return graph->vertexNames[index]; }

    vector<Edge> incidentEdges() {
      vector<Edge> result;
      if (isNull()) {
        return result;
      }

      for (int i = 0; i < (int)graph->vertexNames.size(); i++) {
        if (graph->edgeMatrix[index][i] != "") {
          result.push_back(Graph::Edge(graph, index, i));
        }
      }
      return result;
    }

    bool isAdjacentTo(Vertex v) {
      if (isNull() || v.isNull()) {
        return false;
      }
      return graph->areAdjacent(*this, v);
    }

    bool isNull() { return graph == nullptr || index < 0; }
  };

  class Edge {
  private:
    Graph *graph;
    int uIndex;
    int vIndex;
    friend class Graph;

  public:
    Edge(Graph *g = nullptr, int u = -1, int v = -1) {
      graph = g;
      uIndex = u;
      vIndex = v;
    }

    string operator*() { return graph->edgeMatrix[uIndex][vIndex]; }

    vector<Vertex> endVertices() {
      vector<Vertex> result;
      if (isNull()) {
        return result;
      }

      result.push_back(Graph::Vertex(graph, uIndex));
      result.push_back(Graph::Vertex(graph, vIndex));
      return result;
    }

    Vertex opposite(Vertex v) {
      if (isNull() || v.isNull()) {
        return Graph::Vertex(nullptr, -1);
      }
      if (v.index == uIndex) {
        return Graph::Vertex(graph, vIndex);
      }
      if (v.index == vIndex) {
        return Graph::Vertex(graph, uIndex);
      }
      return Graph::Vertex(nullptr, -1);
    }

    bool isAdjacentTo(Edge e) {
      if (isNull() || e.isNull()) {
        return false;
      }
      return uIndex == e.uIndex || uIndex == e.vIndex || vIndex == e.uIndex ||
             vIndex == e.vIndex;
    }

    bool isIncidentOn(Vertex v) {
      if (isNull() || v.isNull()) {
        return false;
      }
      return v.index == uIndex || v.index == vIndex;
    }

    bool isNull() { return graph == nullptr || uIndex < 0 || vIndex < 0; }
  };

  // Builds the graph from a file.
  Graph(string fileName) {
    ifstream input(fileName.c_str());
    string line;

    if (!getline(input, line)) {
      return;
    }

    vector<string> vertices = splitTab(line);
    for (int i = 0; i < (int)vertices.size(); i++) {
      insertVertex(vertices[i]);
    }

    while (getline(input, line)) {
      vector<string> parts = splitTab(line);
      if (parts.size() < 3) {
        continue;
      }
      Vertex first = findVertex(parts[0]);
      Vertex second = findVertex(parts[1]);
      insertEdge(first, second, parts[2]);
    }
  }

  // Returns all vertices.
  vector<Vertex> vertices() {
    vector<Vertex> result;
    for (int i = 0; i < (int)vertexNames.size(); i++) {
      result.push_back(Vertex(this, i));
    }
    return result;
  }

  // Returns all edges.
  vector<Edge> edges() {
    vector<Edge> result;
    for (int i = 0; i < (int)vertexNames.size(); i++) {
      for (int j = i + 1; j < (int)vertexNames.size(); j++) {
        if (edgeMatrix[i][j] != "") {
          result.push_back(Edge(this, i, j));
        }
      }
    }
    return result;
  }

  // Inserts a vertex if it does not already exist.
  Vertex insertVertex(string value) {
    if (indexMap.find(value) != indexMap.end()) {
      return Vertex(this, indexMap[value]);
    }

    vertexNames.push_back(value);
    indexMap[value] = (int)vertexNames.size() - 1;

    for (int i = 0; i < (int)edgeMatrix.size(); i++) {
      edgeMatrix[i].push_back("");
    }
    edgeMatrix.push_back(vector<string>(vertexNames.size(), ""));

    return Vertex(this, (int)vertexNames.size() - 1);
  }

  // Inserts an undirected edge.
  Edge insertEdge(Vertex v, Vertex w, string value) {
    if (v.isNull() || w.isNull() || v.index == w.index) {
      return Edge(nullptr, -1, -1);
    }
    if (hasEdge(v.index, w.index)) {
      return Edge(nullptr, -1, -1);
    }

    edgeMatrix[v.index][w.index] = value;
    edgeMatrix[w.index][v.index] = value;
    return Edge(this, v.index, w.index);
  }

  // Erases a vertex and its edges.
  bool eraseVertex(Vertex v) {
    if (v.isNull()) {
      return false;
    }

    int index = v.index;
    vertexNames.erase(vertexNames.begin() + index);
    edgeMatrix.erase(edgeMatrix.begin() + index);
    for (int i = 0; i < (int)edgeMatrix.size(); i++) {
      edgeMatrix[i].erase(edgeMatrix[i].begin() + index);
    }
    rebuildIndexMap();
    return true;
  }

  // Erases an edge.
  bool eraseEdge(Edge e) {
    if (e.isNull()) {
      return false;
    }

    edgeMatrix[e.uIndex][e.vIndex] = "";
    edgeMatrix[e.vIndex][e.uIndex] = "";
    return true;
  }

  // Finds a vertex by name.
  Vertex findVertex(string value) {
    if (indexMap.find(value) == indexMap.end()) {
      return Vertex(nullptr, -1);
    }
    return Vertex(this, indexMap[value]);
  }

  // Returns whether two vertices are connected.
  bool areAdjacent(Vertex v, Vertex w) {
    if (v.isNull() || w.isNull()) {
      return false;
    }
    return hasEdge(v.index, w.index);
  }

  // Finds a path with BFS.
  vector<string> findPath(string start, string end) {
    vector<string> result;
    Vertex s = findVertex(start);
    Vertex t = findVertex(end);
    if (s.isNull() || t.isNull()) {
      return result;
    }

    vector<int> parent(vertexNames.size(), -1);
    vector<bool> visited(vertexNames.size(), false);
    queue<int> q;
    q.push(s.index);
    visited[s.index] = true;

    while (!q.empty()) {
      int current = q.front();
      q.pop();
      if (current == t.index) {
        break;
      }

      for (int i = 0; i < (int)vertexNames.size(); i++) {
        if (!visited[i] && edgeMatrix[current][i] != "") {
          visited[i] = true;
          parent[i] = current;
          q.push(i);
        }
      }
    }

    if (!visited[t.index]) {
      return result;
    }

    vector<string> path;
    int current = t.index;
    while (current != -1) {
      path.push_back(vertexNames[current]);
      current = parent[current];
    }

    for (int i = (int)path.size() - 1; i >= 0; i--) {
      result.push_back(path[i]);
    }
    return result;
  }
};

#endif
