#include <unordered_map>
#include <vector>
#include <cctype>
#include <string>
#include "Dictionary.h"
using namespace std;



class Solution
{
private:
   Dictionary myDict; 

//                 |   L     D    .
// q0 =         1  |   2     5    5 
// Accept  =    2  |   3     4    5 
// Accept  =    3  |   3     4    5
// Accept  =    4  |   3     4    5
// Nontoken=    5  |   5     5    5 
   unordered_map<int, vector<int>> idDFSM = //every initial state within the dfsm and its following state depending on the order pushed in.
   {
    {1, {2, 5, 5}},
    {2, {3, 4, 5}},
    {3, {3, 4, 5}},
    {4, {3, 4, 5}},
    {5, {5, 5, 5}},
   };




//                 |   D     .    L
// q0 =         1  |   2     3    7 
// int     =    2  |   2     4    7 
// NonToken=    3  |   5     7    7
// NonToken=    4  |   6     7    7
// Real    =    5  |   5     7    7
// Real    =    6  |   6     7    7
// NonToken=    7  |   7     7    7 
   unordered_map<int, vector<int>> numDFSM = {
    {1, {2, 3, 7}},
    {2, {2, 4, 7}},
    {3, {5, 7, 7}},
    {4, {6, 7, 7}},
    {5, {5, 7, 7}},
    {6, {6, 7, 7}},
    {7, {7, 7, 7}}
   };





public:
   void addSepOpr(char c, vector<pair<string, string>> &answer) {
      if (myDict.isOpr(c)) {
            answer.push_back(make_pair("OPERATOR", string(1,c)));
      } else if (myDict.isSep(c)) {
            answer.push_back(make_pair("SEPARETOR", string(1,c)));
      }
   }

   void idLexer(char c, int &curState) {
     if (isalpha(c)) {
        curState = idDFSM[curState][0];
       } else if (isdigit(c)) {
        curState = idDFSM[curState][1];
       } else if (c == '.') {
        curState = idDFSM[curState][2];
       }
   }

   void idHandler(char c, string &lexeme, int &curState, vector<pair<string, string>> &answer) {
      lexeme.pop_back();
      switch(curState) {
        case 1:
         //nothing happens, state 1 is q0
        break;

        case 2:
        case 3:
        case 4:
         // id
         if (myDict.isKeyword(lexeme)) {
          answer.push_back(make_pair("KEYWORD", lexeme));
         } else {
         answer.push_back(make_pair("IDENTIFIER", lexeme)); 
         }
        break;

        case 5:
        answer.push_back(make_pair("NON-TOKEN", lexeme)); 
        break;
      } 
   }


    void numLexer(char c, int &curState) {
     if (isalpha(c)) {
        curState = numDFSM[curState][2];
       } else if (isdigit(c)) {
        curState = numDFSM[curState][0];
       } else if (c == '.') {
        curState = numDFSM[curState][1];
       }
   }

   void numHandler(char c, string &lexeme, int &curState, vector<pair<string, string>> &answer) {
      lexeme.pop_back();
      switch(curState) {
        case 1:
         //nothing happens, state 1 is q0
        break;

        case 2:
        //int
        answer.push_back(make_pair("INTEGAR", lexeme));
        break;

        case 5:
        case 6:
         //real
        answer.push_back(make_pair("Real", lexeme));
        break;

        case 3:
        case 4:
        case 7:
        answer.push_back(make_pair("NON-TOKEN", lexeme)); 
        break;
      } 
   }

  
  
  void Lexer(char c, string &lexeme, int &curState, vector<pair<string, string>> &answer)//input from the main.cc
  
  {
    bool isTerm = c == ' ' || c == '\n' || myDict.isOpr(c) || myDict.isSep(c);//bool c is equal to three cases, either a space, an end line, or is equaled to
    // a term provided by the dictionary
    bool potentialId = isalpha(lexeme[0]); // check is the position in the string lexeme is a alphabetic letter
    bool potentialNum = isdigit(lexeme[0]) || lexeme[0] == '.'; //boolean check to see if the character is either a number or a '.'
    
    if (!isTerm) {        // instructions if the character is a defined term
       if (potentialId) {// but is a alphabetic character
       idLexer(c, curState);//call function to find what state the machine is in
       }
       
       if(potentialNum)//if it is a number, what state is given in our lexer {
        numLexer(c, curState);
       }

    } else {//otherwise
      if (potentialId)//check if it is a potential alphabetic id {
        idHandler(c, lexeme, curState, answer);//check function
      }

      if (potentialNum)//or if potention number {
        numHandler(c, lexeme, curState, answer);//check the number handler
      }
     addSepOpr(c, answer);//add the c and changed answer to the seperator/operator function
     curState = 1;
     lexeme = "";//the string of lexeme at current position is wiped.
     }
  }
};







