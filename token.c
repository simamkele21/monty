#include <stdlib.h>

char **strtok(char *str, char *delims);
int chDelimit(char ch, char *delims);
int tok_strlen(char *str, char *delims);
int str_word_count(char *str, char *delims);
char *str_next_word(char *str, char *delims);

/**
 * strtok - takes a string and seperates its words
 *
 * @str: string to seperate into words
 * @delims: delimitors to use to delimit words
 *
 * Return: 2D array of pointers to each word
 */

char **strtok(char *str, char *delims)
{
    char **words = NULL;
    int word_count, wordLen, n, i = 0;

    if (str == NULL || !*str)
        return (NULL);
    word_count = str_word_count(str, delims);

    if (word_count == 0)
        return (NULL);
    words = malloc((word_count + 1) * sizeof(char *));
    if (words == NULL)
        return (NULL);
    while (i < word_count)
    {
        wordLen = tok_strlen(str, delims);
        if (chDelimit(*str, delims))
        {
            str = str_next_word(str, delims);
        }
        words[i] = malloc((wordLen + 1) * sizeof(char));
        if (words[i] == NULL)
        {
            while (i >= 0)
            {
                i--;
                free(words[i]);
            }
            free(words);
            return (NULL);
        }
        n = 0;
        while (n < wordLen)
        {
            words[i][n] = *(str + n);
            n++;
        }
        words[i][n] = '\0'; /* set end of str */
        str = str_next_word(str, delims);
        i++;
    }
    words[i] = NULL; /* last element is null for iteration */
    return (words);
}

/**
 * chDelimit - checks if stream has delimitor char
 *
 * @ch: character in stream
 *
 * @delims: Pointer to null terminated array of delimitors
 *
 * Return: 1 (success) 0 (failure)
 */

int chDelimit(char ch, char *delims)
{
    int i = 0;

    while (delims[i])
    {
        if (delims[i] == ch)
            return (1);
        i++;
    }
    return (0);
}

/**
 * tok_strlen - gets the word length of current word in str
 *
 * @str: string to get word length from current word
 * @delims: delimitors to use to delimit words
 *
 * Return: word length of current word
 */

int tok_strlen(char *str, char *delims)
{
    int word_len = 0, pending = 1, i = 0;

    while (*(str + i))
    {
        if (chDelimit(str[i], delims))
            pending = 1;
        else if (pending)
        {
            word_len++;
        }
        if (word_len > 0 && chDelimit(str[i], delims))
            break;
        i++;
    }
    return (word_len);
}

/**
 * str_word_count - gets the word count of a string
 *
 * @str: string to get word count from
 * @delims: delimitors to use to delimit words
 *
 * Return: the word count of the string
 */

int str_word_count(char *str, char *delims)
{
    int word_count = 0, pending = 1, i = 0;

    while (*(str + i))
    {
        if (chDelimit(str[i], delims))
            pending = 1;
        else if (pending)
        {
            pending = 0;
            word_count++;
        }
        i++;
    }
    return (word_count);
}

/**
 * str_next_word - gets the next word in a string
 *
 * @str: string to get next word from
 * @delims: delimitors to use to delimit words
 *
 * Return: pointer to first char of next word
 */

char *str_next_word(char *str, char *delims)
{
    int pending = 0;
    int i = 0;

    while (*(str + i))
    {
        if (chDelimit(str[i], delims))
            pending = 1;
        else if (pending)
            break;
        i++;
    }
    return (str + i);
}