#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define MAX_STACK (20)

int _stack[MAX_STACK] = {0};
int _stackCurr = 0;

int push(int v)
{
    if (_stackCurr >= MAX_STACK)
        return 0;
    _stack[_stackCurr] = v;
    _stackCurr++;
    return 1;
}

int isEmpty()
{
    return _stackCurr <= 0;
}

int pop(int *vptr)
{
    if (isEmpty())
        return 0;
    _stackCurr--;
    *vptr = _stack[_stackCurr];
    return 1;
}

int top(int *vptr)
{

    if (isEmpty())
        return 0;
    *vptr = _stack[_stackCurr];
    return 1;
}

int size()
{
    return _stackCurr;
}

void Die()
{
    exit(1);
}

void parseline(char *line)
{
    char *token, *str, *tofree;

    tofree = str = strdup(line); // We own str's memory now.
    while ((token = strsep(&str, " ")))
    {
        // itterates through parts
        fprintf(stdout, "token: %s\n", token);
    }

    free(tofree);
}

int main(int argc, char *argv[])
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;
    while (1)
    {
        fprintf(stdout, ">");
        read = getline(&line, &len, stdin);
        if (read == -1)
            break;

        line[strlen(line) - 1] = '\0';
        if (strcmp("exit", line) == 0)
            break;

        parseline(line);
    }

    free(line);
    fprintf(stdout, "bye~\n");
    return 0;
}