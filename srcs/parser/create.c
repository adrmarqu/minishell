/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:00:41 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/27 18:08:52 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../libft/libft.h"

t_cmd	*new_cmd(t_token *copy)
{
	t_cmd	*ret;

	ret = malloc(sizeof(t_cmd));
	if (!ret)
		return (NULL);
	ret->op = END;
	ret->left = NULL;
	ret->right = NULL;
	ret->command = NULL;
	if (copy)
		ret->op = copy->type;
	return (ret);
}

t_token	*new_token(t_token *prev, t_token_type op, char *s)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = op;
	token->value = NULL;
	token->next = NULL;
	if (prev)
		prev->next = token;
	if (s)
	{
		token->value = ft_strdup(s);
		if (!token->value)
			return (ft_free_token(token), NULL);
	}
	return (token);
}

static t_token	*strip(t_token *t)
{
	t_token	*end;
	t_token	*prev;
	int		depth;

	end = t;
	prev = NULL;
	depth = 0;
	while (end)
	{
		if (end->type == OPEN)
			depth++;
		else if (end->type == CLOSE)
			depth--;
		if (depth == 0)
			break ;
		prev = end;
		end = end->next;
	}
	return (prev);
}

t_token	*strip_outer_parens(t_token *tokens)
{
	t_token	*start;
	t_token	*end;
	t_token	*inner;
	t_token	*prev;

	if (!tokens || tokens->type != OPEN)
		return (tokens);
	start = tokens;
	prev = strip(start);
	end = prev->next;
	if (end && end->next == NULL && prev != start)
	{
		inner = start->next;
		start->next = NULL;
		prev->next = NULL;
		ft_free_two_tokens(start, end);
		return (strip_outer_parens(inner));
	}
	return (tokens);
}
