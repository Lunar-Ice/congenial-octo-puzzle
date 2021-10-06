#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stack>
#include <cstring>
#include <cmath>

using namespace std;

class eight_puzzle {
  private:
    string arr[3][3];
  
  public:
    eight_puzzle() {
      
    }
  
    eight_puzzle(string arrSetup) {
      stringstream ss(arrSetup);
      string tmp;
      
      for(int i = 0; i < 3; i++) {
	for(int j = 0; j < 3; j++) {
	  ss >> tmp;
	  arr[i][j] = tmp;
	}
      }
    }

  string getMove(string move) {
    string tmp[3][3];
    for(int i = 0; i < 3; i++) {
      for(int j = 0; j < 3; j++) {
	tmp[i][j] = arr[i][j];
      }
    }

    bool success = false;
    
    for(int i = 0; i < 3; i++) {
      for(int j = 0; j < 3; j++) {
	if(tmp[i][j] == "*") {
	  if(move == "right" && j < 2) {
	    string temp = tmp[i][j+1];
	    tmp[i][j+1] = tmp[i][j];
	    tmp[i][j] = temp;
	    success = true;
	  }
	  if(move == "left" && j > 0) {
	    string temp = tmp[i][j-1];
	    tmp[i][j-1] = tmp[i][j];
	    tmp[i][j] = temp;
	    success = true;
	  }
	  if(move == "up" && i > 0) {
	    string temp = tmp[i-1][j];
	    tmp[i-1][j] = tmp[i][j];
	    tmp[i][j] = temp;
	    success = true;
	  }
	  if(move == "down" && i < 2) {
	    string temp = tmp[i+1][j];
	    tmp[i+1][j] = tmp[i][j];
	    tmp[i][j] = temp;
	    success = true;
	  }
	  goto EndOfLoop;
	}
      }
    }

    EndOfLoop:
    
    if(!success) {
      return "";
    }
    
    string ret = "";
    
    for(int i = 0; i < 3; i++) {
      for(int j = 0; j < 3; j++) {
	ret += tmp[i][j] + " ";
      }
    }
    
    return ret;
  }

  bool isGoalState() {

    if(arr[1][1] != "*") {
      return false;
    }
    string puzzle_string = "";

    for(int i = 0; i < 3; i++) {
      for(int j = 0; j < 3; j++) {
	puzzle_string += arr[i][j] + " ";
      }
    }

    stringstream ss(puzzle_string);
    string curr, prev;

    ss >> prev;

    if(prev == "*") {
      return false;
    }
    
    while(ss >> curr) {
      if(curr != "*") {
	if(atoi(prev.c_str()) > atoi(curr.c_str())) {
	  return false;
	}
	prev = curr;
      }
    }
    
    return true;
  }

  int numOfMisplacedTiles() {
    int misplaced = 0;
    string puzzle_string = "";    

    for(int i = 0; i < 3; i++) {
      for(int j = 0; j < 3; j++) {
	puzzle_string += arr[i][j] + " ";
      }
    }

    string goal_string = "1 2 3 4 * 5 6 7 8";

    stringstream ss(puzzle_string);
    string curr_tile;

    stringstream gs(goal_string);
    string goal_tile;

    while(ss >> curr_tile && gs >> goal_tile) {
      if(curr_tile != goal_tile) {
	misplaced++;
      }
    }
    
    return misplaced;
  }

  void distanceHelper(string goal[3][3], string match, int &x, int &y) {
    for(int i = 0; i < 3; i++) {
      for(int j = 0; j < 3; j++) {
	if(match == goal[i][j]) {
	  x = i+1;
	  y = j+1;
	  return;
	}
      }
    }
  }
  
  int manhattanDistance() {
    int manhattanDistance = 0;

    string goal[3][3] = {{"1", "2", "3"}, {"4", "*", "5"}, {"6", "7", "8"}};
    
    int x, y = 0;

    for(int i = 0; i < 3; i++) {
      for(int j = 0; j < 3; j++) {
	if(arr[i][j] != "*" && arr[i][j] != goal[i][j]) {
	  distanceHelper(goal, arr[i][j], x, y);
	  manhattanDistance += (abs((i+1)-x) + abs((j+1)-y));
	}
      }
    }
    
    return manhattanDistance;
  }
  
  void print_puzzle() {
    for(int i = 0; i < 3; i++) {
      for(int j = 0; j < 3; j++) {
	cout << arr[i][j] << " ";
      }
      cout << endl;
    }
  }
};

class Node {
  private:
    eight_puzzle puzzle;
    Node* up;
    Node* down;
    Node* right;
    Node* left;
    int depth;
    bool isGoal;

  public:
  Node(string p, int d) {
    puzzle = eight_puzzle(p);
    depth = d;
    up = NULL;
    down = NULL;
    right = NULL;
    left = NULL;
    isGoal = puzzle.isGoalState();
  }

  eight_puzzle getPuzzle() {
    return puzzle;
  }

  int getDepth() {
    return depth;
  }
  
  Node* getUpNode() {
    return up;
  }

  void setUpNode(Node* node) {
    up = node;
  }

  Node* getDownNode() {
    return down;
  }

  void setDownNode(Node* node) {
    down = node;
  }

  Node* getRightNode() {
    return right;
  }

  void setRightNode(Node* node) {
    right = node;
  }

  Node* getLeftNode() {
    return left;
  }

  void setLeftNode(Node* node) {
    left = node;
  }

  bool goalState() {
    return isGoal;
  }

  void print_tree(Node* root) {
    root->getPuzzle().print_puzzle();
    if(root->getUpNode() != NULL) {
      print_tree(root->getUpNode());
    }
    if(root->getDownNode() != NULL) {
      print_tree(root->getDownNode());
    }
    if(root->getRightNode() != NULL) {
      print_tree(root->getRightNode());
    }
    if(root->getLeftNode() != NULL) {
      print_tree(root->getLeftNode());
    }
  }
};

bool dfs_helper(Node* root, int depth, stack<eight_puzzle> &dfs_stack, int &statesEnqueued) {
  if(root->getDepth() > depth) {
    return false;
  }
  if(root->goalState()) {
    statesEnqueued++;
    dfs_stack.push(root->getPuzzle());
    return true;
  }
  if(root->getLeftNode() != NULL) {
    statesEnqueued++;
    if(dfs_helper(root->getLeftNode(), depth, dfs_stack, statesEnqueued)) {
      dfs_stack.push(root->getPuzzle());
      return true;
    }
  }
  if(root->getDownNode() != NULL) {
    statesEnqueued++;
    if(dfs_helper(root->getDownNode(), depth, dfs_stack, statesEnqueued)) {
      dfs_stack.push(root->getPuzzle());
      return true;
    }
  }
  if(root->getUpNode() != NULL) {
    statesEnqueued++;
    if(dfs_helper(root->getUpNode(), depth, dfs_stack, statesEnqueued)) {
      dfs_stack.push(root->getPuzzle());
      return true;
    }
  }
  if(root->getRightNode() != NULL) {
    statesEnqueued++;
    if(dfs_helper(root->getRightNode(), depth, dfs_stack, statesEnqueued)) {
      dfs_stack.push(root->getPuzzle());
      return true;
    }
  }
  return false;
}

void dfs(Node* root, string input) {
  int moves = 0;
  stack<eight_puzzle> dfs_stack;
  cout << "Eight-Puzzle: " << input << endl;
  int statesEnqueued = 0;
  if(dfs_helper(root, 10, dfs_stack, statesEnqueued)) {
    while(!dfs_stack.empty()) {
      dfs_stack.top().print_puzzle();
      cout << endl;
      dfs_stack.pop();
      moves++;
    }
    cout << "Number of moves = " << moves-1 << endl;
    cout << "Number of states enqueued = " << statesEnqueued << endl;
  }
  else {
    cout << "Impossible to reach goal state at search tree of depth 10" << endl;
  }
}

void ids(Node* root, string input) {
  cout << "Eight-Puzzle: " << input << endl;
  for(int i = 1; i <= 10; i++) {
    stack<eight_puzzle> ret_stack;
    int moves = 0;
    int statesEnqueued = 0;
    if(dfs_helper(root, i, ret_stack, statesEnqueued)) {
      while(!ret_stack.empty()) {
	ret_stack.top().print_puzzle();
	cout << endl;
	ret_stack.pop();
	moves++;
      }
      cout << "Number of moves = " << moves-1 << endl;
      cout << "Number of states enqueued = " << statesEnqueued << endl;
      return;
    }
  }
  cout << "Impossible to reach goal state at search tree of depth 10" << endl;
}

bool astarOne_helper(Node* root, stack<eight_puzzle> &ret, int &statesEnqueued) {
  if(root->goalState()) {
    ret.push(root->getPuzzle());
    return true;
  }

  int upMisplaced, downMisplaced, rightMisplaced, leftMisplaced = 0;
  
  if(root->getUpNode() != NULL) {
    upMisplaced = root->getUpNode()->getPuzzle().numOfMisplacedTiles();
  }
  else {
    upMisplaced = 900;
  }

  if(root->getDownNode() != NULL) {
    downMisplaced = root->getDownNode()->getPuzzle().numOfMisplacedTiles();
  }
  else {
    downMisplaced = 900;
  }

  if(root->getRightNode() != NULL) {
    rightMisplaced = root->getRightNode()->getPuzzle().numOfMisplacedTiles();
  }
  else {
    rightMisplaced = 900;
  }

  if(root->getLeftNode() != NULL) {
    leftMisplaced = root->getLeftNode()->getPuzzle().numOfMisplacedTiles();
  }
  else {
    leftMisplaced = 900;
  }

  int sort[] = {upMisplaced, downMisplaced, rightMisplaced, leftMisplaced};

  for(int i = 0; i < 3; i++) {
    int minIndex = i;
    for(int j = i+1; j < 4; j++) {
      if(sort[minIndex] > sort[j]) {
	minIndex = j;
      }
    }
    
    if(minIndex != i) {
      int temp = sort[i];
      sort[i] = sort[minIndex];
      sort[minIndex] = temp;
    }
  }
  
  for(int i = 0; i < 4; i++) {
    if(sort[i] != 900) {
      if(sort[i] == upMisplaced) {
	statesEnqueued++;
	if(astarOne_helper(root->getUpNode(), ret, statesEnqueued)) {
	  ret.push(root->getPuzzle());
	  return true;
	}
      }
      if(sort[i] == downMisplaced) {
	statesEnqueued++;
	if(astarOne_helper(root->getDownNode(), ret, statesEnqueued)) {
	  ret.push(root->getPuzzle());
	  return true;
	}
      }
      if(sort[i] == rightMisplaced) {
	statesEnqueued++;
	if(astarOne_helper(root->getRightNode(), ret, statesEnqueued)) {
	  ret.push(root->getPuzzle());
	  return true;
	}
      }
      if(sort[i] == leftMisplaced) {
	statesEnqueued++;
	if(astarOne_helper(root->getLeftNode(), ret, statesEnqueued)) {
	  ret.push(root->getPuzzle());
	  return true;
	}
      }
    }
  }
  return false;
}

void astarOne(Node* root, string input) {
  //misplaced heuristic
  cout << "Eight-Puzzle: " << input << endl;
  int statesEnqueued, moves = 0;
  stack<eight_puzzle> ret;
  if(astarOne_helper(root, ret, statesEnqueued)) {
    while(!ret.empty()) {
	ret.top().print_puzzle();
	cout << endl;
	ret.pop();
	moves++;
      }
      cout << "Number of moves = " << moves-1 << endl;
      cout << "Number of states enqueued = " << statesEnqueued << endl;
  }
  else {
    cout << "Impossible to reach goal state at search tree of depth 10" << endl;
  }
}

bool astarTwo_helper(Node* root, stack<eight_puzzle> &ret, int &statesEnqueued) {
  if(root->goalState()) {
    ret.push(root->getPuzzle());
    return true;
  }

  int upMisplaced, downMisplaced, rightMisplaced, leftMisplaced = 0;
  
  if(root->getUpNode() != NULL) {
    upMisplaced = root->getUpNode()->getPuzzle().manhattanDistance();
  }
  else {
    upMisplaced = -1;
  }

  if(root->getDownNode() != NULL) {
    downMisplaced = root->getDownNode()->getPuzzle().manhattanDistance();
  }
  else {
    downMisplaced = -1;
  }

  if(root->getRightNode() != NULL) {
    rightMisplaced = root->getRightNode()->getPuzzle().manhattanDistance();
  }
  else {
    rightMisplaced = -1;
  }

  if(root->getLeftNode() != NULL) {
    leftMisplaced = root->getLeftNode()->getPuzzle().manhattanDistance();
  }
  else {
    leftMisplaced = -1;
  }

  int sort[] = {upMisplaced, downMisplaced, rightMisplaced, leftMisplaced};

  for(int i = 0; i < 3; i++) {
    int minIndex = i;
    for(int j = i+1; j < 4; j++) {
      if(sort[minIndex] > sort[j]) {
	minIndex = j;
      }
    }
    
    if(minIndex != i) {
      int temp = sort[i];
      sort[i] = sort[minIndex];
      sort[minIndex] = temp;
    }
  }
  
  for(int i = 0; i < 4; i++) {
    if(sort[i] != -1) {
      if(sort[i] == upMisplaced) {
	statesEnqueued++;
	if(astarTwo_helper(root->getUpNode(), ret, statesEnqueued)) {
	  ret.push(root->getPuzzle());
	  return true;
	}
      }
      if(sort[i] == downMisplaced) {
	statesEnqueued++;
	if(astarTwo_helper(root->getDownNode(), ret, statesEnqueued)) {
	  ret.push(root->getPuzzle());
	  return true;
	}
      }
      if(sort[i] == rightMisplaced) {
	statesEnqueued++;
	if(astarTwo_helper(root->getRightNode(), ret, statesEnqueued)) {
	  ret.push(root->getPuzzle());
	  return true;
	}
      }
      if(sort[i] == leftMisplaced) {
	statesEnqueued++;
	if(astarTwo_helper(root->getLeftNode(), ret, statesEnqueued)) {
	  ret.push(root->getPuzzle());
	  return true;
	}
      }
    }
  }
  return false;
}

void astarTwo(Node* root, string input) {
  //manhattan heuristic
  cout << "Eight-Puzzle: " << input << endl;
  int statesEnqueued, moves = 0;
  stack<eight_puzzle> ret;

  if(astarTwo_helper(root, ret, statesEnqueued)) {
    while(!ret.empty()) {
	ret.top().print_puzzle();
	cout << endl;
	ret.pop();
	moves++;
      }
      cout << "Number of moves = " << moves-1 << endl;
      cout << "Number of states enqueued = " << statesEnqueued << endl;
  }
  else {
    cout << "Impossible to reach goal state at search tree of depth 10" << endl;
  }
  return;
}

void createTree(Node* node, string prev) {
  if(node->getDepth() < 10 && !node->goalState()) {
    string upMove = node->getPuzzle().getMove("up");
    if(upMove != "" && prev != "down") {
      node->setUpNode(new Node(upMove, node->getDepth()+1));
      createTree(node->getUpNode(), "up");
    }
    string downMove = node->getPuzzle().getMove("down");
    if(downMove != "" && prev != "up") {
      node->setDownNode(new Node(downMove, node->getDepth()+1));
      createTree(node->getDownNode(), "down");
    }
    string rightMove = node->getPuzzle().getMove("right");
    if(rightMove != "" && prev != "left") {
      node->setRightNode(new Node(rightMove, node->getDepth()+1));
      createTree(node->getRightNode(), "right");
    }
    string leftMove = node->getPuzzle().getMove("left");
    if(leftMove != "" && prev != "right") {
      node->setLeftNode(new Node(leftMove, node->getDepth()+1));
      createTree(node->getLeftNode(), "left");
    }
  }
  return;
}

int main(int argc, char *argv[]) {
  fstream input;
  input.open(argv[2], ios::in);
  if(input.is_open()) {
    string str;
    while(getline(input, str)) {
      Node* root = new Node(str, 0);
      createTree(root, "");      
      if(strcmp(argv[1], "dfs") == 0) {
	dfs(root, str);
      }
      else if(strcmp(argv[1], "ids") == 0) {
	ids(root, str);
      }
      else if(strcmp(argv[1], "astar1") == 0) {
	astarOne(root, str);
      }
      else if(strcmp(argv[1], "astar2") == 0) {
	astarTwo(root, str);
      }
      cout << endl;
    }
  }
}
