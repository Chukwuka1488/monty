/* memory_management.c */

#include "monty.h"

/**
 * create_node - Creates a new stack node
 * @n: Value to be stored in the new node
 * @return: Pointer to the newly created node
 */
stack_t *create_node(int n)
{
    stack_t *new_node = malloc(sizeof(stack_t));
    if (new_node == NULL)
    {
        fprintf(stderr, "Error: malloc failed\n");
        exit(EXIT_FAILURE);
    }

    new_node->n = n;
    new_node->prev = NULL;
    new_node->next = NULL;

    return new_node;
}

/**
 * free_stack - Frees the entire stack
 * @stack: Pointer to the stack
 */
void free_stack(stack_t **stack)
{
    while (*stack != NULL)
    {
        stack_t *temp = *stack;
        *stack = (*stack)->next;
        free(temp);
    }
}
