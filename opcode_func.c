#include "monty.h"

void monty_push(stack_t **stack, unsigned int line_number);
void monty_pall(stack_t **stack, unsigned int line_number);
void monty_pint(stack_t **stack, unsigned int line_number);
void monty_pop(stack_t **stack, unsigned int line_number);
void monty_swap(stack_t **stack, unsigned int line_number);
void monty_add(stack_t **stack, unsigned int line_number);
void monty_sub(stack_t **stack, unsigned int line_number);
void monty_div(stack_t **stack, unsigned int line_number);
void monty_mul(stack_t **stack, unsigned int line_number);
void monty_mod(stack_t **stack, unsigned int line_number);
void monty_nop(stack_t **stack, unsigned int line_number);
void monty_pchar(stack_t **stack, unsigned int line_number);
void monty_pstr(stack_t **stack, unsigned int line_number);
void monty_rotl(stack_t **stack, unsigned int line_number);
void monty_rotr(stack_t **stack, unsigned int line_number);
void monty_stack(stack_t **stack, unsigned int line_number);
void monty_queue(stack_t **stack, unsigned int line_number);

/**
 * monty_push - Pushes a value to a stack_t linked list.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line_number: The current working line number of a Monty bytecodes file.
 */
void monty_push(stack_t **stack, unsigned int line_number)
{
    stack_t *tmp, *new;
    int i;

    new = malloc(sizeof(stack_t));
    if (new == NULL)
    {
        op_token_error(mall_err());
        return;
    }

    if (op_toks[1] == NULL)
    {
        op_token_error(monty_arg_err(line_number));
        return;
    }

    for (i = 0; op_toks[1][i]; i++)
    {
        if (op_toks[1][i] == '-' && i == 0)
            continue;
        if (op_toks[1][i] < '0' || op_toks[1][i] > '9')
        {
            op_token_error(monty_arg_err(line_number));
            return;
        }
    }
    new->n = atoi(op_toks[1]);

    if (check_mode(*stack) == STACK) /* STACK mode insert at front */
    {
        tmp = (*stack)->next;
        new->prev = *stack;
        new->next = tmp;
        if (tmp)
            tmp->prev = new;
        (*stack)->next = new;
    }
    else /* QUEUE mode insert at end */
    {
        tmp = *stack;
        while (tmp->next)
            tmp = tmp->next;
        new->prev = tmp;
        new->next = NULL;
        tmp->next = new;
    }
}

/**
 * monty_pall - Prints the values of a stack_t linked list.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line_number: The current working line number of a Monty bytecodes file.
 */
void monty_pall(stack_t **stack, unsigned int line_number)
{
    stack_t *tmp = (*stack)->next;

    while (tmp)
    {
        printf("%d\n", tmp->n);
        tmp = tmp->next;
    }
    (void)line_number;
}

/**
 * monty_pint - Prints the top value of a stack_t linked list.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line_number: The current working line number of a Monty bytecodes file.
 */
void monty_pint(stack_t **stack, unsigned int line_number)
{
    if ((*stack)->next == NULL)
    {
        op_token_error(pint_error(line_number));
        return;
    }

    printf("%d\n", (*stack)->next->n);
}

/**
 * monty_pop - Removes the top value element of a stack_t linked list.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line_number: The current working line number of a Monty bytecodes file.
 */
void monty_pop(stack_t **stack, unsigned int line_number)
{
    stack_t *next = NULL;

    if ((*stack)->next == NULL)
    {
        op_token_error(pop_error(line_number));
        return;
    }

    next = (*stack)->next->next;
    free((*stack)->next);
    if (next)
        next->prev = *stack;
    (*stack)->next = next;
}

/**
 * monty_swap - Swaps the top two value elements of a stack_t linked list.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line_number: The current working line number of a Monty bytecodes file.
 */
void monty_swap(stack_t **stack, unsigned int line_number)
{
    stack_t *tmp;

    if ((*stack)->next == NULL || (*stack)->next->next == NULL)
    {
        op_token_error(short_stack_error(line_number, "swap"));
        return;
    }

    tmp = (*stack)->next->next;
    (*stack)->next->next = tmp->next;
    (*stack)->next->prev = tmp;
    if (tmp->next)
        tmp->next->prev = (*stack)->next;
    tmp->next = (*stack)->next;
    tmp->prev = *stack;
    (*stack)->next = tmp;
}

/**
 * monty_add - Adds the top two values of a stack_t linked list.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line_number: The current working line number of a Monty bytecodes file.
 *
 * Description: The result is stored in the second value node
 *              from the top and the top value  is removed.
 */
void monty_add(stack_t **stack, unsigned int line_number)
{
    if ((*stack)->next == NULL || (*stack)->next->next == NULL)
    {
        op_token_error(short_stack_error(line_number, "add"));
        return;
    }

    (*stack)->next->next->n += (*stack)->next->n;
    monty_pop(stack, line_number);
}

/**
 * monty_sub - Subtracts the second value from the top of
 *             a stack_t linked list by the top value.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line_number: The current working line number of a Monty bytecodes file.
 *
 * Description: The result is stored in the second value node
 *              from the top and the top value is removed.
 */
void monty_sub(stack_t **stack, unsigned int line_number)
{
    if ((*stack)->next == NULL || (*stack)->next->next == NULL)
    {
        op_token_error(short_stack_error(line_number, "sub"));
        return;
    }

    (*stack)->next->next->n -= (*stack)->next->n;
    monty_pop(stack, line_number);
}

/**
 * monty_div - Divides the second value from the top of
 *             a stack_t linked list by the top value.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line_number: The current working line number of a Monty bytecodes file.
 *
 * Description: The result is stored in the second value node
 *              from the top and the top value is removed.
 */
void monty_div(stack_t **stack, unsigned int line_number)
{
    if ((*stack)->next == NULL || (*stack)->next->next == NULL)
    {
        op_token_error(short_stack_error(line_number, "div"));
        return;
    }

    if ((*stack)->next->n == 0)
    {
        op_token_error(div_error(line_number));
        return;
    }

    (*stack)->next->next->n /= (*stack)->next->n;
    monty_pop(stack, line_number);
}

/**
 * monty_mul - Multiplies the second value from the top of
 *             a stack_t linked list by the top value.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line_number: The current working line number of a Monty bytecodes file.
 *
 * Description: The result is stored in the second value node
 *              from the top and the top value is removed.
 */
void monty_mul(stack_t **stack, unsigned int line_number)
{
    if ((*stack)->next == NULL || (*stack)->next->next == NULL)
    {
        op_token_error(short_stack_error(line_number, "mul"));
        return;
    }

    (*stack)->next->next->n *= (*stack)->next->n;
    monty_pop(stack, line_number);
}

/**
 * monty_mod - Computes the modulus of the second value from the
 *             top of a stack_t linked list  by the top value.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line_number: The current working line number of a Monty bytecodes file.
 *
 * Description: The result is stored in the second value node
 *              from the top and the top value is removed.
 */
void monty_mod(stack_t **stack, unsigned int line_number)
{
    if ((*stack)->next == NULL || (*stack)->next->next == NULL)
    {
        op_token_error(short_stack_error(line_number, "mod"));
        return;
    }

    if ((*stack)->next->n == 0)
    {
        op_token_error(div_error(line_number));
        return;
    }

    (*stack)->next->next->n %= (*stack)->next->n;
    monty_pop(stack, line_number);
}

/**
 * monty_nop - Does absolutely nothing for the Monty opcode 'nop'.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line_number: The current working line number of a Monty bytecodes file.
 */
void monty_nop(stack_t **stack, unsigned int line_number)
{
    (void)stack;
    (void)line_number;
}

/**
 * monty_pchar - Prints the character in the top value
 *               node of a stack_t linked list.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line_number: The current working line number of a Monty bytecodes file.
 */
void monty_pchar(stack_t **stack, unsigned int line_number)
{
    if ((*stack)->next == NULL)
    {
        op_token_error(pchar_error(line_number, "stack empty"));
        return;
    }
    if ((*stack)->next->n < 0 || (*stack)->next->n > 127)
    {
        op_token_error(pchar_error(line_number,
                                     "value out of range"));
        return;
    }

    printf("%c\n", (*stack)->next->n);
}

/**
 * monty_pstr - Prints the string contained in a stack_t linked list.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line_number: The current working line number of a Monty bytecodes file.
 */
void monty_pstr(stack_t **stack, unsigned int line_number)
{
    stack_t *tmp = (*stack)->next;

    while (tmp && tmp->n != 0 && (tmp->n > 0 && tmp->n <= 127))
    {
        printf("%c", tmp->n);
        tmp = tmp->next;
    }

    printf("\n");

    (void)line_number;
}

/**
 * monty_rotl - Rotates the top value of a stack_t linked list to the bottom.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line_number: The current working line number of a Monty bytecodes file.
 */
void monty_rotl(stack_t **stack, unsigned int line_number)
{
    stack_t *top, *bottom;

    if ((*stack)->next == NULL || (*stack)->next->next == NULL)
        return;

    top = (*stack)->next;
    bottom = (*stack)->next;
    while (bottom->next != NULL)
        bottom = bottom->next;

    top->next->prev = *stack;
    (*stack)->next = top->next;
    bottom->next = top;
    top->next = NULL;
    top->prev = bottom;

    (void)line_number;
}

/**
 * monty_rotr - Rotates the bottom value of a stack_t linked list to the top.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line_number: The current working line number of a Monty bytecodes file.
 */
void monty_rotr(stack_t **stack, unsigned int line_number)
{
    stack_t *top, *bottom;

    if ((*stack)->next == NULL || (*stack)->next->next == NULL)
        return;

    top = (*stack)->next;
    bottom = (*stack)->next;
    while (bottom->next != NULL)
        bottom = bottom->next;

    bottom->prev->next = NULL;
    (*stack)->next = bottom;
    bottom->prev = *stack;
    bottom->next = top;
    top->prev = bottom;

    (void)line_number;
}

/**
 * monty_stack - Converts a queue to a stack.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line_number: The current working line number of a Monty bytecodes file.
 */
void monty_stack(stack_t **stack, unsigned int line_number)
{
    (*stack)->n = STACK;
    (void)line_number;
}

/**
 * monty_queue - Converts a stack to a queue.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line_number: The current working line number of a Monty bytecodes file.
 */
void monty_queue(stack_t **stack, unsigned int line_number)
{
    (*stack)->n = QUEUE;
    (void)line_number;
}