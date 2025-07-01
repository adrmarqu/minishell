/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:59:14 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/01 20:27:34 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/print.h"
#include "../../libft/libft.h"

// Si es un heredoc (<<) devolver un line diferente

void	update(int exit)
{
	g_exit_status = exit;
}

void	print_token(t_token *t)
{
	printf("TOKEN:\n");
	while (t)
	{
		printf("%s\n", t->value);
		t = t->next;
	}
	printf("\n");
}

t_token	*get_lefty_token(t_cmd **cmd)
{
	t_token	*ret;

	ret = NULL;
	if ((*cmd)->command)
	{
		ret = (*cmd)->command;
		(*cmd)->command = NULL;
		return (ret);
	}
	if ((*cmd)->left)
	{
		ret = get_lefty_token(&(*cmd)->left);
		if (!(*cmd)->left->left && !(*cmd)->left->right)
		{
			free((*cmd)->left);
			(*cmd)->left = NULL;
		}
		return (ret);
	}
	if ((*cmd)->right)
	{
		ret = get_lefty_token(&(*cmd)->right);
		if (!(*cmd)->right->left && !(*cmd)->right->right)
		{
			free((*cmd)->right);
			(*cmd)->right = NULL;
		}
		return (ret);
	}
	return (NULL);
}

char	*process_command(char *line, t_data *data)
{
	t_cmd		*cmd;
	t_token		*token;

	token = get_tokens(line);
	if (!token)
		return (line);
	if (!check_syntaxis(token))
		return (ft_free_token(token), line);
	cmd = build_cmd_tree(token);
	if (!cmd)
		return (line);
	while (42)
	{
		token = get_lefty_token(&cmd);
		if (!token)
			break ;
		print_token(token);
		//if (expand(&list->token, data))
		//	return (ft_free_command(cmd), line);
		//execute_cmd(token, data);
	}
	(void)data;
	return (line);
}
