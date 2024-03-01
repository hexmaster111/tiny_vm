#define WINDOWS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef WINDOWS
#include <unistd.h>
#endif
#ifdef WINDOWS
char *strsep(char **stringp, const char *delim)
{
    char *start = *stringp;
    char *p;
    p = (start != NULL) ? strpbrk(start, delim) : NULL;
    if (p == NULL)
    {
        *stringp = NULL;
    }
    else
    {
        *p = '\0';
        *stringp = p + 1;
    }
    return start;
}

#define ssize_t long long
#endif

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
    *vptr = _stack[_stackCurr - 1];
    return 1;
}

int size()
{
    return _stackCurr;
}

void Die(const char *msg)
{
    fprintf(stderr, msg);
    exit(1);
}

int pop_two(int *t, int *n)
{
    if (size() < 1)
    {
        fprintf(stdout, "size was :%d\n", size());
        return 0; // not enough elemts to pop
    }

    if (!pop(t))
        Die("Failed to pop");
    if (!pop(n))
        Die("Failed to pop");

    return 1;
}

void do_command(char *command, int arg)
{

    if (strcmp(command, "!stack") == 0)
    {
        for (size_t i = 0; i < size(); i++)
        {
            fprintf(stdout, "%d\n", _stack[i]);
        }

        return;
    }

    if (strcmp(command, "push") == 0)
    {
        if (!push(arg))
        {
            fprintf(stdout, "Couldnt push\n");
        }
        return;
    }

    if (strcmp(command, "pop") == 0)
    {
        int tmp;
        if (!pop(&tmp))
        {
            fprintf(stdout, "Couldnt pop\n");
        }
        return;
    }

    if (strcmp(command, "add") == 0)
    {
        int vl;
        int vr;

        if (!pop_two(&vr, &vl))
            Die("Not enough values in stack");

        int res = vl + vr;

        if (!push(res))
            Die("Could not push resault onto stack");

        return;
    }

    if (strcmp(command, "sub") == 0)
    {
        int vl;
        int vr;

        if (!pop_two(&vr, &vl))
            Die("Not enough values in stack");

        int res = vl - vr;

        if (!push(res))
            Die("Could not push resault onto stack");
        return;
    }

    if (strcmp(command, "div") == 0)
    {
        int vl;
        int vr;

        if (!pop_two(&vr, &vl))
            Die("Not enough values in stack");

        int res = vl / vr;

        if (!push(res))
            Die("Could not push resault onto stack");
        return;
    }

    if (strcmp(command, "mul") == 0)
    {
        int vl;
        int vr;

        if (!pop_two(&vr, &vl))
            Die("Not enough values in stack");

        int res = vl * vr;

        if (!push(res))
            Die("Could not push resault onto stack");
        return;
    }

    if (strcmp(command, "bsl") == 0)
    {
        int vl;
        int vr;

        if (!pop_two(&vr, &vl))
            Die("Not enough values in stack");

        int res = vl << vr;

        if (!push(res))
            Die("Could not push resault onto stack");
        return;
    }

    if (strcmp(command, "bsr") == 0)
    {
        int vl;
        int vr;

        if (!pop_two(&vr, &vl))
            Die("Not enough values in stack");

        int res = vl >> vr;

        if (!push(res))
            Die("Could not push resault onto stack");
        return;
    }

    if (strcmp(command, "print") == 0)
    {
        int t;
        if (!pop(&t))
        {
            fprintf(stdout, "No values in stack to print\n");
            return;
        }
        fprintf(stdout, "%d\n", t);
        return;
    }

    fprintf(stdout, "Unknown command!\n");
}

void parse_line(char *line)
{
    char *token, *str, *tofree;

    tofree = str = strdup(line); // We own str's memory now.
    char *command = NULL;
    int arg;

    while ((token = strsep(&str, " ")))
    {
        if (command == NULL)
        {
            command = strdup(token);
        }
        else
        {
            arg = atoi(token);
        }
    }

    do_command(command, arg);

    do_command("!stack", 0);

    if (command != NULL)
        free(command);

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

        if (strcmp("", line) == 0)
            continue;

        if (strcmp("!exit", line) == 0)
            break;

        parse_line(line);
    }

    free(line);
    fprintf(stdout, "bye~\n");
    return 0;
}