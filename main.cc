#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>
#include <string>
#include "Dictionary.h"
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


  Dictionary myDict; 
  Solution mySolution;
  vector<pair<string, string>> answer;
  

string word;
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
  bool isTerm = c == ' ' || c == '\n' || myDict.isOpr(c) || myDict.isSep(c);
  if (!isTerm) {
    word += c;   
    curState = mySolution.lexer(c,curState);
  } else {        
    switch(curState) {
        case 1:
        // nothing happens, state 1 is q0
        break;

        case 2:
         // id
         if (myDict.isKeyword(word)) {
          answer.push_back(make_pair("KEYWORD", word));
         } else {
         answer.push_back(make_pair("IDENTIFIER", word)); 
         }
        break;

        case 3:
          // int
          answer.push_back(make_pair("INTEGAR", word));
        break;

        case 4:
        // possible start of a read
        answer.push_back(make_pair("NON-TOKEN", word)); 
        break;

        case 5:
        //real
        answer.push_back(make_pair("REAL", word));
        break;

        case 6:
        //non-token
        answer.push_back(make_pair("NON-TOKEN", word)); 
        break;
    }
      
      if (myDict.isOpr(c)) {
            answer.push_back(make_pair("OPERATOR", string(1,c)));
      } else if (myDict.isSep(c)) {
            answer.push_back(make_pair("SEPARETOR", string(1,c)));
      }
     curState = 1;
     word = "";
  }
 }
  

  ofstream outFile(string("Output.txt"));
  if (outFile.is_open()) {       
  outFile << "TOKEN" << "           " << "LEXEME"<< "\n";
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




