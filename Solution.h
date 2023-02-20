#include <map>
#include <vector>
#include <cctype>
using namespace std;



class Solution
{
private:

//                 |   L     D     .
// q0 =         1  |   2     3     4
// ids =        2  |   2     2     6
// int =        3  |   6     3     4
// maybe real = 4  |   6     5     6
// real =       5  |   6     4     6
// nonToken =   6  |   6     6     6



   map<int, vector<int>> DFSM = {
    {1, {2, 3, 4}},
    {2, {2, 2, 6}},
    {3, {6, 3, 4}},
    {4, {6, 5, 6}},
    {5, {6, 4, 6}},
    {6, {6, 6, 6}}
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







