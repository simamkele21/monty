#include "monty.h"

/**
 * op_token_error - Sets last element of op_toks to be an error code.
 * @error_code: Integer to store as a string in op_toks.
 */
void op_token_error(int error_code)
{
    int total_toks = 0, i = 0;
    char *exit_str = NULL;
    char **new_toks = NULL;

    total_toks = token_arr_len();
    new_toks = malloc(sizeof(char *) * (total_toks + 2));
    if (!op_toks)
    {
        mall_err();
        return;
    }
    while (i < total_toks)
    {
        new_toks[i] = op_toks[i];
        i++;
    }
    exit_str = get_int(error_code);
    if (!exit_str)
    {
        free(new_toks);
        mall_err();
        return;
    }
    new_toks[i++] = exit_str;
    new_toks[i] = NULL;
    free(op_toks);
    op_toks = new_toks;
}