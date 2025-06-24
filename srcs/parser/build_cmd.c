/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:34:22 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/24 14:56:42 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/print.h"
#include "../../libft/libft.h"

static void	print_token(t_token *a, t_token *b)
{
	fd_printf(1, "Token A: \n");
	while (a)
	{
		fd_printf(1, "%s\n", a->value);
		a = a->next;
	}
	fd_printf(1, "\nToken B: \n");
	while (b)
	{
		fd_printf(1, "%s\n", b->value);
		b = b->next;
	}
}

static bool	set_portions(t_token **a, t_token **b, t_token *t, t_token *root)
{
	// Separar en 2 el token t
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
		if (p == t->type && depth == lvl)
			last = t;
		t = t->next;
	}
	return (last);
}

static t_token	*get_root_type(t_token *input)
{
	const t_token_type	types[] = {OR, AND, PIPE, END};
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

t_cmd	*new_cmd(t_token *root)
{
	t_cmd	*ret;

	ret = malloc(sizeof(t_cmd));
	if (!ret)
		return (error_memory("build_cmd/create_cmd()"), NULL);
	ret->op = END;
	ret->left = NULL;
	ret->right = NULL;
	ret->command = NULL;
	if (root)
		ret->op = root->type;
	return (ret);
}

t_cmd	*build_cmd_tree(t_token *token)
{
	t_cmd	*cmd;
	t_token	*root;
	t_token	*a;
	t_token	*b;

	a = NULL;
	b = NULL;
	root = get_root_type(token);
	cmd = new_cmd(root);
	if (!cmd)
		return (NULL);
	if (root)
	{
		if (!set_portions(&a, &b, token, root))
			return (ft_free_command(cmd), NULL);
		return (NULL);
		cmd->left = build_cmd_tree(a);
		cmd->right = build_cmd_tree(b);
		ft_free_token(a);
		ft_free_token(b);
		if (!cmd->left || !cmd->right)
			return (ft_free_command(cmd), NULL);
		return (cmd);
	}
	cmd->command = token;
	return (cmd);
}

/*

((a && b) || (c && d)) && e || f | (g && h || i) && j


((a && b) || (c && d)) && e

tokens:	(	(	a	&&	b	)	||	(	c	&&	d	)	)	&&	e

-> Liberar root

-
	left = x;	-> ((a && b) || (c && d))
	right = y;	-> e
	op = &&;
	command = NULL;

x-
	left = i;	-> a && b
	right = j;	-> c && d
	op = ||;
	command = NULL;

i-
	left = m;	-> a
	right = n;	-> b
	op = &&;
	command = NULL

j-
	left = o;	-> c
	right = p;	-> d
	op = &&;
	command = NULL

m-
	left = NULL;
	right = NULL;
	op = END;
	command = a;

n-
	left = NULL;
	right = NULL;
	op = END;
	command = b;

o-
	left = NULL;
	right = NULL;
	op = END;
	command = c;

p-
	left = NULL;
	right = NULL;
	op = END;
	command = d;

y-
	left = NULL;
	right = NULL;
	op = END;
	command = e;


*/
