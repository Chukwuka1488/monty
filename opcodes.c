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

bool is_valid_integer(char *str)
{
    if (*str == '-' || *str == '+')
        str++;

    if (*str == '\0')
        return false;

    while (*str != '\0')
    {
        if (!isdigit(*str))
            return false;
        str++;
    }

    return true;
}

