#include "apue.h"

//build : gcc ./c15_17 -lapue -o add2.out
int main(void)
{
    int n, int1, int2;
    char line[MAXLINE];
    while ((n = read(STDIN_FILENO, line, MAXLINE)) > 0)
    {
        line[n] = 0;
        if (sscanf(line, "%d%d", &int1, &int2) == 2)
        {
            sprintf(line, "%d\n", int1 + int2);
            n = strlen(line);
            if (write(STDOUT_FILENO, line, n) != n)
            {
                err_sys("write error");
            }
        }
        else
        {
            if (write(STDOUT_FILENO, "invaild args\n", 13) != 13)
            {
                err_sys("write error");
            }
        }
    }
}