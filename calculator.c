#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct
{
    char *array;
    int top;
} Stack;

void initializeStack(Stack *stack, int maxSize);
void push(Stack *stack, char value);
char pop(Stack *stack);
int isStackEmpty(const Stack *stack);
int isOperator(char c);
int getOperatorPrecedence(char c);
double evaluateExpression(const char *expression);

int main()
{
    char expression[100];

    printf("Enter a mathematical expression: ");
    fgets(expression, sizeof(expression), stdin);
    expression[strcspn(expression, "\n")] = '\0';

    double result = evaluateExpression(expression);
    printf("Result: %.2f\n", result);

    return 0;
}

void initializeStack(Stack *stack, int maxSize)
{
    stack->array = (char *)malloc(maxSize * sizeof(char));
    stack->top = -1;
}

void push(Stack *stack, char value)
{
    stack->array[++stack->top] = value;
}

char pop(Stack *stack)
{
    return stack->array[stack->top--];
}

int isStackEmpty(const Stack *stack)
{
    return stack->top == -1;
}

int isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int getOperatorPrecedence(char c)
{
    return (c == '+' || c == '-') ? 1 : ((c == '*' || c == '/') ? 2 : 0);
}

double evaluateExpression(const char *expression)
{
    Stack operatorStack, operandStack;
    initializeStack(&operatorStack, strlen(expression));
    initializeStack(&operandStack, strlen(expression));

    for (int i = 0; expression[i] != '\0'; ++i)
    {
        if (isdigit(expression[i]))
        {
            push(&operandStack, expression[i] - '0');
        }
        else if (isOperator(expression[i]))
        {
            while (!isStackEmpty(&operatorStack) &&
                   getOperatorPrecedence(expression[i]) <= getOperatorPrecedence(operatorStack.array[operatorStack.top]))
            {
                char op = pop(&operatorStack);
                double operand2 = pop(&operandStack);
                double operand1 = pop(&operandStack);

                switch (op)
                {
                case '+':
                    push(&operandStack, operand1 + operand2);
                    break;
                case '-':
                    push(&operandStack, operand1 - operand2);
                    break;
                case '*':
                    push(&operandStack, operand1 * operand2);
                    break;
                case '/':
                    push(&operandStack, operand1 / operand2);
                    break;
                }
            }
            push(&operatorStack, expression[i]);
        }
    }

    while (!isStackEmpty(&operatorStack))
    {
        char op = pop(&operatorStack);
        double operand2 = pop(&operandStack);
        double operand1 = pop(&operandStack);

        switch (op)
        {
        case '+':
            push(&operandStack, operand1 + operand2);
            break;
        case '-':
            push(&operandStack, operand1 - operand2);
            break;
        case '*':
            push(&operandStack, operand1 * operand2);
            break;
        case '/':
            push(&operandStack, operand1 / operand2);
            break;
        }
    }

    double result = pop(&operandStack);
    free(operatorStack.array);
    free(operandStack.array);

    return result;
}
