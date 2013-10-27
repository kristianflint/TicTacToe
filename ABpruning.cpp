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
  board nextMoveBoard;
  public:
    ABpruning (board *);
    ~ABpruning ();
    void pruning (int, int*, int*);
    int AlphaBeta(board, int, int, int,  int, int, int);
    void createChildrenStack (board ,stack<board> *, int);
    board getNextMoveBoard();
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

board ABpruning::getNextMoveBoard () {
    return nextMoveBoard;
}

void ABpruning::createChildrenStack (board boardObj, stack<board> *stack, int turn) {
  int x,y;
  int moreSpaceNoBoard; 
  board internalChildBoard;
  board tempInternalChildBoard;

  tempInternalChildBoard = board(boardObj); 
  while(boardObj.NextFreeSpace(&x, &y) != 0 ){  
    internalChildBoard =  board(tempInternalChildBoard); 
    internalChildBoard.setValue(x, y, turn); 
    boardObj.setValue(x, y, turn); 
    stack->push(internalChildBoard);
  }

  
}

//int nodeType = 1 max, 2 min
int ABpruning::AlphaBeta (board boardObj, int alphaSEND, int betaSEND, int nodeType, int level, int maxLevel, int turn) {
  bool isLeaf = false;
  int V=0;
  int test;
  int nextTurn;
  int alpha = alphaSEND;
  int beta = betaSEND;
  stack<board> childrenStack;
  board tempBoard;

  //cout << "Gamestatus: " << boardObj.getGameStatus() << "\n";
  //boardObj.printBoard();

  if(boardObj.getGameStatus() != 4) isLeaf = true;
  if(level == maxLevel) isLeaf = true;


  //if(nodeType == 1) cout << "max node\n";
  //if(nodeType == 2) cout << "min node\n";

/*
  if(nodeType == 1) cout << "max node level "<< level << " getGameValue " << boardObj.getGameValue() << " getGameStatus " << boardObj.getGameStatus()  << " alpha: " << alpha << " - beta " << beta << "\n";
  if(nodeType == 2) cout << "min node level "<< level << " getGameValue " << boardObj.getGameValue() <<" getGameStatus " << boardObj.getGameStatus()  << " alpha: " << alpha << " - beta " << beta << "\n";
  boardObj.printBoard();
*/
  //cout << "Gamestatus: " << boardObj.getGameStatus() << " - alpha: " << alpha << " - beta " << beta << "\n";

  if(boardObj.getGameStatus() == 1) return inf;
  if(boardObj.getGameStatus() == 2) return -inf; 
  if(boardObj.getGameStatus() == 3) return 0;
  if(isLeaf) {
   
   //cout << "getGameValue: " << boardObj.getGameValue()  << " getGameStatus: " << boardObj.getGameStatus()  << "\n";
   //boardObj.printBoard();
   return boardObj.getGameValue();
  }


  //Skifter turen til næste level
  if(turn==1) nextTurn = 2;
  if(turn==2) nextTurn = 1;

  createChildrenStack(boardObj, &childrenStack, turn);

  if(nodeType == 1){
    //MAX node
    while(alpha < beta && !childrenStack.empty()){ // && children stack not empty
      if  (childrenStack.empty()) break;
      V=AlphaBeta(childrenStack.top(), alpha, beta, 2, level+1, maxLevel,  nextTurn);
      tempBoard = childrenStack.top();
      childrenStack.pop();
      if (V > alpha){
        alpha = V;
        if(level == 0 ) {
          nextMoveBoard = board(tempBoard);
        }
      } 
    }
    return alpha;
    

  }else{
    //min node
    while(alpha < beta){ // && children stack not empty
      if  (childrenStack.empty()) break;
      V=AlphaBeta(childrenStack.top(), alpha, beta, 1, level+1, maxLevel, nextTurn);
      childrenStack.pop();
      if (V < beta){
        beta = V;
      }
    }
    return beta;
  }
  cout << "We are returning 0 \n";
  return 0;
}

void ABpruning::pruning (int level, int *x, int *y) {
  board internalBoard =  board(*BoardPointer);
  

  AlphaBeta(internalBoard, -inf, inf, 1, 0, 1, 1);

}

int main () {

  board tttBoard;
  int x,y;
  int hX, hY;


 


  while(tttBoard.getGameStatus() == 4){
      ABpruning pruning(&tttBoard);
      pruning.pruning (1, &x, &y);
      tttBoard = pruning.getNextMoveBoard();
      tttBoard.printBoard();
      if (tttBoard.getGameStatus() == 4){
        cout << "Your turn\n";
        cin >> hX >> hY;
        while(tttBoard.getValue(hX,hY) != 0 ){
          cout << "Place taken\n";
          cin >> hX >> hY;
        }
        tttBoard.setValue(hX, hY ,2);
      }
  }
  
  switch (tttBoard.getGameStatus())
  {
  case 1: cout << "COMPUTER WON!!\n";
      break;
  case 2: cout << "YOU WON!!\n";
      break;
  case 3: cout << "DRAW!!\n";
      break;
  default: cout << "What tha fuck!?\n";
      break;
  }
  
/*
  //human
  tttBoard.setValue(1,1,2);
  tttBoard.setValue(2,0,2);
  tttBoard.setValue(1,2,2);

  //computer
  tttBoard.setValue(0,2,1);
  tttBoard.setValue(2,2,1);
  //tttBoard.setValue(2,1,1);

  
  //tttBoard.NextFreeSpace(&x, &y);

  cout << "initial board\n";
  tttBoard.printBoard();
  pruning.pruning (1, &x, &y);
  tttBoard = board(pruning.getNextMoveBoard());
  cout << "new board\n";
  tttBoard.printBoard();
  //cout << "x: " << x << " - y:" << y << "\n";
*/
  
  
  return 0;
}
