/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 14:29:54 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/08/03 14:41:40 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"
#include "../../inc/free.h"
#include "../../inc/parser.h"
#include "../../libft/libft.h"
#include <sys/wait.h>

static int	exec_single_command(t_token *cmd_tokens, t_data *data)
{
	char	*path;

	data->argv = tokens_to_split(cmd_tokens);
	if (!data->argv)
		return (perror("malloc argv"), 1);
	data->envp = env_to_split(data->env);
	if (!data->envp)
	{
		ft_free_split(data->argv);
		return (perror("malloc envp"), 1);
	}
	path = get_path(data);
	if (!path)
	{
		ft_free_split(data->argv);
		ft_free_split(data->envp);
		return (1);
	}
	execve(path, data->argv, data->envp);
	perror("minishell: execve");
	free(path);
	ft_free_split(data->argv);
	ft_free_split(data->envp);
	exit(127);
}

int	execute_pipe(t_cmd *cmd, t_data *data, int input, int output)
{
	int		i;
	int		pipefd[2];
	int		prev_fd;
	int		status;
	int		wstatus;
	pid_t	*pids;

	prev_fd = input;
	pids = malloc(sizeof(pid_t) * cmd->n_pipes);
	if (!pids)
		return (perror("malloc"), 1);
	i = 0;
	while (i < cmd->n_pipes)
	{
		if (i < cmd->n_pipes - 1)
		{
			if (pipe(pipefd) == -1)
			{
				perror("pipe");
				free(pids);
				return (1);
			}
		}
		else
		{
			pipefd[0] = -1;
			pipefd[1] = output;
		}
		pids[i] = fork();
		if (pids[i] < 0)
		{
			perror("fork");
			free(pids);
			return (1);
		}
		if (pids[i] == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (i < cmd->n_pipes - 1)
			{
				close(pipefd[0]);
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
			}
			else if (output != -1)
				dup2(output, STDOUT_FILENO);
			exec_single_command(cmd->pipes[i], data);
		}
		if (prev_fd != -1)
			close(prev_fd);
		if (i < cmd->n_pipes - 1)
		{
			close(pipefd[1]);
			prev_fd = pipefd[0];
		}
		i++;
	}
	status = 0;
	i = 0;
	while (i < cmd->n_pipes)
	{
		waitpid(pids[i], &wstatus, 0);
		if (i == cmd->n_pipes - 1 && WIFEXITED(wstatus))
			status = WEXITSTATUS(wstatus);
		i++;
	}
	return (free(pids), status);
}
