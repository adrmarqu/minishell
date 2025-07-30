/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:52:56 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/20 13:49:59 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../libft/libft.h"
#include <sys/wait.h>

int	execute_pipe(t_cmd *cmd, t_data *data, int input, int output)
{
	int	pipefd[2];

	if (pipe(pipefd) < 0)
		return (perror("pipe"), 1);
	execute_cmd_tree(cmd->left, data, input, pipefd[1]);
	close(pipefd[1]);
	execute_cmd_tree(cmd->right, data, pipefd[0], output);
	close(pipefd[0]);
	if (input != -1)
		close(input);
	if (output != -1)
		close(output);
	return (0);
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
	//heredoc(data, cmd->command);
	set_redirections(cmd->command, &input, &output);
	return (execute(cmd, data, input, output));
}
