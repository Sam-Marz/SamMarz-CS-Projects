/* Name: Samuel Marzban
Date: 12/6/2023
Section: 13
Assignment: 5
Due Date: 12/8/2023
About this project: You are the Dungeon Master(DM) for a great DnD campaign. However, you’ve had a very busy week,
and you don’t have a story prepared for this weekend’s session. You decide to wing it with a Free for All
combat, where the party decides to fight each other to see who comes out on top. To make things easier,
you decide to write a program to basically let the session run itself. 
Assumptions: n/a

All work below was performed by Samuel Marzban */

#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

struct Move{
    char name[50];
    int damage;
};

struct character{
    char name[50], char_Class[50], moveName[50];
    int hitPoints, armorClass;
    bool isAlive;
};

void sort(character*, int, char);

int main(){
    char sortBy ='n'; // what to sort by n=name h=hitpoint
    ifstream charFile, sessFile; // create location to open files
    charFile.open("characters.txt");  // open both files
    sessFile.open("session.txt");

    int m; charFile>>m; // read in amount of moves
    charFile.ignore(); // ignore new line after int

    Move* moves = new Move[m]; // dynammic array of moves
    for(int i=0; i<m; i++){ // read in moves
        charFile.getline(moves[i].name,50,'\t');
        charFile>>moves[i].damage;
        charFile.ignore(); // ingnore new line after int
    }

    int k; charFile>>k; // read in amount of characters
    character* chars = new character[k]; // dyanmic array of characters
    charFile.ignore(); // ignore new line after int

    for(int i=0; i<k; i++){  // intilizes bool isAlive to true
        chars[i].isAlive=true;
    }

    for(int i=0; i<k; i++){ // read in contents of characters 
        charFile.getline(chars[i].name, 50,'\t');
        charFile.getline(chars[i].char_Class, 50, '\t');
        charFile>>chars[i].hitPoints;
        charFile>>chars[i].armorClass;
        charFile.ignore(); // ignore tab after int
        charFile.getline(chars[i].moveName, 50);
    }

    int numAtt; sessFile>>numAtt; // create dynamic arrays for each attack aspect
    sessFile.ignore(); // ignore new line after int
    char** charAtt = new char*[numAtt];
    char** moveName = new char*[numAtt];
    char** target = new char*[numAtt];
    int* roll = new int[numAtt];

    // read in contents of sessFile and plays game
    int j,g,q;
    for(int i=0; i<numAtt; i++){
        charAtt[i] = new char[50];
        sessFile.getline(charAtt[i],50,'\t');
        moveName[i] = new char[50];
        sessFile.getline(moveName[i],50,'\t');
        target[i] = new char[50];
        sessFile.getline(target[i],50,'\t');
        sessFile>>roll[i];
        sessFile.ignore();

        bool found = false;
        j=0; while(j<k && !found){ // loops through characters to find matching character 
            if(strcmp(charAtt[i],chars[j].name)==0)
                found=true;
            else
                j++;
        }

        found = false;
        g=0; while(g<k && !found){ // loops through characters to find matching target
            if(strcmp(target[i],chars[g].name)==0)
                found = true;
            else
                g++;
        }

        found = false;
        q=0; while(q<m && !found){ // loops through moves to find matching move of attacking character
            if(strcmp(moveName[i],moves[q].name)==0)
                found = true;
            else
                q++;
        }

        if(!found)q=0; // just works with this ¯\_ (ツ)_/¯

        if(strcmp(moveName[i],chars[j].moveName)==0 && roll[i]>chars[g].armorClass-1){ // condition to see if u can make a move
            chars[g].hitPoints-=moves[q].damage; // subtracts move damage from target hitpoint
            if(chars[g].hitPoints<0) // checks if target is still alive
                chars[g].isAlive=false;
        }    
    }

    sort(chars, k,sortBy); // sort characters
        
    ofstream newFile("alive.txt"); // create new file named "alive.txt" and output alive info onto txt 
    for(int i=0; i<k; i++){
        if(chars[i].isAlive){
            newFile<<chars[i].name<<"\t"<<chars[i].hitPoints<<"\n";
        }
    }

    charFile.close();  // close all files
    sessFile.close();
    newFile.close();

    // deallocate memory 
    for(int i=0; i<numAtt; i++){
        delete [] charAtt[i];
        delete [] moveName[i];
        delete [] target[i];
    }

    delete [] charAtt;
    delete [] moveName;
    delete [] target;
    delete [] roll;
    delete [] moves;
    delete [] chars;

    return 0;
}

void sort(character* chars, int num, char sort){ // selection sort algorithim given
    if(sort=='n'){
        for(int i=1; i<num; i++){
            character x = chars[i];
            int j= i-1;
            while(j>-1 && strcmp(chars[j].name,x.name)>0){
                    chars[j+1]=chars[j];
                    j--;

            }
            chars[j+1]=x;
        }
    }
    else if('h'){
        for(int i=0; i<num; i++){
            character x = chars[i];
            int j= i-1;
            while(j>-1 && x.hitPoints>chars[j].hitPoints){
                    chars[j+1]=chars[j];
                    j--;

            }
            chars[j+1]=x;
        }
    }
}