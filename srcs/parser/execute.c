/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:00:42 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/08/09 17:30:37 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/utils.h"
#include "../../inc/built.h"
#include "../../inc/print.h"
#include "../../inc/free.h"
#include "../../inc/minishell.h"
#include "../../libft/libft.h"
#include <sys/wait.h>

static int	execute_builtin(t_data *data, t_token *cmd)
{
	if (!ft_strcmp(cmd->value, "cd"))
		return (blt_cd(data, cmd));
	else if (!ft_strcmp(cmd->value, "exit"))
		return (blt_exit(data, cmd));
	else if (!ft_strcmp(cmd->value, "export"))
		return (blt_export(data, cmd));
	else if (!ft_strcmp(cmd->value, "unset"))
		return (blt_unset(data, cmd));
	else if (!ft_strcmp(cmd->value, "echo"))
		return (blt_echo(data, cmd));
	else if (!ft_strcmp(cmd->value, "pwd"))
		return (blt_pwd(data, cmd));
	else if (!ft_strcmp(cmd->value, "env"))
		return (blt_env(data, cmd));
	return (1);
}

int	handle_exit_status(int status)
{
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

static int	execute_builtin_fork(t_cmd *cmd, t_data *data, int in, int out)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (perror("minishell"), 1);
	if (pid == 0)
	{
		set_signals(1, 1);
		ft_close_files(in, out, true);
		exit(execute_builtin(data, cmd->command));
	}
	set_signals(3, 3);
	ft_close_files(in, out, false);
	waitpid(pid, &status, 0);
	return (handle_exit_status(status));
}

static int	execute_command(t_data *data, char *path, int in, int out)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (perror("minishell"), 1);
	if (pid == 0)
	{
		set_signals(1, 1);
		if (!path)
		{
			error_not_found(data->argv[0]);
			exit(127);
		}
		ft_close_files(in, out, true);
		execve(path, data->argv, data->envp);
		perror("minishell");
		exit(127);
	}
	set_signals(3, 3);
	ft_close_files(in, out, false);
	waitpid(pid, &status, 0);
	return (handle_exit_status(status));
}

int	execute(t_cmd *cmd, t_data *data, int input, int output)
{
	const bool	isbuiltin = is_builtin(cmd->command->value);
	int			status;
	char		*path;

	if (isbuiltin && input == -1 && output == -1)
		return (execute_builtin(data, cmd->command));
	else if (isbuiltin)
		return (execute_builtin_fork(cmd, data, input, output));
	if (prepare_execution(cmd->command, data, &path))
		return (1);
	status = execute_command(data, path, input, output);
	free(path);
	ft_free_data_split(data);
	return (status);
}
