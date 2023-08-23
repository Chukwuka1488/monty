#include "monty.h"

/**
 * push_stack - Pushes a value onto the stack
 * @stack: Pointer to the stack
 * @value: Value to be pushed
 */
void push_stack(stack_t **stack, int value)
{
    stack_t *new_node = create_node(value);
    if (new_node == NULL)
    {
        fprintf(stderr, "Error: malloc failed\n");
        exit(EXIT_FAILURE);
    }

    if (*stack == NULL)
    {
        new_node->prev = NULL;
        new_node->next = NULL;
    }
    else
    {
        new_node->prev = NULL;
        new_node->next = *stack;
        (*stack)->prev = new_node;
    }

    *stack = new_node;
}

/**
 * pop_stack - Pops the top element from the stack
 * @stack: Pointer to the stack
 * @return: Popped value
 */
int pop_stack(stack_t **stack, unsigned int line_number)
{
	int value;
	stack_t *temp;

    if (*stack == NULL)
    {
        fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
        exit(EXIT_FAILURE);
    }

    value = (*stack)->n;
    temp = *stack;
    *stack = (*stack)->next;
    if (*stack != NULL)
        (*stack)->prev = NULL;
    free(temp);

    return value;
}
