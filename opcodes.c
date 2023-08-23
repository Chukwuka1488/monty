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

void op_pop(stack_t **stack, unsigned int line_number)
{
    pop_stack(stack, line_number);
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

