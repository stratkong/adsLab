#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 100

char stack[MAX];
char infix[MAX];
char postfix[MAX];
int top = -1;

void push(char c)
{
    if (top >= MAX - 1)
    {
        printf("Stack overflow\n");
        exit(1);
    }
    stack[++top] = c;
}

char pop()
{
    if (top < 0)
    {
        printf("Stack underflow\n");
        exit(1);
    }
    return stack[top--];
}

bool isEmpty()
{
    return top == -1;
}

int precedence (char symbol)
{
    switch(symbol)
    {
    case '^':
        return 3;
    case '/':
    case '*':
        return 2;
    case '+':
    case '-':
        return 1;
    default:
        return 0;
    }
}

void inToPost()
{
    int i,j=0;
    char symbol,next;
    for(i = 0;i < strlen(infix);i++)
    {
        symbol = infix[i];
        switch (symbol)
        {
        case '(':
            push(symbol);
            break;
        case ')':
            while ((next = pop()) != '(')
                    postfix[j++] = next;
            break;
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
            while(!isEmpty() && precedence(stack[top]) >= precedence(symbol))
                postfix[j++] = pop();
            push(symbol);
            break;
        default:
            postfix[j++] = symbol;
        }
    }
    while (!isEmpty())
    {
        postfix[j++] = pop();
    }
    postfix[j] = '\0';
}

int main()
{
    printf("enter the infix expression\n");
    gets(infix);
    inToPost();
    printf("%s",postfix);
}
