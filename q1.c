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

void InfixToPostfix (char * item, char* post);
//Main Program
int main (int argc, char* argv[]) {

    char * infix = malloc(sizeof(char) * strlen(argv[1]));
    char * postfix = malloc(sizeof(char)* 100);
    
    strcpy(infix, argv[1]);
    
    InfixToPostfix(infix, postfix);
    
    printf("%s", postfix);

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

void InfixToPostfix (char * infixExp, char *postfixExp)
{
    int i = 0;
    int j = 0;
    char x;

    while (infixExp[i] != '\0')
    {
        if (infixExp[i] == '(')
        {
            push(infixExp[i]);
        }
        else if (isalpha(infixExp[i]) || isdigit(infixExp[i]))
        {
            postfixExp[j] = infixExp[i];
            j++;
        }
        else if (IsOperator(infixExp[i]) == 1)
        {
            x = pop();
            while (IsOperator(x) == 1 &&precedence(x) >= precedence(infixExp[i]))
            {
                postfixExp[j] = x;
                j++;
                x = pop();
            }
            push(x);

            push(infixExp[i]);   
        }
        else if (infixExp[i] == ')')
        {
            x = pop();
            while(x != '(')
            {
                postfixExp[j] = x;
                j++;
                x = pop();
            }
        }
        else if (infixExp[i] == '.')
        {
            postfixExp[j] = infixExp[i];
            j++;
        }
        else
        {
            printf("Invalid Infix Expression\n");
            exit(1);
        }
        i++;
    }
}