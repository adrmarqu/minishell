/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 14:29:54 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/08/03 14:52:07 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"
#include "../../inc/free.h"
#include "../../inc/print.h"
#include "../../inc/parser.h"
#include "../../libft/libft.h"
#include <sys/wait.h>

static int	prepare_execution(t_token *cmd_tokens, t_data *data, char **path)
{
	*path = NULL;
	data->argv = tokens_to_split(cmd_tokens);
	if (!data->argv)
		return (perror("malloc argv"), 1);
	data->envp = env_to_split(data->env);
	if (!data->envp)
	{
		ft_free_split(data->argv);
		return (perror("malloc envp"), 1);
	}
	*path = get_path(data);
	return (0);
}

int	exec_single_command(t_token *cmd_tokens, t_data *data)
{
	char	*path;

	if (prepare_execution(cmd_tokens, data, &path) != 0)
		return (1);
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

static void	pipe_child_exec(t_cmd *cmd, t_data *data, int i,
							int prev_fd, int pipefd[2], int output)
{
	if (i < cmd->n_pipes - 1)
		close(pipefd[0]);
	ft_close_files(prev_fd, (i < cmd->n_pipes - 1) ? pipefd[1] : output, true);
	exec_single_command(cmd->pipes[i], data);
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

static int	fork_and_run_pipe(t_cmd *cmd, t_data *data, pid_t *pids,
								int i, int prev_fd, int pipefd[2], int output)
{
	pids[i] = fork();
	if (pids[i] < 0)
		return (perror("fork"), 1);
	if (pids[i] == 0)
		pipe_child_exec(cmd, data, i, prev_fd, pipefd, output);
	return (0);
}

static int	wait_all_children(pid_t *pids, int n)
{
	int	i = 0;
	int	status = 0;
	int	wstatus;

	while (i < n)
	{
		waitpid(pids[i], &wstatus, 0);
		if (i == n - 1 && WIFEXITED(wstatus))
			status = WEXITSTATUS(wstatus);
		i++;
	}
	return (status);
}

int	execute_pipe(t_cmd *cmd, t_data *data, int input, int output)
{
	int		i = 0;
	int		pipefd[2];
	int		prev_fd = input;
	pid_t	*pids;

	pids = malloc(sizeof(pid_t) * cmd->n_pipes);
	if (!pids)
		return (perror("malloc"), 1);

	while (i < cmd->n_pipes)
	{
		if (setup_pipe(pipefd, i, cmd->n_pipes))
			return (free(pids), 1);
		if (fork_and_run_pipe(cmd, data, pids, i, prev_fd, pipefd, output))
			return (free(pids), 1);

		if (prev_fd != -1)
			close(prev_fd);
		if (i < cmd->n_pipes - 1)
		{
			close(pipefd[1]);
			prev_fd = pipefd[0];
		}
		i++;
	}
	i = wait_all_children(pids, cmd->n_pipes);
	free(pids);
	return (i);
}