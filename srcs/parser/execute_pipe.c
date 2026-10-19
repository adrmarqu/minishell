/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 14:29:54 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/08/09 18:03:29 by adrmarqu         ###   ########.fr       */
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
		if (i == n - 1)
			status = handle_exit_status(wstatus);
		i++;
	}
	free(pids);
	return (status);
}

static void	child_pipe_exec(t_data *data, t_cmd *cmd, t_pipe p, int h_fd)
{
	int		in;
	int		out;
	char	*path;

	set_signals(data->level, 1, 1);
	in = p.input;
	out = p.output;
	if (p.idx < cmd->n_pipes - 1)
	{
		close(p.pipefd[0]);
		out = p.pipefd[1];
	}
	set_redirections(cmd->pipes[p.idx], &in, &out);
	apply_heredoc(cmd->pipes[p.idx], &in, h_fd);
	delete_node_redir(&cmd->pipes[p.idx]);
	ft_close_files(in, out, true);
	if (!cmd->pipes[p.idx])
		exit(0);
	if (is_builtin(cmd->pipes[p.idx]->value))
		exit(execute_builtin(data, cmd->pipes[p.idx]));
	path = NULL;
	if (prepare_execution(cmd->pipes[p.idx], data, &path) != 0)
		exit(1);
	exec_single_command(data, path);
}

static int	fork_and_run_pipe(t_data *data, t_cmd *cmd, t_pipe p)
{
	int	h_fd;

	if (!expand(&cmd->pipes[p.idx], data))
		return (1);
	h_fd = -1;
	if (heredoc(cmd->pipes[p.idx], &h_fd))
		return (1);
	p.pids[p.idx] = fork();
	if (p.pids[p.idx] < 0)
	{
		if (h_fd != -1)
			close(h_fd);
		return (perror("minishell"), 1);
	}
	if (p.pids[p.idx] == 0)
		child_pipe_exec(data, cmd, p, h_fd);
	if (h_fd != -1)
		close(h_fd);
	set_signals(data->level, 3, 2);
	return (0);
}

int	execute_pipe(t_cmd *cmd, t_data *data, int input, int output)
{
	t_pipe	p;

	p.pids = malloc(cmd->n_pipes * sizeof(pid_t));
	if (!p.pids)
		return (perror("minishell"), 1);
	p.input = input;
	p.output = output;
	p.idx = -1;
	while (++p.idx < cmd->n_pipes)
	{
		if (p.idx < cmd->n_pipes - 1 && pipe(p.pipefd) == -1)
			return (free(p.pids), perror("pipe"), 1);
		if (fork_and_run_pipe(data, cmd, p))
			return (free(p.pids), 1);
		if (p.input != -1)
			close(p.input);
		if (p.idx < cmd->n_pipes - 1)
		{
			close(p.pipefd[1]);
			p.input = p.pipefd[0];
		}
	}
	return (wait_all_children(p.pids, cmd->n_pipes));
}
