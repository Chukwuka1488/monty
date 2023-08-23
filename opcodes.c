#include "monty.h"

/**
 * op_push - Implements the push opcode
 * @stack: Pointer to the stack
 * @line_number: Line number in the Monty file
 */
void op_push(stack_t **stack, unsigned int line_number)
{
    char *arg = strtok(NULL, " \t\n");
	int value;

    if (arg == NULL || !is_valid_integer(arg))
    {
        fprintf(stderr, "L%u: usage: push integer\n", line_number);
        exit(EXIT_FAILURE);
    }

    value = atoi(arg);
    push_stack(stack, value);
}

/**
 * op_pall - Implements the pall opcode
 * @stack: Pointer to the stack
 * @line_number: Line number in the Monty file
 */
void op_pall(stack_t **stack, unsigned int line_number)
{
	stack_t *current;

    (void)line_number;
    current = *stack;

    while (current != NULL)
    {
        printf("%d\n", current->n);
        current = current->next;
    }
}

/**
 * op_pint - Prints the value at the top of the stack
 * @stack: Double pointer to the head of the stack
 * @line_number: The line number currently being executed
 *
 * Description: Prints the value at the top of the stack, followed by a new line.
 * If the stack is empty, prints an error message to stderr and exits with a
 * status of EXIT_FAILURE.
 */
void op_pint(stack_t **stack, unsigned int line_number)
{
    if (*stack == NULL)
    {
        fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
        exit(EXIT_FAILURE);
    }

    printf("%d\n", (*stack)->n);
}

/**
 * op_pop - Removes the top element of the stack
 * @stack: Double pointer to the head of the stack
 * @line_number: The line number currently being executed
 *
 * Description: Removes the top element of the stack. If the stack is empty,
 * prints an error message to stderr and exits with a status of EXIT_FAILURE.
 */
void op_pop(stack_t **stack, unsigned int line_number)
{
    if (*stack == NULL)
    {
        fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
        exit(EXIT_FAILURE);
    }

    pop_stack(stack, line_number);
}

/**
 * op_swap - Swaps the top two elements of the stack
 * @stack: Double pointer to the head of the stack
 * @line_number: The line number currently being executed
 *
 * Description: Swaps the top two elements of the stack. If the stack contains
 * less than two elements, prints an error message to stderr and exits with a
 * status of EXIT_FAILURE.
 */
void op_swap(stack_t **stack, unsigned int line_number)
{
    int temp;

    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%u: can't swap, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    temp = (*stack)->n;
    (*stack)->n = (*stack)->next->n;
    (*stack)->next->n = temp;
}

/**
 * op_add - Adds the top two elements of the stack
 * @stack: Double pointer to the head of the stack
 * @line_number: The line number currently being executed
 *
 * Description: Adds the top two elements of the stack. If the stack contains
 * less than two elements, prints an error message to stderr and exits with a
 * status of EXIT_FAILURE. The result is stored in the second top element of
 * the stack and the top element is removed.
 */
void op_add(stack_t **stack, unsigned int line_number)
{
    int sum;

    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%u: can't add, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    sum = (*stack)->n + (*stack)->next->n;
    pop_stack(stack, line_number);
    (*stack)->n = sum;
}

/**
 * op_nop - Does nothing
 * @stack: Double pointer to the head of the stack
 * @line_number: The line number currently being executed
 *
 * Description: Does nothing.
 */
void op_nop(stack_t **stack, unsigned int line_number)
{
    (void)stack;
    (void)line_number;
}

/**
 * op_sub - Subtracts the top element of the stack from the second top element
 * @stack: Double pointer to the head of the stack
 * @line_number: The line number currently being executed
 *
 * Description: Subtracts the top element of the stack from the second top
 * element of the stack. If the stack contains less than two elements, prints
 * an error message to stderr and exits with a status of EXIT_FAILURE. The
 * result is stored in the second top element of the stack and the top element
 * is removed.
 */
void op_sub(stack_t **stack, unsigned int line_number)
{
    int difference;

    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%u: can't sub, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    difference = (*stack)->next->n - (*stack)->n;
    pop_stack(stack, line_number);
    (*stack)->n = difference;
}

/**
 * op_div - Divides the second top element of the stack by the top element
 * @stack: Double pointer to the head of the stack
 * @line_number: The line number currently being executed
 *
 * Description: Divides the second top element of the stack by the top element
 * of the stack. If the stack contains less than two elements, prints an error
 * message to stderr and exits with a status of EXIT_FAILURE. The result is
 * stored in the second top element of the stack and the top element is removed.
 * If the top element of the stack is 0, prints an error message to stderr and
 * exits with a status of EXIT_FAILURE.
 */
void op_div(stack_t **stack, unsigned int line_number)
{
    int quotient;

    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%u: can't div, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    if ((*stack)->n == 0)
    {
        fprintf(stderr, "L%u: division by zero\n", line_number);
        exit(EXIT_FAILURE);
    }

    quotient = (*stack)->next->n / (*stack)->n;
    pop_stack(stack, line_number);
    (*stack)->n = quotient;
}

/**
 * op_mul - Multiplies the second top element of the stack with the top element
 * @stack: Double pointer to the head of the stack
 * @line_number: The line number currently being executed
 *
 * Description: Multiplies the second top element of the stack with the top
 * element of the stack. If the stack contains less than two elements, prints
 * an error message to stderr and exits with a status of EXIT_FAILURE. The
 * result is stored in the second top element of the stack and the top element
 * is removed.
 */
void op_mul(stack_t **stack, unsigned int line_number)
{
    int product;

    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%u: can't mul, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    product = (*stack)->next->n * (*stack)->n;
    pop_stack(stack, line_number);
    (*stack)->n = product;
}

/**
 * op_mod - Computes modulo division of second top element by top element
 * @stack: Double pointer to head of stack
 * @line_number: Line number currently being executed
 *
 * Description: Computes modulo division of second top element by top element.
 * If stack contains less than two elements or if top element is 0,
 * prints error message to stderr and exits with status EXIT_FAILURE.
 */
void op_mod(stack_t **stack, unsigned int line_number)
{
    int mod;

    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%u: can't mod, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    if ((*stack)->n == 0)
    {
        fprintf(stderr, "L%u: division by zero\n", line_number);
        exit(EXIT_FAILURE);
    }

    mod = (*stack)->next->n % (*stack)->n;
    pop_stack(stack, line_number);
    (*stack)->n = mod;
}

/**
 * op_pchar - Prints the char at the top of the stack
 * @stack: Double pointer to the head of the stack
 * @line_number: The line number currently being executed
 *
 * Description: Prints the char at the top of the stack, followed by a new line.
 * The integer stored at the top of the stack is treated as the ASCII value of
 * the character to be printed. If the value is not in the ASCII table or if
 * the stack is empty, prints an error message to stderr and exits with a status
 * of EXIT_FAILURE.
 */
void op_pchar(stack_t **stack, unsigned int line_number)
{
    int value;

    if (*stack == NULL)
    {
        fprintf(stderr, "L%u: can't pchar, stack empty\n", line_number);
        exit(EXIT_FAILURE);
    }

    value = (*stack)->n;
    if (value < 0 || value > 127)
    {
        fprintf(stderr, "L%u: can't pchar, value out of range\n", line_number);
        exit(EXIT_FAILURE);
    }

    printf("%c\n", value);
}

/**
 * op_pstr - Prints the string starting at the top of the stack
 * @stack: Double pointer to the head of the stack
 * @line_number: The line number currently being executed
 *
 * Description: Prints the string starting at the top of the stack, followed by
 * a new line. The integer stored in each element of the stack is treated as
 * the ASCII value of the character to be printed. The string stops when either
 * the stack is over, the value of an element is 0, or the value of an element
 * is not in the ASCII table. If the stack is empty, prints only a new line.
 */
void op_pstr(stack_t **stack, unsigned int line_number)
{
    stack_t *current;

    (void)line_number;
    current = *stack;

    while (current != NULL && current->n > 0 && current->n <= 127)
    {
        printf("%c", current->n);
        current = current->next;
    }

    printf("\n");
}

/**
 * op_rotl - Rotates the stack to the top
 * @stack: Double pointer to the head of the stack
 * @line_number: The line number currently being executed
 *
 * Description: Rotates the stack to the top. The top element of the stack
 * becomes the last one, and the second top element of the stack becomes the
 * first one. This opcode never fails.
 */
void op_rotl(stack_t **stack, unsigned int line_number)
{
    stack_t *top;
    stack_t *bottom;

    (void)line_number;
    if (*stack == NULL || (*stack)->next == NULL)
        return;

    top = *stack;
    bottom = *stack;
    while (bottom->next != NULL)
        bottom = bottom->next;

    *stack = top->next;
    (*stack)->prev = NULL;
    bottom->next = top;
    top->prev = bottom;
    top->next = NULL;
}

/**
 * op_rotr - Rotates the stack to the bottom
 * @stack: Double pointer to the head of the stack
 * @line_number: The line number currently being executed
 *
 * Description: Rotates the stack to the bottom. The last element of the stack
 * becomes the top element of the stack. This opcode never fails.
 */
void op_rotr(stack_t **stack, unsigned int line_number)
{
    stack_t *top;
    stack_t *bottom;

    (void)line_number;
    if (*stack == NULL || (*stack)->next == NULL)
        return;

    top = *stack;
    bottom = *stack;
    while (bottom->next != NULL)
        bottom = bottom->next;

    *stack = bottom;
    bottom->prev->next = NULL;
    bottom->prev = NULL;
    bottom->next = top;
    top->prev = bottom;
}

/**
 * op_stack - Sets the format of the data to a stack (LIFO)
 * @stack: Double pointer to the head of the stack
 * @line_number: The line number currently being executed
 *
 * Description: Sets the format of the data to a stack (LIFO). This is the
 * default behavior of the program.
 */
void op_stack(stack_t **stack, unsigned int line_number)
{
    (void)stack;
    (void)line_number;
    /* Set global variable or data structure to indicate stack mode */
}

/**
 * op_queue - Sets the format of the data to a queue (FIFO)
 * @stack: Double pointer to the head of the stack
 * @line_number: The line number currently being executed
 *
 * Description: Sets the format of the data to a queue (FIFO).
 */
void op_queue(stack_t **stack, unsigned int line_number)
{
    (void)stack;
    (void)line_number;
    /* Set global variable or data structure to indicate queue mode */
}

/**
 * is_valid_integer - Checks if a string represents a valid integer
 * @str: The string to check
 *
 * Return: true if the string represents a valid integer, otherwise false
 *
 * Description: Checks if a given string represents a valid integer. A string
 * is considered to represent a valid integer if it consists only of digits,
 * with an optional leading '+' or '-' sign.
 */
bool is_valid_integer(char *str)
{
    if (*str == '-' || *str == '+')
        str++;

    if (*str == '\0')
        return (false);

    while (*str != '\0')
    {
        if (!isdigit(*str))
            return (false);
        str++;
    }

    return (true);
}

