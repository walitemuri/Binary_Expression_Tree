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

char * Stack[SIZE];
int top = -1;

void push (char item);
char pop ();

char * InfixToPostfix (char * infixExp);
//Main Program
int main (int argc, char* argv[]) {

    int i, j;
    char * inputString = malloc(sizeof(char) * strlen(argv[1]));
    strcpy(inputString, argv[1]);

    char item = inputString[i];
    

    /*
        ^  R-L
        /* L-R 
        +- L-R   
    */

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
    if (symbol == '*' || suymbol == '/')
    {
        return 2;
    }
    else if (symbol == '+' || symbol == '-')
    {
        return 1;
    }

    return 0;
}

char * InfixToPostfix (char * infixExp)
{
    int i = 0;
    int j = 0;

    char item = infixExp[i];

    while (item != '\0')
    {
        if (item == '(')
        {
            push(item);
        }
        else if (isalpha(item))
        {

        }
        else if (isdigit(item))
        {

        }
        else if (IsOperator(item))
        {

        }
        else if (item == ')')
        {

        }
        else if (item == '.')
        {

        }
        else
        {

        }
        i++;

        item = infixExp[i];
    }
}