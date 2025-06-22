/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 19:15:30 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/22 14:27:34 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/print.h"
#include <stdlib.h>

#define UIT t_token_type

static void	set_types(UIT *prev, UIT *curr, UIT *next, t_token *token)
{
	*prev = *curr;
	*curr = token->type;
	token = token->next;
	while (token && (token->type == OPEN || token->type == CLOSE))
		token = token->next;
	if (!token)
		*next = VOID;
	else
		*next = token->type;
}

static bool	check_redirections(t_token *token)
{
	t_token_type	prev;
	t_token_type	curr;
	t_token_type	next;

	curr = VOID;
	while (token)
	{
		if (token->type != OPEN && token->type != CLOSE)
		{
			set_types(&prev, &curr, &next, token);
			if (curr == REDIR)
			{
				if (prev == REDIR)
					return (error_token(token->value), false);
				if (next == VOID)
					return (error_token("newline"), false);
				else if (next != WORD)
					return (error_token(token->value), false);
			}
		}
		token = token->next;
	}
	return (true);
}

static bool	check_operators(t_token *token)
{
	t_token_type	prev;
	t_token_type	curr;
	t_token_type	next;

	curr = VOID;
	while (token)
	{
		if (token->type != OPEN && token->type != CLOSE)
		{
			set_types(&prev, &curr, &next, token);
			if (curr == OP)
			{
				if (prev != WORD)
					return (error_token(token->value), false);
				if (next != WORD && next != REDIR)
					return (error_token(token->value), false);
			}
		}
		token = token->next;
	}
	return (true);
}

static bool	check_parentesis(UIT prev, UIT curr, UIT next)
{
	const UIT	open_prev[] = {WORD, REDIR, CLOSE, END};
	const UIT	close_prev[] = {OP, REDIR, END};
	const UIT	close_next[] = {WORD, OPEN, END};
	int			i;

	i = 0;
	if (curr == OPEN)
	{
		while (open_prev[i] != END)
			if (prev == open_prev[i++])
				return (false);
		if (next == OP)
			return (false);
	}
	else
	{
		while (close_prev[i] != END)
			if (prev == open_prev[i++])
				return (false);
		i = 0;
		while (close_next[i] != END)
			if (next == close_next[i++])
				return (false);
	}
	return (true);
}

bool	check_syntaxis(t_token *token)
{
	t_token_type	prev;
	t_token_type	next;

	if (!check_operators(token) || !check_redirections(token))
		return (false);
	while (token)
	{
		if (token->next)
			next = token->next->type;
		else
			next = VOID;
		if (token->type == OPEN || token->type == CLOSE)
		{
			if (!check_parentesis(prev, token->type, next))
				return (error_token(token->value), false);
		}
		prev = token->type;
		token = token->next;
	}
	return (true);
}
