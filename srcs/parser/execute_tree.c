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
#include "../../inc/utils.h"
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

void	delete_node_redir(t_token **token)
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

void	apply_heredoc(t_token *cmd, int *input, int h_fd)
{
	t_token	*curr;
	bool	last_is_h;

	if (h_fd == -1)
		return ;
	curr = cmd;
	last_is_h = false;
	while (curr)
	{
		if (!ft_strcmp(curr->value, "<<"))
			last_is_h = true;
		else if (!ft_strcmp(curr->value, "<"))
			last_is_h = false;
		curr = curr->next;
	}
	if (last_is_h)
	{
		if (*input != -1)
			close(*input);
		*input = h_fd;
	}
	else
		close(h_fd);
}

int	execute_cmd_tree(t_cmd *cmd, t_data *data, int input, int output)
{
	int	h_fd;
	int	status;

	if (!cmd)
		return (fd_printf(2, "ERROR CMD\n"), 1);
	if (cmd->op == PIPE)
		return (execute_pipe(cmd, data, input, output));
	else if (cmd->op == OR || cmd->op == AND)
		return (execute_operator(cmd, data));
	if (!expand(&cmd->command, data))
		return (1);
	h_fd = -1;
	status = heredoc(cmd->command, &h_fd);
	if (status)
		return (status);
	if (set_redirections(cmd->command, &input, &output))
		return (ft_close_files(h_fd, -1, false), 1);
	apply_heredoc(cmd->command, &input, h_fd);
	delete_node_redir(&cmd->command);
	if (!cmd->command)
		return (ft_close_files(input, output, false), 0);
	return (execute(cmd, data, input, output));
}
