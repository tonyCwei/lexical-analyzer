#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>
#include <string>
#include "Dictionary.h"
#include "Solution.h"
using namespace std;

void print(vector<pair<string, string>> answer) {
  if (answer.empty()) {cout << "empty" << "\n";}
  for (pair<string, string> kvpair : answer) {
    cout << kvpair.first << "         " << kvpair.second << "\n";
  }
}

int main() {
  vector<char> lexemes;
  string fileName;
  cout << "Please enter your input file name(include .txt): ";
  cin >> fileName;
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
    cin >> fileName;
  }
  }


  Dictionary myDict; 
  Solution mySolution;
  vector<pair<string, string>> answer;
  
string word;
int curState = 1;
 for (int i = 0; i < lexemes.size(); i++) {
  
  char c = lexemes[i];
  //cout<< c << "\n";
  bool isTerm = c == ' ' || c == '\n' || myDict.isOpr(c) || myDict.isSep(c);
  
  if (!isTerm) {
    word += c;   
    curState = mySolution.lexer(c,curState);
  } else {        
    switch(curState) {
        case 1:
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
        // real
        answer.push_back(make_pair("REAL", word));
        break;

        case 5:
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
  
  // cout << "TOKEN" << "        " << "LEXEME"<< "\n";
  // print(answer);


  ofstream outFile(string("Output.txt"));
  if (outFile.is_open()) {
        
  outFile << "TOKEN" << "           " << "LEXEME"<< "\n";
  for (pair<string, string> kvpair : answer) {
    outFile << kvpair.first << "           " << kvpair.second << "\n";
  }
    outFile.close();
  }
  cout << "Output.txt has been generated";
  return 0;
}


// int main() {
//   string myWord;
//   string finalRead;
//   ifstream myFile("input.txt");
//   Dictionary myDict; 
//   vector<pair<string, string>> answer;
//   vector<string> lexemes;
 
//   while(myFile >> myWord) {  
//     string lexeme; 
//     bool isComment=false;
//     for (int i = 0; i < myWord.size(); i++) {
//     char c = myWord[i];   
//     if ((!myDict.isSep(c) && !myDict.isOpr(c)) && (isalpha(c) || isdigit(c)) ) {
//       lexeme.push_back(c);
//     }  
//     if (myDict.isSep(c) || myDict.isOpr(c)) {
//       if(lexeme != "") {
//         lexemes.push_back(lexeme);
//         lexeme = "";
//         }
//       string sepop = string(1,c);
//       lexemes.push_back(sepop);
//     } else if (i == myWord.size() - 1){
//       lexemes.push_back(lexeme);
//     }
//   }  
//   }
  
//   for (string word : lexemes) {
//     cout << word << "\n";
//   }

//   return 0;
// }

