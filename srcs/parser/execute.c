/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:00:42 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/20 14:54:00 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/utils.h"
#include "../../inc/built.h"
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

static void	ft_close_files(int a, int b, bool make_dup)
{
	if (a != -1)
	{
		if (make_dup)
			dup2(a, STDIN_FILENO);
		close(a);
	}
	if (b != -1)
	{
		if (make_dup)
			dup2(b, STDOUT_FILENO);
		close(b);
	}
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
		ft_close_files(in, out, true);
		exit(execute_builtin(data, cmd->command));
	}
	ft_close_files(in, out, false);
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
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
		ft_close_files(in, out, true);
		execve(path, data->argv, data->envp);
		perror("minishell");
		exit(127);
	}
	ft_close_files(in, out, false);
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

int	execute(t_cmd *cmd, t_data *data, int input, int output)
{
	const bool	isbuiltin = is_builtin(cmd->command->value);
	int			status;

	if (isbuiltin && input == -1 && output == -1)
		return (execute_builtin(data, cmd->command));
	else if (isbuiltin)
		return (execute_builtin_fork(cmd, data, input, output));
	data->argv = tokens_to_split(cmd->command);
	if (!data->argv)
		return (1);
	data->envp = env_to_split(data->env);
	if (!data->envp)
		return (ft_free_split(data->argv), 1);
	status = execute_command(data, get_path(data), input, output);
	ft_free_split(data->argv);
	data->argv = NULL;
	ft_free_split(data->envp);
	data->envp = NULL;
	return (status);
}
