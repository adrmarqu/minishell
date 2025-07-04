/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:52:56 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/04 17:12:26 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../libft/libft.h"
#include <sys/wait.h>

int	execute_pipe(t_cmd *cmd, t_data *data, int input, int output)
{
	int		pipefd[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		status;

	if (pipe(pipefd) < 0)
		return (perror("pipe"), 1);
	pid_left = fork();
	if (pid_left == 0)
	{
		if (input != -1)
			dup2(input, STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execute_cmd_tree(cmd->left, data, -1, -1);
		exit(1);
	}
	pid_right = fork();
	if (pid_right == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		if (output != -1)
			dup2(output, STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execute_cmd_tree(cmd->right, data, -1, -1);
		exit(1);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid_left, &status, 0);
	waitpid(pid_right, &status, 0);
	return (status);
}

static int	execute_operator(t_cmd *cmd, t_data *data)
{
	int	status;

	status = execute_cmd_tree(cmd->left, data, -1, -1);
	if ((cmd->op == OR && status != 0) || (cmd->op == AND && status == 0))
		status = execute_cmd_tree(cmd->right, data, -1, -1);
	return (status);
}

int	execute_cmd_tree(t_cmd *cmd, t_data *data, int input, int output)
{
	if (!cmd)
		return (1);
	if (cmd->op == PIPE)
		return (execute_pipe(cmd, data, input, output));
	else if (cmd->op == OR || cmd->op == AND)
		return (execute_operator(cmd, data));
	if (!expand(&cmd->command, data))
		return (1);
	return (execute(cmd, data, input, output));
}
