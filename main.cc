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

  if (inFile.is_open()) {
  char c;
  while(inFile.get(c)) {
    lexemes.push_back(c);
  }
  inFile.close();
  break;
  } else {
    cout << "No file found, please re-enter your input file name(include .txt): ";
    getline(cin, fileName);
  }
  }

  Solution mySolution;
  vector<pair<string, string>> answer;

  string lexeme;
  int curState = 1;
  bool isComment = false;

  for (int i = 0; i < lexemes.size(); i++) {
     char c = lexemes[i];
     // if [* is not closed by *], anything after [* will be ignored 
     isComment = c == '['  && lexemes[i+1] == '*' ? true : isComment;
     if (isComment) {
     isComment = c == ']' && lexemes[i-1] == '*' ? false : isComment;  
     continue;
     }
     // if Not Comment, do following
     lexeme += c;
     mySolution.Lexer(c, lexeme, curState, answer);
  }


  ofstream outFile(string("Output.txt"));
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




