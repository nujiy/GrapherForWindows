#include "Algorithm/Lexer.h"

Lexer::Lexer()
{
    position = 0;
    root = nullptr;
}

Lexer::Lexer(string str)
{
    position = 0;
    S = str;
    root = nullptr;
}

Lexer::~Lexer()
{
    drop(root);
}

// recursively delete specified node
// and its descendants.
void Lexer::drop(TNode node)
{
    if (root==nullptr)
        return;
    drop(root->lchild);
    drop(root->rchild);
    delete node;
    node = nullptr;
}

// update the string we want to do lexical analysis.
// set the position to the start of string (0)
void Lexer::setstring(string str)
{
    S = str;
    position = 0;
}

enum TokenType Lexer::token_identify()
{
    // do not reach the end of string.
    while(position < S.length())
    {
        // ignore and skip meaningless character.
        if (S[position] == ' ' || S[position] == '\n')
            position++;
        // number is encountered.
        if (S[position] >= '0' && S[position] <= '9' )
        {
            // point is used to specify whether a decimal point is encountered.
            bool point = false;
            for (int i = position; i < S.length(); i++)
            {
                // unexpected input (e.g. 1.2.344 is not a number)
                if (S[i]=='.' && point == true)
                    return WRONG;
                else if (S[i]=='.') point = true;
                if ((S[i] > '9' || S[i] < '0') && S[i] != '.')
                    break;
            }
            return NUMBER;
        }
        else
        {
            // polynomial functions.
            if (S[position] == 'x')
                return ALGEBRA;
            // test matching of string and FuncType.
            for (int i=0; i < FuncTotal; i++)
            {
                if(!S.compare(position,func[i].length(),func[i]))
                    return FUNCTION;
            }
            // match character with operator type.
            if (S[position]=='+'||S[position]=='-'||S[position]=='*'||S[position]=='/'||
                S[position]=='^'||S[position]=='('||S[position]==')')
                return OPERATOR;
            return WRONG;
        }
    }
    
    return NONE;
}

char Lexer::get_operation()
{
    return S[position++];
}

// transform string to double.
double Lexer::get_number()
{
    double ans = 0;
    int pos = 0;
    bool point = false;
    while (position < S.length())
    {
        if (S[position] >= '0' && S[position] <= '9')
        {
            ans = ans*10 + S[position] - '0';
            if(point==true)
                pos++;
        }
        else if (S[position] == '.' && point == false)
            point = true;
        else
            break;
        
        position++;
    }
    
    ans = ans / pow(10,pos);
    return ans;
}

int Lexer::get_function()
{
    for (int i=0; i<FuncTotal; i++)
    {
        if (!S.compare(position, func[i].length(), func[i]))
        {
            position += func[i].length();
            return i;
        }
    }
    return 0;
}

string Lexer::getstring()
{
    return S;
}

// return the corresponding priority of the operator.
// priority order is defined in enum Priority.
int Lexer::priority(char c)
{
    switch (c)
    {
        case '+': return AddSub;
        case '-': return AddSub;
        case '*': return MulDiv;
        case '/': return MulDiv;
        case '^': return Pow;
        case '(': return LeftBracket;
        case ')': return RightBracket;
        default: return ERROR;
    }
}

// string_to_tree() is the core of Lexer.
// To transfer a string into tree, we use the method that transfer an
// inorder expression into postorder expression, as soon as we get a
// postorder expression, transfer it directly to an expression tree.
// reference: Data Structure And Algorithm Analysis in C, second edition,
//            chinese version, P54~
bool Lexer::string_to_tree()
{
    drop(root);
    root = nullptr;
    if (S.length() == 0)
        return false;
    // last is used to check whether the function expression is valid.
    // it records the last token we met.
    enum TokenType last = NONE;
    while (position < S.length())
    {
        if (token_identify() == NUMBER)
        {
            // since two numbers (f(x) = 233.1234.6) or one number one algebra (3x)
            // or one number one function (2sin(x)) are unexpected, return false.
            // acceptable form should be like: 233.1*234.6, 3*x, 2*sin(x).
            if (last==NUMBER||last==ALGEBRA||last==FUNCTION)
                return false;
            last = NUMBER;
            val.push(new TreeNode (get_number())); // position ++ is included in get_number()
        }
        else if (token_identify()==ALGEBRA)
        {
            if (last==NUMBER||last==ALGEBRA||last==FUNCTION)
                return false;
            last = ALGEBRA;
            val.push(new TreeNode('x'));
            position++;
        }
        else if (token_identify()==FUNCTION)
        {
            if (last==NUMBER||last==ALGEBRA||last==FUNCTION)
                return false;
            last = FUNCTION;
            val.push(new TreeNode (get_function()));
        }
        else if (token_identify()==OPERATOR)
        {
            // when the first character in string is '-'.
            // f(x) = -g(x) == f(x) = 0.00 - g(x)
            if (op.empty() && val.empty() && S[position]=='-')
            {
                val.push(new TreeNode(0.0));
                op.push(S[position++]);
            }
            else if (op.empty())    // if operator stack is empty, simply push.
                op.push(S[position++]);
            else
            {
                if (S[position]==')')
                {
                    // pop the operator stack until we met a '('
                    while (op.top()!='(')
                    {
                        TNode tmp = new TreeNode (op.top());
                        tmp->rchild = val.top(); val.pop();
                        tmp->lchild = val.top(); val.pop();
                        tmp->rchild->parent = tmp->lchild->parent = tmp;
                        op.pop();
                        val.push(tmp);
                    }
                    TNode temp = val.top();
                    val.pop();
                    // form like sin(x^3+2*x^2+x+1) is possible, here we deal with this situation.
                    if (val.size() && val.top()->type == FUNCTION && val.top()->lchild == nullptr)
                    {
                        TNode t = val.top();
                        val.pop();
                        t->lchild = temp;
                        temp->parent = t;
                        temp = t;
                    }
                    val.push(temp);
                    op.pop();   // pop '('
                    position++;
                }
                // pop operators until we get an operator whose priority is lower than S[position]
                // or encounter '('
                else if (priority(op.top() >= priority(S[position])) && op.top() != '(')
                {
                    while (!op.empty() && priority(op.top())>=priority(S[position]) && op.top()!='(')
                    {
                        TNode temp = new TreeNode (op.top());
                        temp->rchild = val.top(); val.pop();
                        temp->lchild = val.top(); val.pop();
                        op.pop();
                        val.push(temp);
                    }
                    op.push(S[position++]);
                }
                else
                    op.push(S[position++]);
            }
            last = OPERATOR;
        }
        else
            return false;
    }
    // it's still possible that there are some operators left in stack.
    while (!op.empty())
    {
        TNode tmp = new TreeNode (op.top());
        tmp->rchild = val.top(); val.pop();
        tmp->lchild = val.top(); val.pop();
        tmp->rchild->parent = tmp->lchild->parent = tmp;
        op.pop();
        val.push(tmp);
    }
    
    // success
    if (!val.empty())
    {
        root = val.top();
        val.pop();
    }
    else
        root = nullptr;
    
    return true;
}

// this part is used to calculate the value of expression
// tree, using the input value x.
double Lexer::calculate(double x)
{
    double ans = 0;
    if(!root)
        return 0.0;
    else if(root->calculate(ans, x))
        return ans;
    return 0.0;
}
