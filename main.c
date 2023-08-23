#include "monty.h"
#define BUFFER_SIZE 1024
#include <stdio.h>

/**
 * main - Entry point for the Monty interpreter
 * @argc: The number of command-line arguments
 * @argv: An array of command-line argument strings
 * Return: EXIT_SUCCESS if successful, otherwise EXIT_FAILURE
 */
int main(int argc, char *argv[])
{
	FILE *file;
	stack_t *stack = NULL;
	char *line = malloc(BUFFER_SIZE);
	unsigned int line_number = 0;

	if (argc != 2)
	{
        fprintf(stderr, "USAGE: %s file\n", argv[0]);
        return EXIT_FAILURE;
    }

	file = fopen(argv[1], "r");
    if (!file)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    while (fgets(line, BUFFER_SIZE, file) != NULL)
    {
		char *opcode;

        line_number++;
        opcode = strtok(line, " \t\n");

        if (opcode != NULL)
        {
            if (strcmp(opcode, "push") == 0)
            {
                op_push(&stack, line_number);
            }
            else if (strcmp(opcode, "pall") == 0)
            {
                op_pall(&stack, line_number);
            }
			else if (strcmp(opcode, "pop") == 0)
			{
				op_pop(&stack, line_number);
			}
			else if (strcmp(opcode, "pint") == 0)
		    {
        		op_pint(&stack, line_number);
    		}
		    else if (strcmp(opcode, "swap") == 0) /* New else if statement for swap opcode */
    		{
            op_swap(&stack, line_number);
    }
			else
            {
                fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
                fclose(file);
                free_stack(&stack);
				free(line);

                return EXIT_FAILURE;
            }
        }
    }

    fclose(file);
    free_stack(&stack);
	free(line);

    return EXIT_SUCCESS;
}
