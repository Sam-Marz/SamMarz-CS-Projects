/* Name: Samuel Marzban
Date: 12/6/2023
Section: 13
Assignment: 5
Due Date: 12/8/2023
About this project: Write a C++ program to simulate a game similar to the snake game. You have a rectangular “field”,
with a wall around it and obstacles at certain spots. There is one opening in the wall through which the
snake enters the field. The snake is infinitely long. The snake makes turns according to input and the
game ends when the snake runs into itself. Print an orthographic map (viewed from above) of the field
when the game ends
Assumptions: You may assume that the first turn will work with the location of the gate. That is, if the gate
is on the Eastern wall, the first turn’s direction will be ‘L’. You may also assume the gate will
never be at the corner, and the obstacles will not block entry into the field

All work below was performed by Samuel Marzban */


#include <iostream>

using namespace std;

char** createField(int , int);
void playGame(char**, int, int);

int main(){
    cout<<"Enter the number of rows: "; int row; cin>>row; // row prompt
    cout<<"Enter the number of columns: "; int col; cin>>col;  //col prompt
    char** field= createField(row,col); // initlize field for game
    playGame(field, row, col);
    // deallocation of memory
    for(int i =0; i<row; i++){
        delete [] field[i];
    }
    delete [] field;

    return 0;
}

char** createField(int length, int width){ // char pointer to a pointer return value to return 2d array
    char** field = new char*[length]; // create field of pointer to char array
    for(int i=0; i<length; i++){
        field[i] = new char[width]; // feild row set = to char array
        for(int j=0; j<width; j++){
            if(i==length-1 || i==0 || j==0 || j==width-1) // if border of field set = to w
                field[i][j]='W'; // set wall
            else 
                field[i][j]='.'; // else set = to .
        }
    }

    cout<<"Enter the number of obstacles: "; int n; cin>>n; // prompt for number of obstacles
    cout<<"Enter the locations of the obstacles:\n"; // prompt for obstacle location
    char dummy; int row,col; // dummy char for ','
    for(int i=0; i<n; i++){ // read in positions
        cin>>row>>dummy>>col;
        field[row][col]='O';
    }
    return field; // return field
}

void playGame(char** field, int rowF, int colF){
    char dummy; // the ','
    cout<<"Enter the location of the gate: "; int row, col; cin>>row>>dummy>>col; // prompt for gate position
    field[row][col]='G';

    cout<<"Enter the number of turns: "; int turns; cin>>turns; // prompts for turns
    cout<<"Enter the turns:\n";
    char* move= new char[turns]; //move storage
    int* spc=new int[turns]; // number of moves
    bool over=false; // game over condition

    for(int i=0; i<turns; i++){
        cin>>move[i]; // read in move and number of moves
        cin.ignore(); 
        cin>>spc[i]; 
    }

    int i=0; while(!over && i<turns){ // run until turns reach or game over
        switch(move[i]){
            case 'D':
                while(spc[i]>0){ // while you have moves...
                    if(field[row+1][col]!='O' && field[row+1][col]!='S'){ // if snake runs into obstacle or itself game over if not it continues to move DOWN
                        row++; // row+1 to move down
                        field[row][col]='S';
                        spc[i]--;// 1 less move
                    }
                    else{
                        spc[i]=0; // ends moves 
                        over=true; // ends turn while if over=true
                    }
                }
                break;
            case 'U':
                while(spc[i]>0){ // while you have moves...
                    if(field[row-1][col]!='O' && field[row-1][col]!='S'){ // if snake runs into obstacle or itself game over if not it continues to move UP
                        row--; // row-1 to move up
                        field[row][col]='S';
                        spc[i]--; // 1 less move
                    }
                    else{
                        spc[i]=0; // ends moves 
                        over=true; // ends turn while if over=true
                    }
                }
                break;
            case 'L':
                while(spc[i]>0){ // while you have moves...
                    if(field[row][col-1]!='O' && field[row][col-1]!='S'){ // if snake runs into obstacle or itself game over if not it continues to move LEFT
                        col--; // col-1 to move left
                        field[row][col]='S';
                        spc[i]--; // 1 less move
                    }
                    else{
                        spc[i]=0; // ends moves 
                        over=true; // ends turn while if over=true
                    }
                }
                break;
            case 'R':
                while(spc[i]>0){ // while you have moves...
                    if(field[row][col+1]!='O' && field[row][col+1]!='S'){ // if snake runs into obstacle or itself game over if not it continues to move RIGHT
                        col++; // col+1 to move right
                        field[row][col]='S'; 
                        spc[i]--; // 1 less move
                    }
                    else{
                        spc[i]=0; // ends moves 
                        over=true; // ends turn while if over=true
                    }
                }
                break;
        }
        i++; // one less turn
    }

    for(int i=0; i<rowF; i++){ // print field after game
        for(int j=0; j<colF; j++){
            cout<<field[i][j];
        }
        cout<<"\n";
    }
    delete [] move; // dealloacte memory
    delete [] spc;
}

