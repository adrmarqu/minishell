/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:34:22 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/20 11:36:19 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/print.h"
#include "../../libft/libft.h"
#include "../../inc/free.h"

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

static t_token	*find_last_of(t_token *t, int lvl, t_token_type p)
{
	t_token	*last;
	int		depth;

	depth = 0;
	last = NULL;
	while (t)
	{
		if (t->type == OPEN)
			depth++;
		else if (t->type == CLOSE)
			depth--;
		if (depth == lvl)
		{
			if (p == t->type)
				last = t;
			else if (t->type == AND && p == OR)
				last = t;
		}
		t = t->next;
	}
	return (last);
}

static t_token	*get_root_type(t_token *input)
{
	const t_token_type	types[] = {OR, PIPE, END};
	int					lvl;
	int					max_lvl;
	int					i;
	t_token				*root;

	lvl = 0;
	max_lvl = get_max_depth(input);
	root = NULL;
	while (lvl <= max_lvl)
	{
		i = 0;
		while (types[i] != END)
		{
			root = find_last_of(input, lvl, types[i]);
			if (root)
				return (root);
			i++;
		}
		lvl++;
	}
	return (NULL);
}

t_cmd	*build_cmd_tree(t_token *token)
{
	t_cmd	*cmd;
	t_token	*root;
	t_token	*a;
	t_token	*b;

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
	cmd->command = token;
	return (cmd);
}
