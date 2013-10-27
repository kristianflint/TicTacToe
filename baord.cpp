// Board plate
//Computer = 1
//Human = 2

#include <iostream>
#include <string>
using namespace std;

class board {
    int boardLayout[3][3];
    int boardValues[3][3];
  public:
    board ();
    ~board ();
    void setValue (int,int,int);
    void printBoard();
    int getGameValue(); 
    int getGameStatus(); //returens codes 1 = computer wins! 2 = Human wins! 3 = draw! 4 = not finish!
    int getValue(int, int);
    int NextFreeSpace(int*, int*);
};

board::board () {
  //reset the board
  for (int i=0; i<3; i++) {
    boardLayout[i][0] = 0;
    boardLayout[i][1] = 0;
    boardLayout[i][2] = 0;
  }

  boardValues[0][0] = 3;
  boardValues[0][1] = 2;
  boardValues[0][2] = 3;
    
  boardValues[1][0] = 2;
  boardValues[1][1] = 4;
  boardValues[1][2] = 2;
    
  boardValues[2][0] = 3;
  boardValues[2][1] = 2;
  boardValues[2][2] = 3;
}

board::~board () {

}

void board::setValue (int x, int y, int value) {
  if  (boardLayout[x][y] == 0) boardLayout[x][y] = value;
}

int board::getValue (int x, int y) {
  return boardLayout[x][y];
}


int board::NextFreeSpace (int *x_pointer, int *y_pointer) {
    int k= 0;

    for (int x=0; x<3; x++) {
      for (int y=0; y<3; y++) {
        if(boardLayout[x][y] == 0){
          k = 1;
          *x_pointer = x;
          *y_pointer = y;
          goto stop;
        } 
      }
    }

stop:
  if(k==1) return 1;
  else return 0;
}


void board::printBoard () {

  string printString = "";
   // cout << "|" << boardLayout[0][0] << "," << boardLayout[1][0] << "," << boardLayout[0][2] << "|\n";
   // cout << "|" << boardLayout[0][1] << "," << boardLayout[1][1] << "," << boardLayout[1][2] << "|\n";
   // cout << "|" << boardLayout[0][2] << "," << boardLayout[1][2] << "," << boardLayout[2][2] << "|\n";
    for (int x=0; x<3; x++) {
      for (int y=0; y<3; y++) {
          if (boardLayout[y][x] == 1) printString += "| x ";
          if (boardLayout[y][x] == 2) printString += "| o ";
          if (boardLayout[y][x] == 0) printString += "|   ";
      }
    printString += "|\n";
  }
  cout << " -----------\n" << printString  << " -----------\n";
}


int board::getGameValue () {
  int tempValue = 0;

    for (int x=0; x<3; x++) {
      for (int y=0; y<3; y++) {
        if(boardLayout[x][y] == 1) tempValue += boardValues[x][y];
        if(boardLayout[x][y] == 2) tempValue -= boardValues[x][y];
      }
    }
  return tempValue;
}

//Computer = 1
//Human = 2
//returens codes 1 = computer wins! 2 = Human wins! 3 = draw! 4 = not finish!
int board::getGameStatus () {
  int draw = 0;
    //Computer wins
    if( (boardLayout[0][0] == 1 && boardLayout[1][0] == 1 && boardLayout[2][0] ==1) || //top
        (boardLayout[0][0] == 1 && boardLayout[0][1] == 1 && boardLayout[0][2] ==1) || //left
        (boardLayout[0][2] == 1 && boardLayout[1][2] == 1 && boardLayout[2][2] ==1) || //buttom
        (boardLayout[2][2] == 1 && boardLayout[2][1] == 1 && boardLayout[2][0] ==1) || //right
        (boardLayout[0][1] == 1 && boardLayout[1][1] == 1 && boardLayout[2][1] ==1) || //middel
        (boardLayout[1][0] == 1 && boardLayout[1][1] == 1 && boardLayout[1][2] ==1) || //middel
        (boardLayout[0][0] == 1 && boardLayout[1][1] == 1 && boardLayout[2][2] ==1) || //cross
        (boardLayout[0][2] == 1 && boardLayout[1][1] == 1 && boardLayout[2][0] ==1)    //cross
      ) return  1;

    //Human wins
    if( (boardLayout[0][0] == 2 && boardLayout[1][0] == 2 && boardLayout[2][0] ==2) || //top
        (boardLayout[0][0] == 2 && boardLayout[0][1] == 2 && boardLayout[0][2] ==2) || //left
        (boardLayout[0][2] == 2 && boardLayout[1][2] == 2 && boardLayout[2][2] ==2) || //buttom
        (boardLayout[2][2] == 2 && boardLayout[2][1] == 2 && boardLayout[2][0] ==2) || //right
        (boardLayout[0][1] == 2 && boardLayout[1][1] == 2 && boardLayout[2][1] ==2) || //middel
        (boardLayout[1][0] == 2 && boardLayout[1][1] == 2 && boardLayout[1][2] ==2) || //middel
        (boardLayout[0][0] == 2 && boardLayout[1][1] == 2 && boardLayout[2][2] ==2) || //cross
        (boardLayout[0][2] == 2 && boardLayout[1][1] == 2 && boardLayout[2][0] ==2)    //cross
      ) return  2;

      for (int x=0; x<3; x++) {
        for (int y=0; y<3; y++) {
            if (boardLayout[x][y] == 0) draw += 1;
        }
      }
      if( draw == 0 ) return 3;


    return 4;
}

