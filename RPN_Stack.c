#include <stdio.h>
#include <stdlib.h>


// Reverse Polish Notation (RPN) calculator implementation using a stack!



#define MAX_STACK_SIZE 10

typedef enum
{
    ADD,
    MULT,
    SUBTRACT,
    DIV,
    UNSUPPORTED
} MathOperation;

void IssueBadNumberError()
{
    printf("The string does not represent a floating point number.\n");
    exit(EXIT_FAILURE);
}

void IssueBadOperationError()
{
    printf("The string does not represent a valid operation.\n");
    exit(EXIT_FAILURE);
}

MathOperation GetOperation(char *op)
{
	const char *count = op;
	while (*count != '\0'){
		count++;
	}
	if (count - op > 1){
			 return UNSUPPORTED;
		}

	switch(*op){
		case '+':
			return ADD;
		case '-':
			return SUBTRACT;
		case 'x':
			return MULT;
		case '/':
			return DIV;
		default:
			return UNSUPPORTED;
	}
}


double StringToDouble(char *str)
{
    double result = 0.0;
    int sign = 1;

    if (*str == '-'){
	    sign = -1;
	    ++str;
    }

    while (*str != '.' &&  *str != '\0'){
		if (*str >= '0' && *str <= '9'){
			result = result * 10.0 +  (*str - '0');
		}
		else{
			IssueBadNumberError();
		}
	++str;
    }

    if (*str == '.'){
	    str++;
	    double power = 10.0;
	    while (*str != '\0'){
		if (*str >= '0' && *str <= '9'){
			result += (*str - '0') / power;
			power *= 10;
		}
		else{
			IssueBadNumberError();
		}
		++str;
	    }
    } 
    return result * sign;
}

typedef struct
{
    double data[MAX_STACK_SIZE];
    int top;
} Stack;

void InitStack(Stack *s)
{
    s->top = -1;
}

int IsEmpty(Stack *s)
{
    return s->top == -1;
}

int Overflow(Stack *s)
{
    return s->top == MAX_STACK_SIZE - 1;
}

void Push(Stack *s, double value)
{
    if (Overflow(s))
    {
        printf("Stack overflow :(\n");
        exit(EXIT_FAILURE);
    }
    s->data[++(s->top)] = value;
}

double Pop(Stack *s)
{
    if (IsEmpty(s))
    {
        printf("Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return s->data[(s->top)--];
}

int main(int argc, char *argv[])
{
    Stack stack;
    InitStack(&stack);

    for (int i = 1; i < argc; i++)
    {
        char *arg = argv[i];
        MathOperation op = GetOperation(arg);

        if (op != UNSUPPORTED)
        {
            if (stack.top < 1)
            {
                IssueBadOperationError();
            }
            double b = Pop(&stack);
            double a = Pop(&stack);

            double result;
            switch (op)
            {
            case ADD:
                result = a + b;
                break;
            case SUBTRACT:
                result = a - b;
                break;
            case MULT:
                result = a * b;
                break;
            default:
                IssueBadOperationError();
            }
            Push(&stack, result);
        }
        else
        {
            double number = StringToDouble(arg);
            Push(&stack, number);
        }
    }

    if (stack.top != 0)
    {
        printf("Error: Invalid input\n");
        return EXIT_FAILURE;
    }

    double Result = Pop(&stack);
    printf("The total is %d\n", (int)Result);

    return 0;
}

