#ifndef DECISION_TREE_H
#define DECISION_TREE_H

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "linked_tree.h"

using namespace std;

struct DecisionNodeData {
  string content;
  string incomingEdge;
  int preorderPosition;

  DecisionNodeData(string nodeContent = "", string edgeLabel = "", int position = 0)
      : content(nodeContent), incomingEdge(edgeLabel), preorderPosition(position) {}
};

class DecisionTree {
private:
  struct Record {
    int level;
    int preorderPosition;
    string edgeLabel;
    string content;
  };

  LinkedTree<DecisionNodeData> tree;
  unordered_map<int, LinkedTree<DecisionNodeData>::Position> positionMap;

  // Removes leading spaces and tabs from a string.
  string ltrim(string value) {
    int index = 0;
    while (index < (int)value.size() &&
           (value[index] == ' ' || value[index] == '\t' || value[index] == '\r')) {
      index++;
    }
    return value.substr(index);
  }

  // Joins list entries with comma separators.
  string joinList(vector<string> &items) {
    if (items.empty()) {
      return "None";
    }

    string result = "";
    for (int i = 0; i < (int)items.size(); i++) {
      if (i > 0) {
        result += ", ";
      }
      result += items[i];
    }
    return result;
  }

  // Returns subtree height for a position.
  int height(LinkedTree<DecisionNodeData>::Position position) {
    if (position.isNull() || position.isExternal()) {
      return 0;
    }

    int maxHeight = 0;
    vector<LinkedTree<DecisionNodeData>::Position> kids = tree.children(position);
    for (int i = 0; i < (int)kids.size(); i++) {
      int childHeight = height(kids[i]);
      if (childHeight > maxHeight) {
        maxHeight = childHeight;
      }
    }
    return 1 + maxHeight;
  }

  // Counts internal nodes recursively.
  int internalCount(LinkedTree<DecisionNodeData>::Position position) {
    if (position.isNull()) {
      return 0;
    }

    int total = position.isInternal() ? 1 : 0;
    vector<LinkedTree<DecisionNodeData>::Position> kids = tree.children(position);
    for (int i = 0; i < (int)kids.size(); i++) {
      total += internalCount(kids[i]);
    }
    return total;
  }

  // Counts external nodes recursively.
  int externalCount(LinkedTree<DecisionNodeData>::Position position) {
    if (position.isNull()) {
      return 0;
    }
    if (position.isExternal()) {
      return 1;
    }

    int total = 0;
    vector<LinkedTree<DecisionNodeData>::Position> kids = tree.children(position);
    for (int i = 0; i < (int)kids.size(); i++) {
      total += externalCount(kids[i]);
    }
    return total;
  }

  // Returns true when every node has at most two children.
  bool isBinary(LinkedTree<DecisionNodeData>::Position position) {
    if (position.isNull()) {
      return true;
    }

    vector<LinkedTree<DecisionNodeData>::Position> kids = tree.children(position);
    if ((int)kids.size() > 2) {
      return false;
    }
    for (int i = 0; i < (int)kids.size(); i++) {
      if (!isBinary(kids[i])) {
        return false;
      }
    }
    return true;
  }

  // Returns true when every internal node has exactly two children.
  bool isProperBinary(LinkedTree<DecisionNodeData>::Position position) {
    if (position.isNull() || position.isExternal()) {
      return true;
    }

    vector<LinkedTree<DecisionNodeData>::Position> kids = tree.children(position);
    if ((int)kids.size() != 2) {
      return false;
    }
    for (int i = 0; i < (int)kids.size(); i++) {
      if (!isProperBinary(kids[i])) {
        return false;
      }
    }
    return true;
  }

  // Returns true when all leaves are found at one depth.
  bool leavesSameDepth(LinkedTree<DecisionNodeData>::Position position, int depth,
                       int &leafDepth) {
    if (position.isNull()) {
      return true;
    }

    if (position.isExternal()) {
      if (leafDepth == -1) {
        leafDepth = depth;
      }
      return depth == leafDepth;
    }

    vector<LinkedTree<DecisionNodeData>::Position> kids = tree.children(position);
    for (int i = 0; i < (int)kids.size(); i++) {
      if (!leavesSameDepth(kids[i], depth + 1, leafDepth)) {
        return false;
      }
    }
    return true;
  }

  // Returns true when tree is height balanced.
  bool balancedHeight(LinkedTree<DecisionNodeData>::Position position,
                      int &subtreeHeight) {
    if (position.isNull()) {
      subtreeHeight = 0;
      return true;
    }
    if (position.isExternal()) {
      subtreeHeight = 0;
      return true;
    }

    vector<LinkedTree<DecisionNodeData>::Position> kids = tree.children(position);
    int firstHeight = 0;
    int secondHeight = 0;

    for (int i = 0; i < (int)kids.size(); i++) {
      int childHeight = 0;
      if (!balancedHeight(kids[i], childHeight)) {
        return false;
      }
      if (i == 0) {
        firstHeight = childHeight;
      } else if (i == 1) {
        secondHeight = childHeight;
      }
    }

    if ((int)kids.size() == 1) {
      secondHeight = -1;
    }

    int diff = firstHeight - secondHeight;
    if (diff < 0) {
      diff = -diff;
    }
    if (diff > 1) {
      return false;
    }

    subtreeHeight = 1 + (firstHeight > secondHeight ? firstHeight : secondHeight);
    return true;
  }

  // Writes preorder tree visualization with required indentation.
  void writeVisualization(LinkedTree<DecisionNodeData>::Position position, int level,
                          ofstream &out) {
    if (position.isNull()) {
      return;
    }

    DecisionNodeData data = *position;
    for (int i = 0; i < level * 2; i++) {
      out << "-";
    }

    if (level > 0) {
      out << "[" << data.incomingEdge << "] ";
    }
    out << data.content << "\n";

    vector<LinkedTree<DecisionNodeData>::Position> kids = tree.children(position);
    for (int i = 0; i < (int)kids.size(); i++) {
      writeVisualization(kids[i], level + 1, out);
    }
  }

public:
  // Initializes an empty decision tree.
  DecisionTree() {}

  // Parses one input line into a record.
  bool parseLine(string line, bool isRootLine, Record &record) {
    string cleaned = ltrim(line);
    if (cleaned.size() == 0) {
      return false;
    }

    istringstream iss(cleaned);
    int level;
    int position;

    if (!(iss >> level >> position)) {
      if (!isRootLine) {
        return false;
      }
      record.level = 0;
      record.preorderPosition = 1;
      record.edgeLabel = "";
      record.content = cleaned;
      return true;
    }

    record.level = level;
    record.preorderPosition = position;
    record.edgeLabel = "";

    if (level == 0) {
      string rest;
      getline(iss, rest);
      record.content = ltrim(rest);
      return record.content.size() > 0;
    }

    string edge;
    if (!(iss >> edge)) {
      return false;
    }
    record.edgeLabel = edge;

    string rest;
    getline(iss, rest);
    record.content = ltrim(rest);
    return record.content.size() > 0;
  }

  // Builds the tree from an input text file.
  bool buildFromFile(string filePath) {
    ifstream in(filePath);
    if (!in.is_open()) {
      return false;
    }

    vector<Record> records;
    string line;
    bool first = true;

    while (getline(in, line)) {
      Record record;
      if (parseLine(line, first, record)) {
        records.push_back(record);
        first = false;
      }
    }

    if (records.empty()) {
      return false;
    }

    sort(records.begin(), records.end(), [](Record a, Record b) {
      return a.preorderPosition < b.preorderPosition;
    });

    Record rootRecord = records[0];
    DecisionNodeData rootData(rootRecord.content, "", rootRecord.preorderPosition);
    LinkedTree<DecisionNodeData>::Position rootPosition = tree.addRoot(rootData);
    positionMap[rootRecord.preorderPosition] = rootPosition;

    vector<LinkedTree<DecisionNodeData>::Position> levelStack;
    levelStack.push_back(rootPosition);

    for (int i = 1; i < (int)records.size(); i++) {
      Record record = records[i];
      if (record.level <= 0) {
        continue;
      }

      while ((int)levelStack.size() > record.level) {
        levelStack.pop_back();
      }
      if ((int)levelStack.size() != record.level) {
        continue;
      }

      LinkedTree<DecisionNodeData>::Position parentPosition = levelStack.back();
      if (parentPosition.isNull()) {
        continue;
      }

      DecisionNodeData newData(record.content, record.edgeLabel, record.preorderPosition);
      LinkedTree<DecisionNodeData>::Position newPosition =
          tree.addChild(parentPosition, newData);

      positionMap[record.preorderPosition] = newPosition;
      levelStack.push_back(newPosition);
    }

    return true;
  }

  // Writes tree visualization and property analysis to a file.
  bool writeAboutTree(string filePath) {
    LinkedTree<DecisionNodeData>::Position rootPosition = tree.root();
    if (rootPosition.isNull()) {
      return false;
    }

    ofstream out(filePath);
    if (!out.is_open()) {
      return false;
    }

    out << "Tree Visualization\n";
    writeVisualization(rootPosition, 0, out);
    out << "\n";

    out << "Tree Properties\n";
    out << "Root node: " << (*rootPosition).content << "\n";
    out << "Number of internal nodes: " << internalCount(rootPosition) << "\n";
    out << "Number of external (leaf) nodes: " << externalCount(rootPosition) << "\n";
    out << "Tree height: " << height(rootPosition) << "\n";

    vector<string> internalItems;
    vector<string> externalItems;
    vector<LinkedTree<DecisionNodeData>::Position> preorderItems = tree.preorder();
    for (int i = 0; i < (int)preorderItems.size(); i++) {
      if (preorderItems[i].isInternal()) {
        internalItems.push_back((*preorderItems[i]).content);
      } else {
        externalItems.push_back((*preorderItems[i]).content);
      }
    }

    out << "Internal nodes (preorder): " << joinList(internalItems) << "\n";
    out << "External nodes (preorder): " << joinList(externalItems) << "\n";
    out << "\n";

    out << "Binary Tree Analysis\n";
    bool binary = isBinary(rootPosition);
    out << "Is it a Binary Tree? " << (binary ? "Yes" : "No") << "\n";

    if (binary) {
      bool proper = isProperBinary(rootPosition);
      int leafDepth = -1;
      bool perfect = proper && leavesSameDepth(rootPosition, 0, leafDepth);
      int rootHeight = 0;
      bool balanced = balancedHeight(rootPosition, rootHeight);

      out << "Proper Tree: " << (proper ? "Yes" : "No") << "\n";
      out << "Perfect Tree: " << (perfect ? "Yes" : "No") << "\n";
      out << "Balanced Tree: " << (balanced ? "Yes" : "No") << "\n";
    }

    return true;
  }

  // Returns true when a position exists in the tree.
  bool hasPosition(int preorderPosition) {
    return positionMap.find(preorderPosition) != positionMap.end();
  }

  // Returns node content by preorder position.
  string nodeContent(int preorderPosition) {
    if (!hasPosition(preorderPosition)) {
      return "";
    }
    return (*positionMap[preorderPosition]).content;
  }

  // Returns one ancestor content by preorder position.
  string oneAncestor(int preorderPosition) {
    if (!hasPosition(preorderPosition)) {
      return "None";
    }

    LinkedTree<DecisionNodeData>::Position nodePosition = positionMap[preorderPosition];
    LinkedTree<DecisionNodeData>::Position parentPosition = nodePosition.parent();
    if (parentPosition.isNull()) {
      return "None";
    }
    return (*parentPosition).content;
  }

  // Returns one descendant content by preorder position.
  string oneDescendant(int preorderPosition) {
    if (!hasPosition(preorderPosition)) {
      return "None";
    }

    LinkedTree<DecisionNodeData>::Position nodePosition = positionMap[preorderPosition];
    LinkedTree<DecisionNodeData>::Position childPosition = nodePosition.firstChild();
    if (childPosition.isNull()) {
      return "None";
    }
    return (*childPosition).content;
  }

  // Returns one sibling content by preorder position.
  string oneSibling(int preorderPosition) {
    if (!hasPosition(preorderPosition)) {
      return "None";
    }

    LinkedTree<DecisionNodeData>::Position nodePosition = positionMap[preorderPosition];
    LinkedTree<DecisionNodeData>::Position parentPosition = nodePosition.parent();
    if (parentPosition.isNull()) {
      return "None";
    }

    vector<LinkedTree<DecisionNodeData>::Position> siblings = tree.children(parentPosition);
    int nodePositionId = (*nodePosition).preorderPosition;
    for (int i = 0; i < (int)siblings.size(); i++) {
      if ((*siblings[i]).preorderPosition != nodePositionId) {
        return (*siblings[i]).content;
      }
    }
    return "None";
  }

  // Returns total number of nodes in the tree.
  int size() { return tree.size(); }
};

#endif
