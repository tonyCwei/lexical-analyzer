#include <iostream>
#include <fstream>
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
  char c;
  vector<char> lexemes;
  ifstream myFile("input.txt");
  while(myFile.get(c)) {
    lexemes.push_back(c);
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
  
  cout << "TOKEN" << "        " << "LEXEME"<< "\n";
  print(answer);
  //cout << answer[answer.size()- 1].second << "\n";

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

