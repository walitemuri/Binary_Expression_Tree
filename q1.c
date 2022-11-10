#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 100

//Binary Tree Struct                                        
typedef struct Tree { 
    int type; //0 for var //1 for operand// 2 for operator
    char var[3];
    char operand[5];   
    char operator; //For string nodes
    struct Tree *left, *right;
}node;

int nodeTop = -1;
node * nodeStack[25];

char Stack[SIZE];
int top = -1;

void push (char infixExp);
char pop ();
node * ExpressionTree(char * s);
void InfixToPostfix (char * item);
//Main Program
int main (int argc, char* argv[]) {

    char * infix = malloc(sizeof(char) * strlen(argv[1]));
    
    strcpy(infix, argv[1]);

    strcpy(infix, "(((x1+5.12)*(x2-7.68))/x3)");
    InfixToPostfix(infix);

    node * root = ExpressionTree(infix);

    printf("%s\n%c\n", infix, root->operator);

}

void push (char item)
{
    if (top >= SIZE - 1)
    {
        printf("Stack Overflow\n");
    }
    else
    {
        top++;
        Stack[top] = item;
    }
}

char pop ()
{
    char item;

    if (top < 0)
    {
        printf("Stack underflow\n");
        exit(1);
    }
    else
    {
        item = Stack[top];
        top--;
        return item;
    }
}

int isEmpty()
{
    return top == -1;
}

int isFull()
{
    return top == SIZE - 1;
}

char peek()
{
    return Stack[top];
}


int IsOperator (char symbol)
{
    if (symbol == '*' || symbol == '/' || symbol == '-' || symbol == '+')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int Presedence (char symbol)
{
    if (symbol == '*' || symbol == '/')
    {
        return 2;
    }
    else if (symbol == '+' || symbol == '-')
    {
        return 1;
    }

    return 0;
}

void InfixToPostfix (char * infixExp)
{
    int i , j;
    char x;

    for (i = 0, j = -1; infixExp[i]; ++i)
    {
        if(isalpha(infixExp[i]) || isdigit(infixExp[i]))
        {
            infixExp[++j] = infixExp[i];
        }
        else if (infixExp[i] == '(')
        {
            push(infixExp[i]);
        }
        else if(infixExp[i] == ')')
        {
            while (!isEmpty() && peek() != '(')
            {
                infixExp[++j] = pop();
            }
            if (!isEmpty() && peek() != '(')
            {
                return;
            }
            else
            {
                pop();
            }
        }
        else if(infixExp[i] == '.')
        {
            infixExp[++j] = infixExp[i];
        }
        else
        {
            while(!isEmpty() && Presedence(infixExp[i]) <= Presedence(peek()))
            {
                infixExp[++j] = pop();
            }
            push(infixExp[i]);
        }
    }

    while(!isEmpty())
    {
        infixExp[++j] = pop();
    }

    infixExp[++j] = '\0';
}

node * createNode (int type)
{
    node * newNode = malloc(sizeof(node));

    newNode->left = NULL;
    newNode->right = NULL;
    newNode->type = type;

    return newNode;

}

void pushNode (node * node)
{
    if (nodeTop > 25)
    {
        printf("Stack Overflow\n");
        exit(1);
    }
    ++nodeTop;
    nodeStack[nodeTop] = node;
}

node * popNode()
{
    if (nodeTop <= -1)
    {
        printf("Stack Underflow\n");
        exit(1);
    }

    return nodeStack[nodeTop--];
}

node * ExpressionTree (char * s)
{
    int i;
    int varC = 0;

    for (i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == 'x')
        {
            ++varC;
            char var[3];
            node * varNode = createNode(0);

            var[0] = s[i];
            var[1] = varC + '0';
            strcpy(varNode->var, var);   
            ++i;
            pushNode(varNode);
        }
        else if(IsOperator(s[i]))
        {
            node * opNode = createNode(1);

            opNode->operator = s[i];

            node * right = popNode();
            node * left = popNode();
            pushNode(opNode);
        }
        else    
        {
            node * flNode = createNode(2);
            int j;
            for (j = 0; j < 4; j++)
            {
                flNode->operand[j] = s[i];
                ++i;
            }
            pushNode(flNode);
        }
    }

    node* root = popNode();
    return root;
}