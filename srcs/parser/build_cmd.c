/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:34:22 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/08/03 13:34:11 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/print.h"
#include "../../libft/libft.h"
#include "../../inc/free.h"
/*
void	print_t(t_token *t)
{
	t_token	*token;

	token = t;
	printf("----------------\n");
	while (token)
	{
		printf("%s\n", token->value);
		token = token->next;
	}
	printf("----------------\n");
}

void	print_token(t_token *t, t_token **p)
{
	int	i;

	if (t)
		print_t(t);
	else
	{
		i = 0;
		while (p && p[i])
		{
			print_t(p[i++]);
		}
	}
}*/

static void	set_portions(t_token **a, t_token **b, t_token *t, t_token *r)
{
	t_token	*curr;

	*a = t;
	curr = t;
	while (curr && curr->next && curr->next != r)
		curr = curr->next;
	curr->next = NULL;
	*b = r->next;
	r->next = NULL;
}

static t_token	*find_last_root(t_token *t, int lvl)
{
	t_token	*last;
	int		depth;

	last = NULL;
	depth = 0;
	while (t)
	{
		if (t->type == OPEN)
			depth++;
		else if (t->type == CLOSE)
			depth--;
		if (depth == lvl && (t->type == AND || t->type == OR))
			last = t;
		t = t->next;
	}
	return (last);
}

static t_token	*get_root_type(t_token *input)
{
	t_token		*root;
	int			lvl;
	const int	max = get_max_depth(input);

	lvl = 0;
	root = NULL;
	while (lvl <= max)
	{
		root = find_last_root(input, lvl);
		if (root)
			return (root);
		lvl++;
	}
	return (NULL);
}

bool	set_data_command(t_cmd **cmd, t_token *token)
{
	t_token	*t;
	int		count;

	count = 0;
	t = token;
	while (t)
	{
		if (t->type == PIPE)
			count++;
		t = t->next;
	}
	if (count)
		return (split_pipes(cmd, token, count + 1));
	(*cmd)->command = token;
	return (true);
}

t_cmd	*build_cmd_tree(t_token *token)
{
	t_cmd	*cmd;
	t_token	*root;
	t_token	*a;
	t_token *b;

	token = strip_outer_parens(token);
	root = get_root_type(token);
	cmd = new_cmd(root);
	if (!cmd)
		return (error_memory("build_cmd/build_cmd_tree()"), NULL);
	if (root)
	{
		set_portions(&a, &b, token, root);
		cmd->left = build_cmd_tree(a);
		cmd->right = build_cmd_tree(b);
		ft_free_token(root);
		if (!cmd->left || !cmd->right)
			return (ft_free_command(cmd), NULL);
		return (cmd);
	}
	if (!set_data_command(&cmd, token))
		return (ft_free_command(cmd), NULL);
	//print_token(cmd->command, cmd->pipes);
	return (cmd);
}
