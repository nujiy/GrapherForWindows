#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
#include <cmath>

using std::string;
typedef class TreeNode* TNode;

#define FuncTotal 7
const string func[7] = {"sin","cos","tan","abs","sqrt","ln","lg"};

enum TokenType
{NUMBER, ALGEBRA,OPERATOR,FUNCTION,NONE,WRONG};

// MulDiv will cause redeclaration of function MulDiv(int,int,int) in Winbase.h
enum Priority
{ERROR,RightBracket,AddSub,MulDiv1,Pow,LeftBracket};

class TreeNode {
private:
    char op;
    double value;
    int function;
    
public:
    void initialize();
    TreeNode(double x);
    TreeNode(char c);
    TreeNode(int x);
    ~TreeNode();
    bool calculate(double& ans, double x);
    TNode lchild,rchild,parent;
    enum TokenType type;
};

#endif /* Tree_h */
