#ifndef Lexer_hpp
#define Lexer_hpp

#include "Tree.h"
#include <string>
#include <stack>

using std::string;

class Lexer
{
private:
    string S;
    int position;
    std::stack<char> op;
    std::stack<TNode> val;
    
    void drop(TNode node);
    int priority(char c);
    
public:
    Lexer();
    Lexer(string str);
    ~Lexer();
    void setstring(string str);
    enum TokenType token_identify();
    char get_operation();
    double get_number();
    int get_function();
    bool string_to_tree();
    string getstring();
    double calculate(double x);
    TNode root;
};

#endif /* Lexer_hpp */
