#include <iostream>
#include <string>
#include <vector>

#include "graph.h"

using namespace std;

// Prints program menu.
void printMenu() {
  cout << "\nWhat would you like to do?\n";
  cout << "1. Find edges incident on a vertex\n";
  cout << "2. Find a path in the graph\n";
  cout << "3. Insert an edge\n";
  cout << "4. Erase a vertex\n";
  cout << "Choice: ";
}

// Runs interactive graph menu.
void runMenu(Graph &graph) {
  while (true) {
    printMenu();
    int choice;
    cin >> choice;

    switch (choice) {
    case 1: {
      string vertexName;
      cout << "Enter vertex: ";
      cin >> vertexName;
      Graph::Vertex vertex = graph.findVertex(vertexName);
      if (vertex.isNull()) {
        cout << "Vertex not found" << endl;
        break;
      }

      vector<Graph::Edge> incident = vertex.incidentEdges();
      for (int i = 0; i < (int)incident.size(); i++) {
        vector<Graph::Vertex> ends = incident[i].endVertices();
        Graph::Vertex other = ends[0];
        if ((*other) == vertexName) {
          other = ends[1];
        }
        cout << vertexName << " to " << (*other) << " is " << (*incident[i]) << endl;
      }
      break;
    }
    case 2: {
      string start;
      string end;
      cout << "Enter start vertex: ";
      cin >> start;
      cout << "Enter end vertex: ";
      cin >> end;

      vector<string> path = graph.findPath(start, end);
      if ((int)path.size() < 3) {
        cout << "No valid path found" << endl;
      } else {
        for (int i = 0; i < (int)path.size(); i++) {
          if (i > 0) {
            cout << " to ";
          }
          cout << path[i];
        }
        cout << endl;
      }
      break;
    }
    case 3: {
      string v;
      string w;
      string label;
      cout << "Enter first vertex: ";
      cin >> v;
      cout << "Enter second vertex: ";
      cin >> w;
      cout << "Enter edge label: ";
      cin >> label;

      Graph::Vertex first = graph.findVertex(v);
      Graph::Vertex second = graph.findVertex(w);

      if (first.isNull() || second.isNull()) {
        cout << "Vertex not found" << endl;
      } else if (first.isAdjacentTo(second)) {
        cout << "Edge already exists" << endl;
      } else {
        graph.insertEdge(first, second, label);
        cout << "Edge inserted" << endl;
      }
      break;
    }
    case 4: {
      string vertexName;
      cout << "Enter vertex: ";
      cin >> vertexName;
      Graph::Vertex vertex = graph.findVertex(vertexName);
      if (vertex.isNull()) {
        cout << "Vertex not found" << endl;
      } else {
        graph.eraseVertex(vertex);
        cout << "Vertex removed" << endl;
      }
      break;
    }
    default:
      break;
    }
  }
}

int main() {
  cout << "Hello!" << endl;
  cout << "Enter the file name: ";

  string fileName;
  cin >> fileName;

  Graph graph(fileName);
  cout << "\nThank you. Your graph is ready." << endl;

  runMenu(graph);
  return 0;
}
