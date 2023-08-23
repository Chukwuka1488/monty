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

