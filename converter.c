#include <stdlib.h>

char *get_int(int num);
unsigned int _abs(int);
int buff_len(unsigned int num, unsigned int base);
void base_buff(unsigned int num, unsigned int base, char *buff, int buff_size);

/**
 * get_int - gets a character pointer to new string containing int
 * @num: number to convert to string
 *
 * Return: character pointer to newly created string. NULL if malloc fails.
 */
char *get_int(int num)
{
    unsigned int holder;
    int len = 0;
    char *c;

    holder = _abs(num);
    len = buff_len(holder, 10);

    if (num < 0)
        len++;
    c = malloc(len + 1);
    if (!c)
        return (NULL);

    base_buff(holder, 10, c, len);
    if (num < 0)
        c[0] = '-';

    return (c);
}

/**
 * _abs - gets the absolute value of an integer
 * @i: integer to get absolute value of
 *
 * Return: unsigned integer abs rep of i
 */
unsigned int _abs(int i)
{
    if (i < 0)
        return (-(unsigned int)i);
    return ((unsigned int)i);
}

/**
 * buff_len - gets length of buffer needed for an unsigned int
 * @num: number to get length needed for
 * @base: base of number representation used by buffer
 *
 * Return: integer containing length of buffer needed (doesn't contain null bt)
 */
int buff_len(unsigned int num, unsigned int base)
{
    int len = 1;

    while (num > base - 1)
    {
        len++;
        num /= base;
    }
    return (len);
}

/**
 * base_buff - fills buffer with correct numbers up to base 36
 * @num: number to convert to string given base
 * @base: base of number used in conversion, only works up to base 36
 * @buff: buffer to fill with result of conversion
 * @buff_size: size of buffer in bytes
 *
 * Return: always void.
 */
void base_buff(unsigned int num, unsigned int base, char *buff, int buff_size)
{
    int i = buff_size - 1;
    int j;

    buff[buff_size] = '\0';
    while (i >= 0)
    {
        j = num % base;
        if (j > 9)
            buff[i] = j + 87;
        else
            buff[i] = j + '0';
        num /= base;
        i--;
    }
}
