#include "Algorithm/Tree.h"

void TreeNode::initialize()
{
    lchild = rchild = parent = nullptr;
    type = NONE;
    op = 0;
    value = 0.0;
    function = 0;
}

// set the TreeNode to save Function info.
// function = x denotes which function is selected.
// e.g. function = 0 means 'sin' is selected.
TreeNode::TreeNode(int x)
{
    initialize();
    type = FUNCTION;
    function = x;
}

// set the TreeNode to save Number info.
// e.g. f(x) = 2*x. 2 should be saved as real number.
TreeNode::TreeNode(double x)
{
    initialize();
    type = NUMBER;
    value = x;
}

// since we need to deal with polynomial functions like x+1
// 'x' is marked as ALGEBRA.
// +-*/^() is marked as OPERATOR.
TreeNode::TreeNode(char c)
{
    initialize();
    if (c == 'x')
        type = ALGEBRA;
    else
    {
        type = OPERATOR;
        op = c;
    }
}

TreeNode::~TreeNode()
{
    
}

// calculate the expression tree T(x) using input value x
// and store the result into ans.
bool TreeNode::calculate(double &ans, double x)
{
    ans = 0;

    if (type == NUMBER)     // T(x) = constant real value.
    {
        ans = value;
        return true;
    }
    else if (type == ALGEBRA)   // T(x) = x.
    {
        ans = x;
        return true;
    }
    else if (type == OPERATOR)
    {
        double lres = 0.0, rres = 0.0;
        // recursively calculate the value of left child and right child.
        // store the results in lres and rres respectively.
        if (lchild->calculate(lres, x) && rchild->calculate(rres,x))
        {
            switch (op)
            {
                case '+':
                    ans = lres + rres;
                    return true;
                    break;
                case '-':
                    ans = lres - rres;
                    return true;
                    break;
                case '*':
                    ans = lres * rres;
                    return true;
                    break;
                case '/':
                    ans = lres / rres;
                    return true;
                    break;
                case '^':
                    ans = pow(lres, rres);
                    return true;
                    break;
                default:
                    return false;
                    break;
            }
        }
        else
            return false;
    }
    // For example, sin(x), its expression tree is like sin at root,
    // 'x' being 'sin's left child.
    else if (type == FUNCTION)
    {
        double lres = 0.0;
        if (!lchild->calculate(lres, x))
            return false;
        switch (function)
        {
            case 0:
                ans = sin(lres);
                break;
            case 1:
                ans = cos(lres);
                break;
            case 2:
                ans = tan(lres);
                break;
            case 3:
                ans = fabs(lres);
                break;
            case 4:
                ans = pow(lres,0.5);
                break;
            case 5:
                ans = log(lres);
                break;
            case 6:
                ans = log10(lres);
                break;
            default:
                ans = 0;
                break;
        }
        return true;
    }
    return true;
}
