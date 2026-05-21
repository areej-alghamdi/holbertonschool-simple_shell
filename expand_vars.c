#include "shell.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * expand_variables - replace $?, $$, and env variables
 * @args: array of command arguments
 * @exit_status: the last exit status
 * Return: void
 */
void expand_variables(char **args, int exit_status)
{
    int i = 0;
    char pid_str[20], status_str[20], *env_val;

    /* تحويل الأرقام إلى نصوص (يفضل استخدام دوالكم الخاصة إذا sprintf ممنوعة) */
    sprintf(pid_str, "%d", getpid());
    sprintf(status_str, "%d", exit_status);

    while (args[i] != NULL)
    {
        if (args[i][0] == '$' && args[i][1] != '\0')
        {
            if (args[i][1] == '?')
            {
                free(args[i]);
                args[i] = strdup(status_str);
            }
            else if (args[i][1] == '$')
            {
                free(args[i]);
                args[i] = strdup(pid_str);
            }
            else
            {
                env_val = getenv(args[i] + 1); /* استخدموا _getenv إذا getenv ممنوعة */
                free(args[i]);
                args[i] = env_val ? strdup(env_val) : strdup("");
            }
        }
        i++;
    }
}
