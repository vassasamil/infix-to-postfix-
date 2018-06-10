#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
// Stack type
struct Stack
{
    int top;
    unsigned capacity;
    int* array;
};
 
// Stack Operations
struct Stack* createStack( unsigned capacity )
{
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
 
    if (!stack) 
        return NULL;
 
    stack->top = -1;
    stack->capacity = capacity;
 
    stack->array = (int*) malloc(stack->capacity * sizeof(int));
 
    if (!stack->array)
        return NULL;
    return stack;
}
int isEmpty(struct Stack* stack)
{
    return stack->top == -1 ;
}
char peek(struct Stack* stack)
{
    return stack->array[stack->top];
}
char pop(struct Stack* stack)
{
    if (!isEmpty(stack))
        return stack->array[stack->top--] ;
    return '$';
}
void push(struct Stack* stack, char op)
{
    stack->array[++stack->top] = op;
}
 

// A utility function to check if the given character is operand
int isOperand(char ch)
{
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}
// A utility function to return priority of a given operator
// Higher returned value means higher priority
int Priority(char ch)
{
    switch (ch)
    {
    case '+':
    case '-':
        return 1;
 
    case '*':
    case '/':
        return 2;
 
    case '=':
        return 0;
    }
    return -1;
}
//function to convert infix to postfix
int infixToPostfix(char* input,char* output)
{
	int i,k;
	// we create stack equal to size of input
    struct Stack* stack = createStack(strlen(input));
    if(!stack) // See if stack was created successfully 
        return -1 ;
    
    for (i=0 , k=-1; input[i] ; i++ ){
    	// if the sccanned character is operand we add it to output
        if (isOperand(input[i]))
            output[++k] = input[i];
         
        // If the scanned character is an ‘(‘, we push it to the stack.
        else if (input[i] == '(')
            push(stack, input[i]);
         
        // If the scanned character is an ‘)’, pop and output from the stack 
        // until an ‘(‘ is encountered.
        else if (input[i] == ')')
        {
            while (!isEmpty(stack) && peek(stack) != '(')
                output[++k] = pop(stack);
            if (!isEmpty(stack) && peek(stack) != '(')  ;         
            else
                pop(stack);
        }
        else // if we scan any other operator we push it to stack by their priorities
        {
            while (!isEmpty(stack) && Priority(input[i]) <= Priority(peek(stack)) )
                output[++k] = pop(stack);
            push(stack, input[i]);
        }
 
    }
 
    // pop everything from stack
    while (!isEmpty(stack))
        output[++k] = pop(stack );	
	}
int main(int argc, char **argv)
{
	FILE *ptr_file;
    		char output[10000];
    		char input [1000];
    		int count=0;
    		int ci;

    		ptr_file =fopen("input.txt","r");
    		if (!ptr_file)
        		return 1;

    		while (fgets(input,1000, ptr_file)!=NULL  )
        	printf("%s\n",input);
        	fclose(ptr_file);
        	
			while(input[count]!='\0'){
			    if(input[count]== ' '){
					ci=count;
			
				while(input[ci]!='\0'){
					input[ci]=input[ci+1];
					ci++;
				}
				
				}
				count++;
				}	
		

		infixToPostfix(input,output);
    	printf("%s\n",input);
    	printf("%s\n",output);
return 0;
}

