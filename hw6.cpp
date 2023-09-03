//Peter de Ruiter
//CSCI 1113
//04/15/2022
//Homework 6
//This program reads cnc directions from a file and outputs what the cnc would make given those directions

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

void fillZero(bool **cnc, int rows, int cols);
void onOrOff(char letters, string &onOff);
void direction(int &dirc, char letters);
void move(int &posX, int &posY, int nums, int dir, bool **cnc, string &onOff);
void print(bool **cnc, int rows, int cols);

int main(){
  bool **cnc; //declares a 2d pointer
  string onOff = "off"; //sets the cnc laser to off
  int row = 50, col = 50, posX = 0, posY = 0, dirc = 1, num;
  char letter;
  ifstream infile;
  
  cnc = new bool *[row]; 
  //gives the 2d pointer set rows and collumns
  for (int i = 0; i < row; i++) { 
    cnc[i] = new bool [col]; 
  }
  
  fillZero(cnc, row, col);
  //calls the fillZero function
  
  infile.open("laser.txt");
  //opens the file laser.txt
  if (!infile){
    //if the file could not be found
    cout << "No file found" << endl;
  }
  
  while (infile >> letter){
    //loop that runs while there are still letters in the inputted file
    if (letter == 'D' || letter == 'U'){
      //If the letter is D or U it calls function onOrOff
      onOrOff(letter, onOff);
    }
    else if (letter == 'L' || letter == 'R'){
      //If the letter is L or R it calls fucntion direction to change the direction of the cnc
      direction(dirc, letter);
    }
    else if (letter == 'F'){
      // if the letter is F it gets the number following the letter F and calls the function move
      infile >> num;
      move(posX, posY, num, dirc, cnc, onOff);
    }
    else if (letter == 'P'){
      //if the letter is P function print is called to output what the cnc printed
      print(cnc, row, col);
    }
    else{
      
    }
  }


  infile.close(); //closes laser.txt
}


//This function fill the 2d pointer with 0
void fillZero(bool **cnc, int rows, int cols){
  for (int i = 0; i < rows; i++){
    //for each row
    for (int j = 0; j < cols; j++){
      //for each collumn
      cnc[i][j] = 0;
      //assigns zero to each position
    }
  }
}


//This function turns the CNC on and off
void onOrOff(char letters, string &onOff){
  if (letters == 'D'){
    //if the letter is D it turns the laser on
    onOff = "on";
  }
  
  else if (letters == 'U'){
    //if the letter is U it turns the laser off
    onOff = "off";
  }
  
  else{  
  }
}


//The function direction sets the direction that the cnc is moving, it is assigned a number for each of the cardinal direction 1 is east, 4 is south, 3 is west and, 2 is north
void direction(int &dirc, char letters){
  
  if (letters == 'L'){
    //if the letter is L it turns the cnc left by subtracting one from the direction
    dirc--;
    
    if (dirc < 1){
      //if the direction is less then one the it is reassigned to the number 4 because in my system 0 would be the same direction as 4
      dirc = 4;
    }
  }
  
  if (letters == 'R'){
    //if the letter is R it turns the cnc right by adding one to the direction
    dirc++;
    
    if (dirc > 4){
      //if the number direction is bigger the four it is reassigned to number 1 becuase 1 is the same direction as 5 in this system
      dirc = 1;
    }
  }
}


//This function moves the cnc and fills each location with a one if the cnc is on
void move(int &posX, int &posY, int nums, int dir, bool **cnc, string &onOff){
  
  if (dir == 1){
    //if the cnc machine is moving east
    int j = posX;
    // j is assigned the x-position of where the cnc is positoned
    for (int i = 1; i <= nums; i++){
      //runs a for loop as many psoitons the cnc has to move
      j++;
      //adds one to j count
      if (onOff == "on"){
      //if the cnc is on it changes the boolen variable stored in that location to a 1
        cnc[j][posY] = 1;
      }
    }
    posX += nums;
    //adds the amount of spaces moved to x-posisiton
  }
  
  if (dir == 2){
    //if the cnc machine is set to move north
    int k = posY;
    //k is assigned the current y-positon of the cnc
    for (int i = 1; i <= nums; i++){
      //runs a for loop as many psoitons the cnc has to move
      k++;
      //adds one to variable k
      if (onOff == "on"){
      //if the cnc is on it changes the boolen variable stored in that location to a 1
        cnc[posX][k] = 1;
      }
    }
    posY += nums;
    //add the amount of space moved to the y-postion
  }
  
  if (dir == 3){
    //if the cnc is moving is west
    int l = posX;
    //l is assigned the current x-postion of the cnc
    for (int i = 1; i <= nums; i++){
    //runs a for loop as many positions the cnc has to move
      l--;
      //subtracts one from variable l
      if (onOff == "on" && cnc[l][posY] != 1){
        //if the cnc is on it assigns the positon one
        cnc[l][posY] = 1;
      }
    }
    posX -= nums;
    //subtracts the number of positions moved from the x-postion because moving "west" on a cartesian coordinate system is moving backwards
  }
  
  if (dir == 4){
    //if the direction the cnc is moving is south
    int m = posY;
    for (int i = 1; i <= nums; i++){
    //runs a for loop as many positions the cnc has to move
      m--;
      //subtracts one from variable m
      if (onOff == "on" && cnc[posX][m] != 1){
        //if the cnc is on it sets the positon to 1
        cnc[posX][m] = 1;
      }
    }
    posY -= nums;
    //subtracts the number of positions moved from the y-postion because moving "south" on a cartesian coordinate system is moving downwards
  } 
}


//This function prints the output on the screen and outputs the result into a file
void print(bool **cnc, int rows, int cols){
  ofstream ofile;
  ofile.open("output.txt");
  //opens the file output.txt
  
  if (!ofile){
    //if the file could not be opened it returns an error message
    cout << "Could not create file" << endl;
  }
  
  for (int i = 0; i < rows; i++){
    //for rows
    for (int j = 0; j < cols; j++){
      //for collumns
      if (cnc[j][i] == 1){
        //if the number at the position is 1 it outputs a *
        cout << "*";
      }
      if (cnc [j][i] == 0){
        //if the number at the postion is a 0 it outputs a space
        cout << " ";
      }
    }
    cout << endl;
  }
  //same thing as above just outputs it into file output.txt
  for (int i = 0; i < rows; i++){
    //for rows
    for (int j = 0; j < cols; j++){
      //for collumns
      if (cnc[j][i] == 1){
        //if the number at the position is 1 it outputs a *
        ofile << "*";
      }
      if (cnc [j][i] == 0){
        //if the number at the postion is a 0 it outputs a space
        ofile << " ";
      }
    }
    ofile << endl;
  }
  ofile.close();
  //closes the file output.txt
}



