#include "monty.h"

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
        return (EXIT_FAILURE);
    }

	file = fopen(argv[1], "r");
    if (!file)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        return (EXIT_FAILURE);
    }

    while (fgets(line, BUFFER_SIZE, file) != NULL)
    {
		char *opcode;

        line_number++;
        opcode = strtok(line, " \t\n");

        if (opcode != NULL && opcode[0] != '#')
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
		    else if (strcmp(opcode, "swap") == 0)
    		{
                op_swap(&stack, line_number);
            }
            else if (strcmp(opcode, "add") == 0)
            {
                op_add(&stack, line_number);
            }
            else if (strcmp(opcode, "nop") == 0)
            {
                op_nop(&stack, line_number);
            }
            else if (strcmp(opcode, "sub") == 0)
            {
                op_sub(&stack, line_number);
            }
            else if (strcmp(opcode, "div") == 0)
            {
                op_div(&stack, line_number);
            }
            else if (strcmp(opcode, "mul") == 0)
            {
                op_mul(&stack, line_number);
            }
            else if (strcmp(opcode, "mod") == 0)
            {
                op_mod(&stack, line_number);
            }
            else if (strcmp(opcode, "pchar") == 0)
            {
                op_pchar(&stack, line_number);
            }
            else if (strcmp(opcode, "pstr") == 0)
            {
                op_pstr(&stack, line_number);
            }
            else if (strcmp(opcode, "rotl") == 0) /* New else if statement for rotl opcode */
            {
                op_rotl(&stack, line_number);
            }
            else if (strcmp(opcode, "rotr") == 0) /* New else if statement for rotr opcode */
            {
                op_rotr(&stack, line_number);
            }
            else if (strcmp(opcode, "stack") == 0) /* New else if statement for stack opcode */
            {
                op_stack(&stack, line_number);
            }   
            else if (strcmp(opcode, "queue") == 0) /* New else if statement for queue opcode */
            {
                op_queue(&stack, line_number);
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

    return (EXIT_SUCCESS);
}
