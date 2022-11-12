/*
    File Owned By: Wali Temuri 1183379
    CIS-2520 A3, Question # 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 100

/*
Data Structure: Binary Tree
Purpose: Store nodes containing expression components
Stores: Operator, Operand, Variables, left and right child nodes
*/
typedef struct Tree
{
    int type; // 0 for var //1 for operand// 2 for operator
    char var[3]; //stores var
    char operand[5]; //stores operand 
    char operator; //stores operator
    struct Tree *left, *right;
} node;

// Node Stack to construct Tree
int nodeTop = -1;
node *nodeStack[25];

// Char stack to convert to postfix
char Stack[SIZE];
int top = -1;

// Function Headers

// Stack Functions
void push(char infixExp);
char pop();
int isEmpty();
int isFull();
char peek();

// String Functions
int IsOperator(char symbol);
int Presedence(char symbol);
void InfixToPostfix(char *infixExp);

// Tree Functions
node *ExpressionTree(char *s);
node *createNode(int type);
void pushNode(node *node);
node *popNode();
void PrintPreOrder(node *node);
void PrintPostOrder(node *);
void PrintMenu();

// Main Program
int main(int argc, char *argv[])
{

    char *userInput = malloc(sizeof(char) * strlen(argv[1]));

    strcpy(userInput, argv[1]);
    InfixToPostfix(userInput);
    node *root = ExpressionTree(userInput);

    // PrintPreOrder(root);
    int input = 0;
    while (input != 7)
    {
        PrintMenu();
        scanf("%d", &input);
        switch (input)
        {
        case 1:
            printf("Feature not implemented\n");
            break;
        case 2:
            PrintPreOrder(root);
            printf("\n");
            break;
        case 3:
            printf("Feature not implemented\n");
            break;
        case 4:
            PrintPostOrder(root);
            printf("\n");
            break;
        case 5:
            printf("Feature not implemented\n");
        case 6:
            printf("Feature not implemented\n");
            break;
        case 7:
            break;
        default:
            break;
        }
    }

    free(userInput);
}

/*
Function: Pushes item on to the Stack
Input: char item
Output: void
*/
void push(char item)
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

/*
Function: Pops the first item on the stack
Input: void
Output: void
*/
char pop()
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

/*
Function: Returns true if the stack is empty
Input: char item
Output: void
*/
int isEmpty()
{
    return top == -1;
}

/*
Function: Checks if the Stack is full
Input: void
Output: void
*/
int isFull()
{
    return top == SIZE - 1;
}

/*
Function: Returns item on top of stack without popping it
Input: void
Output: void
*/
char peek()
{
    return Stack[top];
}

/*
Function: Returns if symbol is an operator
Input: char symbol
Output: int
*/
int IsOperator(char symbol)
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

/*
Function: Ranks presedence of the operator
Input: char operator
Output: int
*/
int Presedence(char operator)
{
    if (operator== '*' || operator== '/')
    {
        return 2;
    }
    else if (operator== '+' || operator== '-')
    {
        return 1;
    }

    return 0;
}

/*
Function:Converts input from infix to postfix so tree construction is easy
Input: char *infixExp
Output: void
*/
void InfixToPostfix(char *infixExp)
{
    int i, j;
    char x;

    for (i = 0, j = -1; infixExp[i]; ++i)
    {
        if (isalpha(infixExp[i]) || isdigit(infixExp[i]))
        {
            infixExp[++j] = infixExp[i];
        }
        else if (infixExp[i] == '(')
        {
            push(infixExp[i]);
        }
        else if (infixExp[i] == ')')
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
        else if (infixExp[i] == '.')
        {
            infixExp[++j] = infixExp[i];
        }
        else
        {
            while (!isEmpty() && Presedence(infixExp[i]) <= Presedence(peek()))
            {
                infixExp[++j] = pop();
            }
            push(infixExp[i]);
        }
    }

    while (!isEmpty())
    {
        infixExp[++j] = pop();
    }

    infixExp[++j] = '\0';
}

/*
Function: Creates new node
Input: int type
Output: node * 
*/
node *createNode(int type)
{
    node *newNode = malloc(sizeof(node));

    newNode->left = NULL;
    newNode->right = NULL;
    newNode->type = type;

    return newNode;
}

/*
Function: Pushes a node onto the stack
Input: node * node
Output: void
*/
void pushNode(node *node)
{
    if (nodeTop > 25)
    {
        printf("Stack Overflow\n");
        exit(1);
    }
    nodeTop++;
    nodeStack[nodeTop] = node;
}

/*
Function: Pops the first node on the stack
Input: void
Output: node * node
*/
node *popNode()
{
    if (nodeTop <= -1)
    {
        printf("Stack Underflow\n");
        exit(1);
    }

    return nodeStack[nodeTop--];
}

/*
Function: Constructs the Expression Tree
Input: char * s
Output: node * node
*/
node *ExpressionTree(char *s)
{
    int i;
    int varC = 0;

    for (i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == 'x')
        {
            ++varC;
            char var[3];
            node *varNode = createNode(0);

            var[0] = s[i];
            var[1] = varC + '0';
            strcpy(varNode->var, var);
            i++;
            pushNode(varNode);
        }
        else if (IsOperator(s[i]))
        {
            node *opNode = createNode(1);

            opNode->operator= s[i];
            opNode->right = popNode();
            opNode->left = popNode();
            pushNode(opNode);
        }
        else
        {
            node *flNode = createNode(2);
            int j = 0;
            for (j = 0; j < 4; j++)
            {
                flNode->operand[j] = s[i];
                ++i;
            }

            i--;
            pushNode(flNode);
        }
    }

    node *root = popNode();
    return root;
}
/*
Function: Prints the expression tree using preorder traversal
Input: node * node
Output: void
*/
void PrintPreOrder(node *node)
{
    if (node == NULL)
    {
        return;
    }

    switch (node->type)
    {
    case 0:
        printf("%s ", node->var);
        break;
    case 1:
        printf("%c ", node->operator);
        break;
    case 2:
        printf("%s ", node->operand);
        break;
    default:
        break;
    }

    PrintPreOrder(node->left);
    PrintPreOrder(node->right);
}

/*
Function: Prints the expression tree using postorder traversal
Input: node * node
Output: void
*/
void PrintPostOrder(node *node)
{
    if (node == NULL)
    {
        return;
    }

    PrintPostOrder(node->left);
    PrintPostOrder(node->right);

    switch (node->type)
    {
    case 0:
        printf("%s ", node->var);
        break;
    case 1:
        printf("%c ", node->operator);
        break;
    case 2:
        printf("%s ", node->operand);
        break;
    default:
        break;
    }
}

/*
Function: Prints the Menu
Input: void
Output: void
*/
void PrintMenu()
{
    printf("Please select from the following options:\n1. Display\n2. Preorder\n3. Inorder\n4. Postorder\n5. Update\n6. Calculate\n7. Exit\n");
}