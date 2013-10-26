// classes example
#include <iostream>
#include "baord.cpp"
#include <vector>
#include <stack>
using namespace std;

class ABpruning {
  //int alpha;
  //int beta;
  int inf;
  board* BoardPointer;
  board internalBoard;
  public:
    ABpruning (board *);
    ~ABpruning ();
    void pruning (int, int*, int*);
    int AlphaBeta(board, int, int, int,  int, int, int);
    void createChildrenStack (board ,stack<board> *, int);
};

ABpruning::ABpruning (board *boardObj) {
  inf = 999999999;
  //alpha = -inf;
  //beta = inf;
  BoardPointer = boardObj;
  internalBoard =  board(*BoardPointer);
}

ABpruning::~ABpruning () {

}

void ABpruning::createChildrenStack (board boardObj, stack<board> *stack, int turn) {
  int x,y;
  int moreSpaceNoBoard; 
  board internalChildBoard;
  board tempInternalChildBoard;

  tempInternalChildBoard = board(boardObj); 
  while(boardObj.NextFreeSpace(&x, &y) != 0 ){  //loop stopper aldrig for de det er det nye board der opdateres.
    internalChildBoard =  board(tempInternalChildBoard); 
    internalChildBoard.setValue(x, y, turn); 
    boardObj.setValue(x, y, turn); 
    stack->push(internalChildBoard);
  }

  
}

//int nodeType = 1 max, 2 min
int ABpruning::AlphaBeta (board boardObj, int alpha, int beta, int nodeType, int level, int maxLevel, int turn) {
  bool isLeaf = false;
  int V;
  int test;
  int nextTurn;
  stack<board> childrenStack;
  board tempBoard;

  if(boardObj.getGameStatus() != 4) isLeaf = true;
  if(level == maxLevel) isLeaf = true;


  if(nodeType == 1) cout << "max node\n";
  if(nodeType == 2) cout << "min node\n";
  boardObj.printBoard();
  cout << "Gamestatus: " << boardObj.getGameStatus() << " - alpha: " << alpha << " - beta " << beta << "\n";

  if(boardObj.getGameStatus() == 1) return inf;
  if(boardObj.getGameStatus() == 2) return -inf; 
  if(boardObj.getGameStatus() == 3) return 0;
  if(isLeaf) return boardObj.getGameValue();

  if(turn==1) nextTurn = 2;
  if(turn==2) nextTurn = 1;

  //Create Children stack
  //childrenStack.push();
  createChildrenStack(boardObj, &childrenStack, turn);
  //childrenStack.pop()
  

  if(nodeType == 1){
    //MAX node
    while(alpha <= beta && !childrenStack.empty() ){ // && children stack not empty
      V=AlphaBeta(childrenStack.top(),-inf, inf, 2, level+1, maxLevel,nextTurn);
      childrenStack.pop();
      if (V >= alpha){
        alpha = V;
      } 
    }
    return alpha;
    

  }else{
    //min node
    while(alpha <= beta && !childrenStack.empty()){ // && children stack not empty
      V=AlphaBeta(childrenStack.top(), -inf, inf, 1, level+1, maxLevel,nextTurn);
      childrenStack.pop();
      if (V <= beta){
        beta = V;
        cout << "beta" << beta << "\n";
      }
    }
    return beta;
  }
  cout << "We are returning 0 \n";
  return 0;
}

void ABpruning::pruning (int level, int *x, int *y) {
  board internalBoard =  board(*BoardPointer);
  board nextMoveBoard;

  AlphaBeta(internalBoard, -inf, inf, 1, 0, 3, 1);

}

int main () {

  board tttBoard;
  int x,y;


  ABpruning pruning(&tttBoard);

  tttBoard.setValue(0,1,2);
  tttBoard.setValue(2,2,1);
  //tttBoard.NextFreeSpace(&x, &y);

  pruning.pruning (1, &x, &y);
  //cout << "x: " << x << " - y:" << y << "\n";

  
  
  return 0;
}
