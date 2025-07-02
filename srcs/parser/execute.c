#include "../../inc/parser.h"
#include "../../inc/utils.h"
#include "../../inc/built.h"
#include "../../libft/libft.h"

static int execute_builtin(t_data *data, t_token *cmd)
{
    const int   len = ft_strlen(cmd->value);

    if (!ft_strncmp(cmd->value, "cd", len))
        return (blt_cd(data, cmd));
    else if (!ft_strncmp(cmd->value, "exit", len))
        return (blt_exit(data, cmd));
    else if (!ft_strncmp(cmd->value, "export", len))
        return (blt_export(data, cmd));
    else if (!ft_strncmp(cmd->value, "unset", len))
        return (blt_unset(data, cmd));
    else if (!ft_strncmp(cmd->value, "echo", len))
        return (blt_echo(data, cmd));
    else if (!ft_strncmp(cmd->value, "pwd", len))
        return (blt_pwd(data, cmd));
    else if (!ft_strncmp(cmd->value, "env", len))
        return (blt_env(data, cmd));
    return (1);
}

int execute(t_cmd *cmd, t_data *data, int input, int output)
{
    if (isbuiltin(cmd->command->value))
        return (execute_builtin(data, cmd->command));
    return (0);
}