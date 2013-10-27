#include <iostream>
using namespace std;

int main(){
	int boardLayout[3][3];

	boardLayout[0][1] = 2;
	boardLayout[1][1] = 2;
	boardLayout[2][0] = 2;

	boardLayout[2][2] = 1;
	boardLayout[2][1] = 1;
	boardLayout[1][2] = 2;


	    if( (boardLayout[0][0] == 1 && boardLayout[1][0] == 1 && boardLayout[2][0] ==1) || //top
        (boardLayout[0][0] == 1 && boardLayout[0][1] == 1 && boardLayout[0][2] ==1) || //left
        (boardLayout[0][2] == 1 && boardLayout[1][2] == 1 && boardLayout[2][2] ==1) || //buttom
        (boardLayout[2][2] == 1 && boardLayout[2][1] == 1 && boardLayout[2][0] ==1) || //right
        (boardLayout[0][1] == 1 && boardLayout[1][1] == 1 && boardLayout[2][1] ==1) || //middel
        (boardLayout[1][0] == 1 && boardLayout[1][1] == 1 && boardLayout[1][2] ==1) || //middel
        (boardLayout[0][0] == 1 && boardLayout[1][1] == 1 && boardLayout[2][2] ==1) || //cross
        (boardLayout[0][2] == 1 && boardLayout[1][1] == 1 && boardLayout[2][0] ==1)    //cross
      ) cout << "Yes"<< "\n";

	    	cout << "No"<< "\n";
	return 5;

}