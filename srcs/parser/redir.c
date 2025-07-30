#include "../../inc/parser.h"
#include "../../libft/libft.h"
#include <fcntl.h>

static t_redir get_redir_type(char *line)
{
    if (!ft_strcmp(line, "<"))
        return (INPUT);
    else if (!ft_strcmp(line, ">"))
        return (OUTPUT);
    else if (!ft_strcmp(line, ">>"))
        return (APPEND);
    return (EMPTY);
}

static int set_stdin(char *file, int *input)
{
    int fd;

    if (!file)
        return (1);
    fd = open(file, O_RDONLY);
    if (fd < 0)
        return (perror("minishell"), 1);
    *input = fd;
    return (0);
}

static int set_stdout(char *file, int *output)
{
    int fd;

    if (!file)
        return (1);
    fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
        return (perror("minishell"), 1);
    *output = fd;
    return (0);
}

static int set_append(char *file, int *output)
{
    int fd;

    if (!file)
        return (1);
    fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0)
        return (perror("minishell"), 1);
    *output = fd;
    return (0);
}

int set_redirections(t_token *cmd, int *input, int *output)
{
    t_token *curr;
    t_redir type;
    int status;

    curr = cmd;
    while (curr)
    {
        type = get_redir_type(curr->value);
        if (type == INPUT)
            status = set_stdin(curr->next->value, input);
        else if (type == OUTPUT)
            status = set_stdout(curr->next->value, output);
        else if (type == APPEND)
            status = set_append(curr->next->value, output);
        if (status == 1)
            return (1);
        curr = curr->next;
    }
    return (0);
}