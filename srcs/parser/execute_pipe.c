/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 14:29:54 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/08/09 16:53:36 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"
#include "../../inc/free.h"
#include "../../inc/print.h"
#include "../../inc/parser.h"
#include "../../libft/libft.h"
#include <sys/wait.h>

static int	exec_single_command(t_data *data, char *path)
{
	if (!path)
	{
		error_not_found(data->argv[0]);
		exit(127);
	}
	execve(path, data->argv, data->envp);
	perror("minishell");
	free(path);
	ft_free_data_split(data);
	exit(127);
}

static int	wait_all_children(pid_t *pids, int n)
{
	int	i;
	int	status;
	int	wstatus;

	i = 0;
	status = 0;
	wstatus = 0;
	while (i < n)
	{
		waitpid(pids[i], &wstatus, 0);
		if (i == n - 1 && WIFEXITED(wstatus))
			status = WEXITSTATUS(wstatus);
		i++;
	}
	free(pids);
	return (status);
}

static int	fork_and_run_pipe(t_data *data, t_cmd *cmd, t_pipe pipe)
{
	char	*path;

	if (prepare_execution(cmd->pipes[pipe.idx], data, &path) != 0)
		return (1);
	pipe.pids[pipe.idx] = fork();
	if (pipe.pids[pipe.idx] < 0)
		return (free(path), perror("minishell"), 1);
	if (pipe.pids[pipe.idx] == 0)
	{
		if (pipe.idx < cmd->n_pipes - 1)
		{
			close(pipe.pipefd[0]);
			ft_close_files(pipe.input, pipe.pipefd[1], true);
		}
		else
			ft_close_files(pipe.input, pipe.output, true);
		exec_single_command(data, path);
	}
	free(path);
	ft_free_data_split(data);
	data->argv = NULL;
	data->envp = NULL;
	return (0);
}

static int	setup_pipe(int pipefd[2], int i, int n_pipes)
{
	if (i < n_pipes - 1)
	{
		if (pipe(pipefd) == -1)
			return (perror("pipe"), 1);
	}
	else
	{
		pipefd[0] = -1;
		pipefd[1] = -1;
	}
	return (0);
}

int	execute_pipe(t_cmd *cmd, t_data *data, int input, int output)
{
	t_pipe	pipe;

	pipe.pids = malloc(cmd->n_pipes * sizeof(pid_t));
	if (!pipe.pids)
		return (perror("minishell"), 1);
	pipe.input = input;
	pipe.output = output;
	pipe.idx = 0;
	while (pipe.idx < cmd->n_pipes)
	{
		if (setup_pipe(pipe.pipefd, pipe.idx, cmd->n_pipes))
			return (free(pipe.pids), 1);
		if (fork_and_run_pipe(data, cmd, pipe))
			return (free(pipe.pids), 1);
		if (pipe.input != -1)
			close(pipe.input);
		if (pipe.idx < cmd->n_pipes - 1)
		{
			close(pipe.pipefd[1]);
			pipe.input = pipe.pipefd[0];
		}
		pipe.idx++;
	}
	return (wait_all_children(pipe.pids, cmd->n_pipes));
}
