#include <map>
#include <vector>
#include <cctype>
using namespace std;



class Solution
{
private:

//                 |   L     D     .
// q0 =         1  |   2     3     4
// ids =        2  |   2     2     5
// int =        3  |   5     3     4
// real =       4  |   5     4     5
// nonToken =   5  |   5     5     5



   map<int, vector<int>> DFSM = {
    {1, {2, 3, 4}},
    {2, {2, 2, 5}},
    {3, {5, 3, 4}},
    {4, {5, 4, 5}},
    {5, {5, 5, 5}}
   };



    /* data */
public:
  

  //curState start as 1
  int lexer(char c, int curState) {
    int newState = curState;
    if (isalpha(c)) {
        newState = DFSM[curState][0];
    } else if (isdigit(c)) {
        newState = DFSM[curState][1];
    } else if (c == '.') {
        newState = DFSM[curState][2];
    }
    return newState;

  }




};







