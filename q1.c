#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 100

//Binary Tree Struct                                        
typedef struct node {   
    char * data; //For string nodes
    float value; //For num nodes
    char op; //For operator ndoes
    struct node *left, *right;
} exp;

char Stack[SIZE];
int top = -1;

void push (char infixExp);
char pop ();

void InfixToPostfix (char * item);
//Main Program
int main (int argc, char* argv[]) {

    char * infix = malloc(sizeof(char) * strlen(argv[1]));
    
    strcpy(infix, argv[1]);

    strcpy(infix, "(((x1+5.12)*(x2-7.68))/x3)");
    InfixToPostfix(infix);

    printf("%s", infix);

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

int precedence (char symbol)
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
            while(!isEmpty() && precedence(infixExp[i]) <= precedence(peek()))
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