#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>
#include <string>
#include "Solution.h"
using namespace std;


int main() {
  vector<char> lexemes;
  string fileName;
  cout << "Please enter your input file name(include .txt): ";
  getline(cin, fileName);
  while (true) {
  ifstream inFile(fileName);

  if (inFile.is_open()) {//open file
  char c;
  while(inFile.get(c)) {//while the file can pull a character, load to variable c
    lexemes.push_back(c);//in the vector lexemes, push back the character into its own slot
  }
  inFile.close();//close file after the entire file has been read
  break;//break the true loop
  } else {
    cout << "No file found, please re-enter your input file name(include .txt): ";
    getline(cin, fileName);// if the initial file name cannot be found, repeat input
  }
  }

  Solution mySolution;
  vector<pair<string, string>> answer;//hefty paired vector

  string lexeme;
  int curState = 1;
  bool isComment = false;

  for (int i = 0; i < lexemes.size(); i++)//for the size of the vector
  {
     char c = lexemes[i];//the char of c is equal to the variables position in lexemes
     // if [* is not closed by *], anything after [* will be ignored 
     isComment = c == '['  && lexemes[i+1] == '*' ? true : isComment;//defining of a commment in the lexeme operator
     if (isComment) {
     isComment = c == ']' && lexemes[i-1] == '*' ? false : isComment;  //ignore if either req is not found.
     continue;
     }
     // if Not Comment, do following
     lexeme += c;//add character to the string lexeme
     mySolution.Lexer(c, lexeme, curState, answer);//adding the character, string, current state, and the paired vector to the class
  }


  ofstream outFile(string("Output.txt"));//output file to .txt file
  if (outFile.is_open()) {       
  outFile << "TOKEN" << "              " << "LEXEME"<< "\n";
  outFile << "----------------------------------"<< "\n";
  for (pair<string, string> kvpair : answer) {
    outFile << kvpair.first << "           " << kvpair.second << "\n";
  }
    outFile.close();
    cout << "Output.txt file has been generated under the same folder";
  } else {
    cout << "Error, Output.txt file was not generated";
  }
  cin.get();
  return 0;
}




