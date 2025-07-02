#include "../../libft/libft.h"
#include <stdbool.h>

bool isbuiltin(char *command)
{
    const char  *builtins[] = {"cd", "exit", "export", "unset", "echo", "pwd", "env", NULL};
    const int   len = ft_strlen(command);
    int         i;
    
    i = 0;
    while (builtins[i])
        if (!ft_strncmp(builtins[i], command, len))
            return (true);
    return (false);  
}