/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:52:56 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/08/03 14:32:07 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/free.h"
#include "../../inc/parser.h"
#include "../../libft/libft.h"
#include <sys/wait.h>

static int	execute_operator(t_cmd *cmd, t_data *data)
{
	int	status;

	status = execute_cmd_tree(cmd->left, data, -1, -1);
	if ((cmd->op == OR && status != 0) || (cmd->op == AND && status == 0))
		status = execute_cmd_tree(cmd->right, data, -1, -1);
	return (status);
}

static void	delete_node_redir(t_token **token)
{
	t_token	*curr;
	t_token	*prev;
	t_token	*next;

	curr = *token;
	prev = NULL;
	while (curr && curr->next)
	{
		if (get_redir_type(curr->value) != EMPTY)
		{
			next = curr->next->next;
			curr->next->next = NULL;
			ft_free_token(curr);
			if (prev)
				prev->next = next;
			else
				*token = next;
			curr = next;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}

int	execute_cmd_tree(t_cmd *cmd, t_data *data, int input, int output)
{
	if (!cmd)
		return (fd_printf(2, "ERROR CMD\n"), 1);
	if (cmd->op == PIPE)
		return (execute_pipe(cmd, data, input, output));
	else if (cmd->op == OR || cmd->op == AND)
		return (execute_operator(cmd, data));
	if (!expand(&cmd->command, data))
		return (1);
	if (heredoc(cmd->command))
		return (1);
	if (set_redirections(cmd->command, &input, &output))
		return (1);
	delete_node_redir(&cmd->command);
	if (!cmd->command)
		return (0);
	return (execute(cmd, data, input, output));
}
