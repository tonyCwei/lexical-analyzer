#include <unordered_set>
#include <string>
using namespace std;

class Dictionary
{
    private:
     unordered_set<string> keywords {"while", "if", "fi", "else", "return", "put", "get", "int", "endif", "function", "int", "bool", "real",  };
    
    unordered_set<char> separators {'(', ')', '{' , '}', '[', ']', ';', '#'};
    
    unordered_set<char> operators  {'<' , '>', '+', '-', '*', '/', '=', '!'};

    /* data */
public:
      bool isKeyword(string str) {
     return (keywords.find(str) != keywords.end());
}
    bool isSep(char c) {
     return (separators.find(c) != separators.end());
}
   
      bool isOpr(char c) {
     return (operators.find(c) != operators.end());
}



    
};






// dictionary::dictionary(/* args */)
// {
// }


